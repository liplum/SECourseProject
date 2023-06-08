//
// Created by Liplum on 6/8/23.
//

#include "terminal.h"

void Terminal::loadResource() {
  users = loadUsersFromFile(userDbPath);
  products = ProductSet::loadFromFile(productDbPath);
}

void Terminal::init() {
  // Main menu
  main.registerCommand("add", "Add product", []() {
    // Add product callback implementation
    // ...
  });

  main.registerCommand("del", "Delete product", []() {
    // Delete product callback implementation
    // ...
  });

  main.registerCommand("edit", "Modify product", []() {
    // Modify product callback implementation
    // ...
  });

  main.registerCommand("search", "Search product", []() {
    // Search product callback implementation
    // ...
  });

  main.registerCommand("show", "Display product rankings", []() {
    // Display product rankings callback implementation
    // ...
  });

  main.registerCommand("user", "User management", []() {

  });

  // User management
  user.registerCommand("1", "Add user", []() {
    // Add user callback implementation
    // ...
  });

  user.registerCommand("2", "Delete user", []() {
    // Delete user callback implementation
    // ...
  });

  user.registerCommand("3", "Modify user", []() {
    // Modify user callback implementation
    // ...
  });

  user.registerCommand("4", "Search user", []() {
    // Search user callback implementation
    // ...
  });

  user.registerCommand("0", "Back to main menu", []() {
    // Back to main menu callback implementation
    // ...
  });
}

void Terminal::start() {
  main.startLoop();
}