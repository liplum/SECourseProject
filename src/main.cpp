#include <iostream>
#include "terminal.h"

const auto usersDbPath = "users.json";
const auto productsDbPath = "products.json";

int main() {
  Terminal terminal(usersDbPath, productsDbPath);
  if (terminal.login()) {
    terminal.init();
    terminal.start();
    return 0;
  } else {
    cout << "Maximum login attempts exceeded. Exiting program." << endl;
    return 1;
  }
}