//
// Created by Liplum on 6/6/23.
//

#include "menu.h"
#include <iostream>

using namespace std;

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

void Menu::cmd(const string &cmdName, const string &desc, const Callback &callback) {
  menuItems[cmdName] = Command(desc, callback);
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
