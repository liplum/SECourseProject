//
// Created by Liplum on 6/6/23.
//

#include "auth.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

PermissionSet::PermissionSet(const json &obj) {
  retrieveProduct = obj["retrieveProduct"];
  modifyProduct = obj["modifyProduct"];
  modifyUser = obj["modifyUser"];
}

User::User(const json &obj) {
  account = obj["account"];
  password = obj["password"];
  permission = PermissionSet(obj["permission"]);
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

User *Auth::findUserByAccount(const string &account) {
  auto it = find_if(users.begin(), users.end(), [account](const User &user) {
    return user.account == account;
  });

  if (it != users.end()) {
    return &(*it);
  } else {
    return nullptr;
  }
}

bool Auth::addUser(const string &account, const string &password, const PermissionSet &permission) {
  if (findUserByAccount(account) == nullptr) {
    users.emplace_back(account, password, permission);
    markDirty();
    return true;
  } else {
    // already exists.
    return false;
  }
}

bool Auth::removeUserByAccount(const string &account) {
  for (auto it = users.begin(); it != users.end(); ++it) {
    if (it->account == account) {
      users.erase(it);
      markDirty();
      return true;
    }
  }
  return false;
}

bool Auth::updateUser(User &user) {
  for (auto &u: users) {
    if (u.account == user.account) {
      u = user; // Update the user
      markDirty();
      return true;
    }
  }
  return false; // User not found
}

void writeUserList(json &arr, const vector<User> &users) {
  for (const auto &user: users) {
    arr.push_back(user.toJson());
  }
}

bool Auth::saveToFile(const string &filename) {
  json root;
  writeUserList(root, users);

  ofstream file(filename);
  if (file.is_open()) {
    file << setw(2) << root << endl;
    return true;
  } else {
    return false;
  }
}

void readUserListFromJson(const json &arr, vector<User> &in) {
  for (const auto &obj: arr) {
    in.emplace_back(obj);
  }
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