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

enum CommandSignal {
  end, waitNext,
};

using Callback = function<CommandSignal()>;

class Command {
public:
  string description;
  Callback callback;

  Command() = default;

  Command(string desc, Callback cb)
    : description(std::move(desc)), callback(std::move(cb)) {}

  [[nodiscard]]
  CommandSignal execute() const;
};

namespace ui {
  struct MenuOptions {
    const bool askForLoop;
    const string quitNotation;

    explicit MenuOptions(bool loopSection = true, string quitNotation = "#")
      : askForLoop(loopSection), quitNotation(std::move(quitNotation)) {};
  };

  const auto defaultOptions = MenuOptions();

  class Menu {
  private:
    map<string, Command> menuItems;

  public:
    const string header;
    const MenuOptions options;

    explicit Menu(string header, MenuOptions options = defaultOptions)
      : header(std::move(header)), options(std::move(options)) {}

    void cmd(const string &cmdName, const string &desc, const Callback &callback);

    void displayMenu();

    void handleInput(const string &choice);

    void startLoop();
  };
}
#endif //PRODMANAGESYS_MENU_H
