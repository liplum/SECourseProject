#include "terminal.h"
#include "models.h"
#include <iostream>
#include "ui.h"

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

    Terminal::Terminal(const string &userDbPath, const string &bookDbPath)
            : userDbPath(userDbPath),
              bookDbPath(bookDbPath) {
        auth = new KAuth(userDbPath);
        books = new DataSet<Book>(bookDbPath);
    }

    Terminal::~Terminal() {
        delete auth;
        delete books;
    }

    void Terminal::initMenu() {
        if (curUser == nullptr) {
            cout << "Unauthorized.";
            return;
        }
        // Main menu
        if (curUser->permission.manageBook) {
            mainMenu.cmd("add", "Add Book", [this]() {
                addBook(*books);
                saveAll();
                return CommandSignal::waitNext;
            });

            mainMenu.cmd("del", "Delete Book", [this]() {
                deleteBook(*books);
                saveAll();
                return CommandSignal::waitNext;
            });

            mainMenu.cmd("edit", "Modify Book", [this]() {
                modifyBook(*books);
                saveAll();
                return CommandSignal::waitNext;
            });
        }

        mainMenu.cmd("search", "Search Product", [this]() {
            searchBook(*books);
            return CommandSignal::waitNext;
        });

        if (curUser->permission.manageUser) {
            mainMenu.cmd("user", "User Management", [this]() {
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
                             << ", Can manage user: " << user.permission.manageUser << endl;
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
    }
}