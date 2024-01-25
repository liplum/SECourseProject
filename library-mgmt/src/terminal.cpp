#include "terminal.h"
#include "models.h"
#include <iostream>
#include "ui.h"

using namespace std;
namespace ui {
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
        addUser(*auth);
        saveAll();
        return CommandSignal::waitNext;
      });

      userMenu.cmd("del", "Delete User", [this]() {
        deleteUser(*auth, *curUser);
        saveAll();
        return CommandSignal::waitNext;
      });

      userMenu.cmd("edit", "Modify User", [this]() {
        modifyUser(*auth);
        saveAll();
        return CommandSignal::waitNext;
      });

      userMenu.cmd("search", "Search User", [this]() {
        searchUser(*auth);
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