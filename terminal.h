//
// Created by Liplum on 6/8/23.
//

#ifndef PRODMANAGESYS_TERMINAL_H
#define PRODMANAGESYS_TERMINAL_H

#include <utility>

#include <string>
#include "product.h"
#include "auth.h"
#include "ui/ui.h"

using namespace std;

class Terminal {
public:
  const string userDbPath;
  const string productDbPath;
  ProductSet products;
  vector<User> *users;
  ui::Menu main{"Main Menu"};
  ui::Menu user{"User Management"};

  Terminal(string userDbPath, string productDbPath) :
    userDbPath(std::move(userDbPath)), productDbPath(std::move(productDbPath)) {}

  void init();

  void loadResource();

  void start();
};


#endif //PRODMANAGESYS_TERMINAL_H
