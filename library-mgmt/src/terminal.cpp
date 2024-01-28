#include "terminal.h"
#include "models.h"
#include <iostream>

using namespace std;
namespace ui {
    LibraryPermissionSet inputPermission() {
        cout << "Enter the permission level (0 for regular, 1 for admin): ";
        auto permissionLevel = inputInt();

        LibraryPermissionSet permission;
        if (permissionLevel >= 0) {
        }
        if (permissionLevel >= 1) {
            permission.manageBook = true;
            permission.manageUser = true;
        }
        return permission;
    }

    Terminal::Terminal(const string &userDbPath, const string &bookDbPath, const string &rentDbPath)
            : userDbPath(userDbPath),
              bookDbPath(bookDbPath), rentDbPath(rentDbPath) {
        auth = new Auth<LibraryPermissionSet>(userDbPath);
        books = new DataSet<Book>(bookDbPath);
        bookRents = new DataSet<BookRent>(rentDbPath);
    }

    Terminal::~Terminal() {
        delete auth;
        delete books;
    }

    void Terminal::initMenu() {
        if (!curUser.has_value()) {
            cout << "Unauthorized.";
            return;
        }
        // Main menu
        if (curUser->permission.manageBook) {
            mainMenu.cmd("add", "Add Book", [this]() {
                addBook();
                saveAll();
                return CommandSignal::waitNext;
            });

            mainMenu.cmd("del", "Delete Book", [this]() {
                deleteBook();
                saveAll();
                return CommandSignal::waitNext;
            });

            mainMenu.cmd("edit", "Modify Book", [this]() {
                modifyBook();
                saveAll();
                return CommandSignal::waitNext;
            });
        }

        mainMenu.cmd("search", "Search Book", [this]() {
            searchBook();
            return CommandSignal::waitNext;
        });
        mainMenu.cmd("rent", "Rent Book", [this]() {
            rentBook();
            return CommandSignal::waitNext;
        });
        mainMenu.cmd("return", "Return Book", [this]() {
            returnBook();
            return CommandSignal::waitNext;
        });

        if (curUser->permission.manageUser) {
            mainMenu.cmd("curUser", "User Management", [this]() {
                userMenu.startLoop();
                return CommandSignal::end;
            });

            // User management
            userMenu.cmd("add", "Add User", [this]() {
                addUser(*auth, inputPermission);
                saveAll();
                return CommandSignal::waitNext;
            });

            userMenu.cmd("del", "Delete User", [this]() {
                deleteUser(*auth, *curUser);
                saveAll();
                return CommandSignal::waitNext;
            });

            userMenu.cmd("edit", "Modify User", [this]() {
                modifyUser(*auth, inputPermission);
                saveAll();
                return CommandSignal::waitNext;
            });

            userMenu.cmd("search", "Search User", [this]() {
                auto users = searchUser(*auth);
                if (users.empty()) {
                    cout << "User not found." << endl;
                } else {
                    for (auto &user: users) {
                        cout << "Account: " << user.account
                             << ", Can manage product: " << user.permission.manageBook
                             << ", Can manage curUser: " << user.permission.manageUser << endl;
                    }
                }
                return CommandSignal::waitNext;
            });
        }
    }

    void Terminal::start() {
        mainMenu.startLoop();
    }

    void Terminal::saveAll() {
        if (books->clearDirty()) {
            books->saveToFile(bookDbPath);
        }
        if (auth->clearDirty()) {
            auth->saveToFile(userDbPath);
        }
        if (bookRents->clearDirty()) {
            bookRents->saveToFile(rentDbPath);
        }
    }

    void inputBook(Book &p) {
        cout << "Enter the name: ";
        p.name = inputString();
        auto $int = nonNegativeInputBox(inputInt);
        p.collection = $int.getInput("collection");
        p.rest = $int.getInput("rest");
    }
    
