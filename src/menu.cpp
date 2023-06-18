//
// Created by Liplum on 6/6/23.
//

#include "menu.h"
#include "utils.h"
#include <iostream>
#include "ui.h"

using namespace std;

CommandSignal Command::execute() const {
  return callback();
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

    cout << "[" << options.quitNotation << "] Quit" << endl;
    cout << "=====================" << endl;
  }

  /**
   * # Yes
   * y, yes, ok
   * # No
   * n, no
   * @param input the case-insensitive user input that indicates `yes` or `no`.
   * @return true for `yes`, false for `no`.
   */
  bool yesOrNo(const string &input) {
    // Convert input to lowercase for case-insensitive comparison
    string lowercaseInput = toLowercase(input);

    // List of valid affirmative and negative responses
    const vector<string> affirmative = {"y", "yes", "ok"};
    const vector<string> negative = {"n", "no"};

    // Check if the input matches any affirmative or negative response
    if (std::find(affirmative.begin(), affirmative.end(), lowercaseInput) != affirmative.end()) {
      return true; // Affirmative response
    } else if (std::find(negative.begin(), negative.end(), lowercaseInput) != negative.end()) {
      return false; // Negative response
    }

    // Invalid response, default to false (no)
    return false;
  }

  void Menu::handleInput(const string &choice) {
    auto it = menuItems.find(choice);
    if (it != menuItems.end()) {
      while (true) {
        auto signal = it->second.execute();
        if (signal == CommandSignal::end) {
          break;
        } else if (signal == CommandSignal::waitNext) {
          cout << "Continue(y/n)? ";
          string leave = inputString();
          if (leave.empty() || yesOrNo(leave)) {
            continue;
          } else {
            break;
          }
        }
      }
    } else {
      cout << "Invalid option. Please try again." << endl;
    }
  }

  void Menu::startLoop() {
    while (true) {
      displayMenu();
      cout << "Command: ";
      auto choice = inputString();
      if (choice == options.quitNotation) {
        break;
      }
      handleInput(toLowercase(choice));
    }
  }
}
