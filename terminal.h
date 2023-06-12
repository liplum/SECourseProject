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

public:
  const string userDbPath;
  const string productDbPath;
  ProductSet *products;
  Auth *auth;
  Menu main{"Main Menu"};
  Menu user{"User Management"};

  Terminal(const string &userDbPath, const string &productDbPath);

  ~Terminal();

  void init();

  void start();
};


#endif //PRODMANAGESYS_TERMINAL_H
