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
}
