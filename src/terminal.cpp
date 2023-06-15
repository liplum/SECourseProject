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
    if (curUser->permission.manageProduct) {
      mainMenu.cmd("add", "Add Product", [this]() {
        addProduct(*products);
        saveAll();
      });

      mainMenu.cmd("del", "Delete Product", [this]() {
        deleteProduct(*products);
        saveAll();
      });

      mainMenu.cmd("edit", "Modify Product", [this]() {
        modifyProduct(*products);
        saveAll();
      });
    }

    mainMenu.cmd("search", "Search Product", [this]() {
      searchProduct(*products);
    });

    mainMenu.cmd("show", "Display Product Ranks", [this]() {
      // Display product rankings callback implementation
    });

    if (curUser->permission.manageUser) {
      mainMenu.cmd("user", "User Management", [this]() {
        userMenu.startLoop();
      });

      // User management
      userMenu.cmd("add", "Add User", [this]() {
        addUser(*auth);
        saveAll();
      });

      userMenu.cmd("del", "Delete User", [this]() {
        deleteUser(*auth, *curUser);
        saveAll();
      });

      userMenu.cmd("edit", "Modify User", [this]() {
        modifyUser(*auth);
        saveAll();
      });

      userMenu.cmd("search", "Search User", [this]() {
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
    cout << "Enter account: ";
    auto account = inputString();
    cout << "Enter password: ";
    auto password = inputString();

    auto user = auth.findUserByAccount(account);

    if (user.has_value() && user->password == password) {
      cout << "Login successful." << endl;
      return *user;
    } else {
      return nullopt;
    }
  }

  bool Terminal::login() {
    // check if any user is available
    if (auth->begin() == auth->end()) {
      auth->addUser("admin", "admin", PermissionSet::all());
      cout << "Because there's no user available for now, an administrator is created.";
      cout << R"(account: "admin", password: "admin".)" << endl;
      saveAll();
    }

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