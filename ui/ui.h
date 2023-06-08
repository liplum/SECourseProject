//
// Created by Liplum on 6/6/23.
//

#ifndef PRODMANAGESYS_UI_H
#define PRODMANAGESYS_UI_H

#include <functional>
#include <map>
#include <utility>
#include "../auth.h"
#include "../product.h"

namespace ui {
/**
 *
 * @param users all users
 * @return
 */
  User *tryLogin(vector<User> &users);

  void displayMainMenu();

  void displayUserManagementMenu();

  void displayProductRankings(const vector<Product> &products);

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

    Menu(string header) : header(std::move(header)) {}

    void registerCommand(const string &cmdName, const string &desc, const Callback &callback);

    void displayMenu();

    void handleInput(const string &choice);

    void startLoop();
  };
}
#endif //PRODMANAGESYS_UI_H
