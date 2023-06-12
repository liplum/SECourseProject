#include <iostream>
#include "src/terminal.h"

const auto usersDbPath = "users.json";
const auto productsDbPath = "products.json";

int main() {
  ui::Terminal terminal(usersDbPath, productsDbPath);
  if (terminal.login()) {
    terminal.initMenu();
    terminal.start();
    return 0;
  } else {
    cout << "Maximum login attempts exceeded. Exiting program." << endl;
    return 1;
  }
}
