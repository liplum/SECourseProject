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
  bool retreieveProduct;
  bool modifyProduct;
  bool modifyUser;

  UserType(bool retreieveProduct = false, bool modifyProduct = false, bool modifyUser = false)
    : retreieveProduct(retreieveProduct), modifyProduct(modifyProduct), modifyUser(modifyUser) {}
};

// User information
struct User {
  string username;
  string password;
  UserType userType;
};

#endif //PRODMANAGESYS_AUTH_H
