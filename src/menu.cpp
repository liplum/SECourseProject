//
// Created by Liplum on 6/6/23.
//

#include "menu.h"
#include <iostream>

using namespace std;

void Command::execute() const {
  callback();
}

std::string toLowercase(const std::string &str) {
  std::string result;
  result.reserve(str.length());
  auto locale = std::locale();
  for (auto c: str) {
    result.push_back(tolower(c, locale));
  }

  return std::move(result);
}

namespace ui {
  void Menu::cmd(const string &cmdName, const string &desc, const Callback &callback) {
    menuItems[toLowercase(cmdName)] = Command(desc, callback);
  }

  void Menu::displayMenu() {
    cout << "===== " << header << " =====" << endl;
    cout << "Choose an option:" << endl;

    for (const auto &menuItem: menuItems) {
      cout << "[" << menuItem.first << "] " << menuItem.second.description << endl;
    }

    cout << "[#] Quit" << endl;
    cout << "=====================" << endl;
  }

  void Menu::handleInput(const string &choice) {
    auto it = menuItems.find(choice);
    if (it != menuItems.end()) {
      it->second.execute();
    } else {
      cout << "Invalid option. Please try again." << endl;
    }
  }

  void Menu::startLoop() {
    string choice;
    while (true) {
      displayMenu();
      cout << "Enter your choice: ";
      cin >> choice;
      if (choice == "#") {
        break;
      }
      handleInput(toLowercase(choice));
    }
  }
}
