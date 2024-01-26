#include <iostream>
#include <cstdlib>
#include "src/terminal.h"

const auto usersDbPath = "library-mgmt/users.json";
const auto booksDbPath = "library-mgmt/books.json";

int main() {
  ui::Terminal terminal(usersDbPath, booksDbPath);
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