    void Terminal::addBook() const {
        // Get input for the new product details
        Book p;
        inputBook(p);

        // Add the new product to the DataSet<Book>
        books->addRow(p);
        cout << "Book added successfully!" << endl;
    }
    
    bool Terminal:: deleteBook() const {
        // Get the ID of the product to delete
        cout << "Enter the product ID to delete: ";
        auto id = inputInt();

        auto product = books->findById(id);
        if (!product.has_value()) {
            cout << "Book not found." << endl;
            return false;
        }

        cout << "Ensure to delete product " << product->name << "? ";
        bool ensure = inputInt();
        if (!ensure) {
            return false;
        }

        // Attempt to remove the product by ID
        if (books->removeById(id)) {
            cout << "Book deleted successfully!" << endl;
            return true;
        } else {
            cout << "Failed to delete product." << endl;
            return false;
        }
    }
    
    bool Terminal::modifyBook() const {
        // Get the ID of the product to modify
        cout << "Enter the product ID to modify: ";
        auto id = inputInt();

        // Find the product by ID
        auto product = books->findById(id);

        // Check if the product exists
        if (!product.has_value()) {
            cout << "Book not found." << endl;
            return false;
        }
        // Get input for the updated product details
        inputBook(*product);
        if (books->update(*product)) {
            cout << "Book modified successfully!" << endl;
            return true;
        } else {
            cout << "Failed to delete product." << endl;
            return false;
        }
    }

    void printBookDetails(const Book &book) {
        cout << "ID: " << book.id << ", Name: " << book.name
             << ", Collection: " << book.rest << "/" << book.collection << endl;
    }

    void Terminal::searchBook() const {
        cout << "Enter the book name or ID to search: ";
        auto searchQuery = inputString();

        // Search by name
        auto found = findByName(*books, searchQuery);

        // Search by ID
        auto productId = tryStoi(searchQuery);
        if (productId.has_value()) {
            auto productById = books->findById(*productId);
            if (productById.has_value()) {
                found.push_back(*productById);
            }
        }
        if (!found.empty()) {
            // Books found by name
            cout << "Found " << found.size() << " book(s) by name:" << endl;
            for (const auto &book: found) {
                printBookDetails(book);
            }
        } else {
            // No books found
            cout << "Book not found." << endl;
        }
    }

    bool Terminal::rentBook() {
        // Get the ID of the product to modify
        cout << "Enter the book ID to rent: ";
        auto id = inputInt();

        // Find the product by ID
        auto book = books->findById(id);

        // Check if the product exists
        if (!book.has_value()) {
            cout << "Book not found." << endl;
            return false;
        }

        if (book->rest <= 0) {
            cout << book->name << " was borrowed out." << endl;
            return false;
        }

        BookRent rent(curUser->account, book->id);
        bookRents->addRow(rent);
        (*book).rest--;
        books->update(*book);
        cout << book->name << " was borrowed by " << curUser->account << "." << endl;
        cout << "Collection: " << book->rest << "/" << book->collection << "." << endl;
        return true;
    }

    bool Terminal::returnBook() {
        // Get the ID of the product to modify
        cout << "Enter the book ID to return: ";
        auto id = inputInt();

        // Find the product by ID
        auto book = books->findById(id);

        // Check if the product exists
        if (!book.has_value()) {
            cout << "Book not found." << endl;
            return false;
        }

        if (book->collection >= book->rest) {
            cout << book->name << " was already full." << endl;
            return false;
        }

        auto it = find_if(bookRents->rows.begin(), bookRents->rows.end(), [&book, this](const BookRent &rent) {
            return rent.bookId == book->id && rent.userAccount == curUser->account;
        });
        if (it == bookRents->rows.end()) {
            return false;
        }
        cout << book->name << " was returned by " << curUser->account << "." << endl;
        cout << "Collection: " << book->rest << "/" << book->collection << "." << endl;
        bookRents->removeById(it->id);
        (*book).rest++;
        books->update(*book);
        return true;
    }

    bool Terminal::showBorrowing(){

    }
}