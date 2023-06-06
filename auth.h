//
// Created by Liplum on 6/6/23.
//

#ifndef PRODMANAGESYS_AUTH_H
#define PRODMANAGESYS_AUTH_H

#include "string"

using namespace std;

// User type with hardcoded permissions
class PermissionSet {
public:
  bool retrieveProduct = false;
  bool modifyProduct = false;
  bool modifyUser = false;

  explicit PermissionSet(bool retrieveProduct = false, bool modifyProduct = false, bool modifyUser = false)
    : retrieveProduct(retrieveProduct), modifyProduct(modifyProduct), modifyUser(modifyUser) {}
};

// User information
struct User {
  string account;
  string password;
  PermissionSet permission;
};

void saveUsersToFile(const vector<User>& users, const string& filename);
vector<User>& loadUsersFromFile(const string& filename);
User* findUserByUsername(vector<User>& users, const string& username);
#endif //PRODMANAGESYS_AUTH_H
