#include <iostream>
#include <cstdlib>
#include "src/terminal.h"

const auto usersDbPath = "users.json";
const auto productsDbPath = "products.json";

int main() {
  ui::Terminal terminal(usersDbPath, productsDbPath);
  static auto exitHandler = [&terminal]() {
    terminal.saveAll();
    cout << "Program exit.";
  };
  atexit([]() {
    exitHandler(); // Call the lambda function within the static function
  });
  if (terminal.login()) {
    terminal.initMenu();
    terminal.start();
    return 0;
  } else {
    cout << "Maximum login attempts exceeded. Exiting program." << endl;
    return 1;
  }
}
