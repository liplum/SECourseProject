//
// Created by Liplum on 6/8/23.
//

#ifndef LIBRARYMGMT_TERMINAL_H
#define LIBRARYMGMT_TERMINAL_H

#include <utility>

#include <string>
#include "models.h"
#include "auth.h"
#include "../../shared/terminal.h"

using namespace std;
namespace ui {
    class Terminal : public BasicTerminal<LibraryPermissionSet> {
    public:
        const string userDbPath;
        const string bookDbPath;
        const string rentDbPath;
        DataSet<Book> books;
        DataSet<BookRent> bookRents;
        Menu mainMenu{"Main Menu"};
        Menu userMenu{"User Management"};
        Menu bookMenu{"Book Management"};

        Terminal(const string &userDbPath, const string &bookDbPath, const string &rentDbPath);

        void saveAll();

        void initMenu();

        void start();

    private:
        void addBook();

        optional<Book> deleteBook();

        bool modifyBook();

        void searchBook() const;

        bool borrowBook();

        bool returnBook();

        void showBorrowing();

        vector<BookRent> getBorrowedBooks(const string &account);

        void removeRentOf(const string &account);

        void removeRentOf(const int bookId);
    };
}

#endif //LIBRARYMGMT_TERMINAL_H
