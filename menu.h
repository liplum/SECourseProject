//
// Created by Liplum on 6/6/23.
//

#ifndef PRODMANAGESYS_MENU_H
#define PRODMANAGESYS_MENU_H

#include <functional>
#include <map>
#include <utility>
#include "auth.h"
#include "product.h"

using Callback = function<void()>;

class Command {
public:
  string description;
  Callback callback;

  Command() = default;

  Command(string desc, Callback cb)
    : description(std::move(desc)), callback(std::move(cb)) {}

  void execute() const;
};

class Menu {
private:
  map<string, Command> menuItems;

public:
  const string header;

  explicit Menu(string header) : header(std::move(header)) {}

  void cmd(const string &cmdName, const string &desc, const Callback &callback);

  void displayMenu();

  void handleInput(const string &choice);

  void startLoop();
};

#endif //PRODMANAGESYS_MENU_H
