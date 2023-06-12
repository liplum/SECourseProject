//
// Created by Liplum on 6/6/23.
//

#include "auth.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

PermissionSet::PermissionSet(const json &obj) const {

}

User::User(const json &obj) {

}

json User::toJson() const {
  json obj;
  obj["account"] = account;
  obj["password"] = password;
  obj["permission"] = permission.toJson();
  return obj;
}

json PermissionSet::toJson() const {
  json obj;
  obj["retrieveProduct"] = retrieveProduct;
  obj["modifyProduct"] = modifyProduct;
  obj["modifyUser"] = modifyUser;
  return std::move(obj);
}

User *Auth::findByAccount(const string &account) {
  auto it = find_if(users.begin(), users.end(), [account](const User &user) {
    return user.account == account;
  });

  if (it != users.end()) {
    return &(*it);
  } else {
    return nullptr;
  }
}

bool Auth::addUser(const string &account, string password, PermissionSet permission) {

}

bool Auth::removeUserByAccount(int account) {

}

bool Auth::updateUser(User &user) {

}

void writeUserToJson()

bool Auth::saveToFile(const string &filename) {
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
    file << setw(2) << jsonData << endl;
    cout << "User data saved to " << filename << endl;
  } else {
    cerr << "Unable to save user data to file." << endl;
  }
  file.close();
}

// Function to load user information from JSON file
vector<User> loadUsersFromFile(const string &filename) {
  vector<User> users;
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
      users.push_back(user);
    }
    cout << "User data loaded from " << filename << endl;
  }
  // ignore missing file
  file.close();
  return std::move(users);
}

Auth::Auth(const string &filename) {
  ifstream file(filename);
  if (file.is_open()) {
    json jsonData;
    file >> jsonData;
    readUserListFromJson(jsonData["products"], users);
  }
  // ignore missing file
  file.close();
}