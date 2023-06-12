//
// Created by Liplum on 6/8/23.
//

#ifndef PRODMANAGESYS_TERMINAL_H
#define PRODMANAGESYS_TERMINAL_H

#include <utility>

#include <string>
#include "product.h"
#include "auth.h"
#include "menu.h"

using namespace std;

class Terminal {
private:
  void saveAll();

  User *curUser{nullptr};

public:
  static const int maxAttempts = 3;
  const string userDbPath;
  const string productDbPath;
  ProductSet *products;
  Auth *auth;
  Menu mainMenu{"Main Menu"};
  Menu userMenu{"User Management"};

  Terminal(const string &userDbPath, const string &productDbPath);

  ~Terminal();

  void init();

  bool login();

  void start();
};


#endif //PRODMANAGESYS_TERMINAL_H
