#include <iostream>
#include <vector>
#include "product.h"
#include "auth.h"
#include "ui/ui.h"
#include "ui/crud.h"

vector<User> &loadUsers() {
  return loadUsersFromFile("./users.json");
}

vector<Product> &loadProducts() {
  return loadProductsFromFile("./products.json");
}

void saveUsers(vector<User> &users) {
  saveUsersToFile(users, "./users.json");
}

void saveProducts(vector<Product> &products) {
  saveProductsToFile(products, "./products.json");
}

int main() {
  auto users = loadUsers();
  auto user = ui::tryLogin(users);
  if (user == nullptr) {
    return 1;
  }
  auto products = loadProducts();
  while (true) {
    ui::displayMainMenu();
    int choice;
    std::cin >> choice;

    switch (choice) {
      case 1:
        ui::addProduct(products);
        break;
      case 2:
        ui::deleteProduct(products);
        break;
      case 3:
        ui::modifyProduct(products);
        break;
      case 4:
        ui::searchProduct(products);
        break;
      case 5:
        ui::displayProductRankings(products);
        break;
      case 6:
        while (true) {
          ui::displayUserManagementMenu();
          int userChoice;
          std::cin >> userChoice;

          // Implement user management functions here
          // Add, delete, modify, search user

          if (userChoice == 0) {
            break;
          }
        }
        break;
      case 0:
        saveProductsToFile(products, "product_data.json");
        std::cout << "Exiting program. Goodbye!" << std::endl;
        return 0;
      default:
        std::cout << "Invalid choice. Please try again." << std::endl;
    }
  }
  return 0;
}
