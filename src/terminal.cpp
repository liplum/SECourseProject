//
// Created by Liplum on 6/8/23.
//

#include "terminal.h"
#include <iostream>
#include "ui.h"

using namespace std;
namespace ui {
  Terminal::Terminal(const string &userDbPath, const string &productDbPath)
    : userDbPath(userDbPath),
      productDbPath(productDbPath) {
    auth = new Auth(userDbPath);
    products = new ProductSet(productDbPath);
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
    if (curUser->permission.modifyProduct) {
      mainMenu.cmd("add", "Add Product", [this]() {
        // Add product callback implementation
        addProduct(*products);
        saveAll();
      });

      mainMenu.cmd("del", "Delete Product", [this]() {
        // Delete product callback implementation
        deleteProduct(*products);
        saveAll();
      });

      mainMenu.cmd("edit", "Modify Product", [this]() {
        // Modify product callback implementation
        modifyProduct(*products);
        saveAll();
      });
    }

    if (curUser->permission.retrieveProduct) {
      mainMenu.cmd("search", "Search Product", [this]() {
        // Search product callback implementation
        searchProduct(*products);
      });

      mainMenu.cmd("show", "Display Product Ranks", [this]() {
        // Display product rankings callback implementation
      });
    }

    if (curUser->permission.modifyUser) {
      mainMenu.cmd("user", "User Management", [this]() {
        userMenu.startLoop();
      });

      // User management
      userMenu.cmd("add", "Add User", [this]() {
        // Add userMenu callback implementation
        addUser(*auth);
        saveAll();
      });

      userMenu.cmd("del", "Delete User", [this]() {
        // Delete userMenu callback implementation
        deleteUser(*auth, *curUser);
        saveAll();
      });

      userMenu.cmd("edit", "Modify User", [this]() {
        // Modify userMenu callback implementation
        modifyUser(*auth);
        saveAll();
      });

      userMenu.cmd("search", "Search User", [this]() {
        // Search userMenu callback implementation
        searchUser(*auth);
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

// Function to authenticate userMenu login
  optional<User> tryLogin(Auth &auth) {
    string account, password;

    cout << "Enter account: ";
    getline(cin, account);
    cout << "Enter password: ";
    getline(cin, password);

    auto user = auth.findUserByAccount(account);

    if (user.has_value() && user->password == password) {
      cout << "Login successful." << endl;
      return *user;
    } else {
      return nullopt;
    }
  }

  bool Terminal::login() {
    int attempts = 0;
    while (attempts < Terminal::maxAttempts) {
      auto user = tryLogin(*auth);
      if (user.has_value()) {
        curUser = &*user;
        return true;
      } else {
        cout << "Invalid account or password. Please try again." << endl;
        attempts++;
      }
    }
    return false;
  }
}