//
// Created by Liplum on 6/6/23.
//

#ifndef PRODMANAGESYS_AUTH_H
#define PRODMANAGESYS_AUTH_H

#include "string"

using namespace std;

// User type with hardcoded permissions
class UserType {
public:
  bool retrieveProduct = false;
  bool modifyProduct = false;
  bool modifyUser = false;

  explicit UserType(bool retrieveProduct = false, bool modifyProduct = false, bool modifyUser = false)
    : retrieveProduct(retrieveProduct), modifyProduct(modifyProduct), modifyUser(modifyUser) {}
};

// User information
struct User {
  string username;
  string password;
  UserType userType;
};

void saveUsersToFile(const vector<User>& users, const string& filename);
vector<User> loadUsersFromFile(const string& filename);
User* findUserByUsername(vector<User>& users, const string& username);
#endif //PRODMANAGESYS_AUTH_H
