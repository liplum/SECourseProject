//
// Created by Liplum on 6/6/23.
//

#include "ui.h"
#include <iostream>

using namespace std;
namespace ui {
// Function to authenticate user login
  User *tryLogin(vector<User> &users) {
    string username, password;
    int attempts = 0;

    while (attempts < 3) {
      cout << "Enter account: ";
      cin >> username;
      cout << "Enter password: ";
      cin >> password;

      User *user = findUserByUsername(users, username);

      if (user != nullptr && user->password == password) {
        cout << "Login successful." << endl;
        return user;
      } else {
        cout << "Invalid account or password. Please try again." << endl;
        attempts++;
      }
    }

    cout << "Maximum login attempts exceeded. Exiting program." << endl;
    return nullptr;
  }

// Main menu
  void displayMainMenu() {
    cout << "===== Product Management System =====" << endl;
    cout << "1. Add product" << endl;
    cout << "2. Delete product" << endl;
    cout << "3. Modify product" << endl;
    cout << "4. Search product" << endl;
    cout << "5. Display product rankings" << endl;
    cout << "6. User management" << endl;
    cout << "0. Exit" << endl;
    cout << "=====================================" << endl;
    cout << "Enter your choice: ";
  }

// User management menu
  void displayUserManagementMenu() {
    cout << "===== User Management Menu =====" << endl;
    cout << "1. Add user" << endl;
    cout << "2. Delete user" << endl;
    cout << "3. Modify user" << endl;
    cout << "4. Search user" << endl;
    cout << "0. Back to main menu" << endl;
    cout << "===============================" << endl;
    cout << "Enter your choice: ";
  }

// Function to display product rankings based on discount price
  void displayProductRankings(const vector<Product> &products) {
    vector<Product> sortedProducts = products;
    sort(sortedProducts.begin(), sortedProducts.end(), [](const Product &p1, const Product &p2) {
      return p1.discount < p2.discount;
    });

    cout << "Product Rankings (based on discount price):" << endl;
    for (const auto &product: sortedProducts) {
      cout << "ID: " << product.id << ", Name: " << product.name << ", Discount: " << product.discount
           << endl;
    }
  }

  void Command::execute() const {
    callback();
  }

  void Menu::registerCommand(const string& cmdName, const string& desc, const Callback& callback) {
    menuItems[cmdName] = Command(desc, callback);
  }

  void Menu::displayMenu() {
    cout << "===== "<< header <<" =====" << endl;
    cout << "Choose an option:" << endl;

    int optionNum = 1;
    for (const auto &menuItem: menuItems) {
      cout << optionNum << ". " << menuItem.second.description << endl;
      optionNum++;
    }

    cout << "#. Quit" << endl;
    cout << "=====================" << endl;
  }

  void Menu::handleInput(const string &choice) {
    if (choice == "#") {
      cout << "Quit..." << endl;
      return;
    }

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
      handleInput(choice);
      if (choice == "#") {
        break;
      }
    }
  }
}