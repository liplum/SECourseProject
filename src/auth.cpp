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
  manageProduct = obj["manageProduct"];
  manageUser = obj["manageUser"];
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
  return std::move(obj);
}

json PermissionSet::toJson() const {
  json obj;
  obj["manageProduct"] = manageProduct;
  obj["manageUser"] = manageUser;
  return std::move(obj);
}

vector<User> Auth::getUsers() {
  return users;
}

optional<User> Auth::findUserByAccount(const string &account) {
  auto it = find_if(users.begin(), users.end(), [account](const User &user) {
    return user.account == account;
  });

  if (it != users.end()) {
    return *it;
  } else {
    return nullopt;
  }
}

bool Auth::addUser(const string &account, const string &password, const PermissionSet &permission) {
  if (!findUserByAccount(account).has_value()) {
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
      if (u.password != user.password) {
        u = user; // Update the userMenu
        markDirty();
      }
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
    readUserListFromJson(jsonData, users);
  }
  // ignore missing file
  file.close();
}

