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
      cout << "Enter username: ";
      cin >> username;
      cout << "Enter password: ";
      cin >> password;

      User *user = findUserByUsername(users, username);

      if (user != nullptr && user->password == password) {
        cout << "Login successful." << endl;
        return user;
      } else {
        cout << "Invalid username or password. Please try again." << endl;
        attempts++;
      }
    }

    cout << "Maximum login attempts exceeded. Exiting program." << endl;
    return nullptr;
  }

// Main menu
  void displayMainMenu() {
    std::cout << "===== Product Management System =====" << std::endl;
    std::cout << "1. Add product" << std::endl;
    std::cout << "2. Delete product" << std::endl;
    std::cout << "3. Modify product" << std::endl;
    std::cout << "4. Search product" << std::endl;
    std::cout << "5. Display product rankings" << std::endl;
    std::cout << "6. User management" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "=====================================" << std::endl;
    std::cout << "Enter your choice: ";
  }

// User management menu
  void displayUserManagementMenu() {
    std::cout << "===== User Management Menu =====" << std::endl;
    std::cout << "1. Add user" << std::endl;
    std::cout << "2. Delete user" << std::endl;
    std::cout << "3. Modify user" << std::endl;
    std::cout << "4. Search user" << std::endl;
    std::cout << "0. Back to main menu" << std::endl;
    std::cout << "===============================" << std::endl;
    std::cout << "Enter your choice: ";
  }

// Function to display product rankings based on discount price
  void displayProductRankings(const std::vector<Product> &products) {
    std::vector<Product> sortedProducts = products;
    std::sort(sortedProducts.begin(), sortedProducts.end(), [](const Product &p1, const Product &p2) {
      return p1.discount < p2.discount;
    });

    std::cout << "Product Rankings (based on discount price):" << std::endl;
    for (const auto &product: sortedProducts) {
      std::cout << "ID: " << product.id << ", Name: " << product.name << ", Discount: " << product.discount
                << std::endl;
    }
  }
}