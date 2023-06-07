#include <iostream>
#include "product.h"
#include "auth.h"
#include "ui/ui.h"
#include "ui/crud.h"

const auto usersDbPath = "users.json";
const auto productsDbPath = "products.json";

int main() {
  auto users = loadUsersFromFile(usersDbPath);
  auto user = ui::tryLogin(users);
  if (user == nullptr) {
    return 1;
  }
  auto products = ProductSet::loadFromFile(productsDbPath);
  while (true) {
    ui::displayMainMenu();
    int choice;
    cin >> choice;

    switch (choice) {
      case 1:
        ui::addProduct(products);
        products.saveToFile(productsDbPath);
        break;
      case 2:
        ui::deleteProduct(products);
        products.saveToFile(productsDbPath);
        break;
      case 3:
        ui::modifyProduct(products);
        products.saveToFile(productsDbPath);
        break;
      case 4:
        ui::searchProduct(products);
        break;
      case 5:
     //   ui::displayProductRankings(products);
        break;
      case 6:
        while (true) {
          ui::displayUserManagementMenu();
          int userChoice;
          cin >> userChoice;
          // Implement user management functions here
          // Add, delete, modify, search user

          if (userChoice == 0) {
            break;
          }
        }
        break;
      case 0:
        products.saveToFile(productsDbPath);
        saveUsersToFile(users, usersDbPath);
        cout << "Exiting program. Goodbye!" << endl;
        return 0;
      default:
        cout << "Invalid choice. Please try again." << endl;
    }
  }
  return 0;
}
