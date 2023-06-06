//
// Created by Liplum on 6/6/23.
//

#include "auth.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "nlohmann/json.hpp"

using json = nlohmann::json;
using namespace std;

// Function to serialize user information to JSON file
void saveUsersToFile(const vector<User> &users, const string &filename) {
  json jsonData;
  for (const auto &user: users) {
    json userData;
    userData["account"] = user.account;
    userData["password"] = user.password;
    userData["permission"]["retrieveProduct"] = user.permission.retrieveProduct;
    userData["permission"]["modifyProduct"] = user.permission.modifyProduct;
    userData["permission"]["modifyUser"] = user.permission.modifyUser;
    jsonData.push_back(userData);
  }

  ofstream file(filename);
  if (file.is_open()) {
    file << setw(4) << jsonData << endl;
    cout << "User data saved to " << filename << endl;
  } else {
    cerr << "Unable to save user data to file." << endl;
  }
  file.close();
}

// Function to load user information from JSON file
vector<User> &loadUsersFromFile(const string &filename) {
  auto users = new vector<User>();
  ifstream file(filename);
  if (file.is_open()) {
    json jsonData;
    file >> jsonData;
    for (const auto &userData: jsonData) {
      User user;
      user.account = userData["account"];
      user.password = userData["password"];
      user.permission.retrieveProduct = userData["permission"]["retrieveProduct"];
      user.permission.modifyProduct = userData["permission"]["modifyProduct"];
      user.permission.modifyUser = userData["permission"]["modifyUser"];
      users->push_back(user);
    }
    cout << "User data loaded from " << filename << endl;
  }
  // ignore missing file
  file.close();
  return *users;
}

// Function to find a user by account
User *findUserByUsername(vector<User> &users, const string &username) {
  auto it = find_if(users.begin(), users.end(), [username](const User &user) {
    return user.account == username;
  });

  if (it != users.end()) {
    return &(*it);
  } else {
    return nullptr;
  }
}
