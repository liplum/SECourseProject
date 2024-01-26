//
// Created by Liplum on 6/8/23.
//

#include "terminal.h"
#include <iostream>
#include "ui.h"

using namespace std;
namespace ui {

    ProductPermissionSet inputPermission() {
        cout << "Enter the permission level (0 for regular, 1 for admin): ";
        auto permissionLevel = inputInt();

        ProductPermissionSet permission;
        if (permissionLevel >= 0) {
        }
        if (permissionLevel >= 1) {
            permission.manageProduct = true;
            permission.manageUser = true;
        }
        return permission;
    }

    Terminal::Terminal(const string &userDbPath, const string &productDbPath)
            : userDbPath(userDbPath),
              productDbPath(productDbPath) {
        auth = new Auth<ProductPermissionSet>(userDbPath);
        products = new DataSet<Product>(productDbPath);
    }

    Terminal::~Terminal() {
        delete auth;
        delete products;
    }

    void Terminal::initMenu() {
        if (curUser == nullptr) {
            cout << "Unauthorized.";
            return;
        }
        // Main menu
        if (curUser->permission.manageProduct) {
            mainMenu.cmd("add", "Add Product", [this]() {
                addProduct(*products);
                saveAll();
                return CommandSignal::waitNext;
            });

            mainMenu.cmd("del", "Delete Product", [this]() {
                deleteProduct(*products);
                saveAll();
                return CommandSignal::waitNext;
            });

            mainMenu.cmd("edit", "Modify Product", [this]() {
                modifyProduct(*products);
                saveAll();
                return CommandSignal::waitNext;
            });
        }

        mainMenu.cmd("search", "Search Product", [this]() {
            searchProduct(*products);
            return CommandSignal::waitNext;
        });

        mainMenu.cmd("rank", "Display Product Ranks", [this]() {
            showProductRankings(*products);
            return CommandSignal::end;
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
                             << ", Can manage product: " << user.permission.manageProduct
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
        if (products->clearDirty()) {
            products->saveToFile(productDbPath);
        }
        if (auth->clearDirty()) {
            auth->saveToFile(userDbPath);
        }
    }

}