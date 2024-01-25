//
// Created by Liplum on 6/6/23.
//

#ifndef PRODMGMT_AUTH_H
#define PRODMGMT_AUTH_H

#include <utility>
#include <vector>
#include "string"
#include "../../shared/dirty.h"
#include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

// User type with hardcoded permissions
struct PermissionSet {
  bool manageProduct = false;
  bool manageUser = false;

  explicit PermissionSet(
    bool modifyProduct = false,
    bool modifyUser = false
  ) : manageProduct(modifyProduct),
      manageUser(modifyUser) {}

  explicit PermissionSet(const json &obj);

  static PermissionSet all();

  json toJson() const;
};

struct User {
  string account;
  string password;
  PermissionSet permission;

  User() = default;

  explicit User(
    string account,
    string password,
    const PermissionSet &permission
  ) : account(std::move(account)),
      password(std::move(password)),
      permission(permission) {
  }

  explicit User(const json &obj);

  json toJson() const;
};

class Auth : public DirtyMarkMixin {
private:
  vector<User> users;
public:
  Auth() = default;

  explicit Auth(const string &filename);

  optional<User> findUserByAccount(const string &account);

  bool addUser(const string &account, const string &password, const PermissionSet &permission);

  bool removeUserByAccount(const string &account);

  bool updateUser(User &user);

  bool saveToFile(const string &filename);

  vector<User> getUsers();
};

#endif //PRODMGMT_AUTH_H
