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
    cin >> choice;

    switch (choice) {
      case 1:
        ui::addProduct(products);
        saveProducts(products);
        break;
      case 2:
        ui::deleteProduct(products);
        saveProducts(products);
        break;
      case 3:
        ui::modifyProduct(products);
        saveProducts(products);
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
          cin >> userChoice;
          // Implement user management functions here
          // Add, delete, modify, search user

          if (userChoice == 0) {
            break;
          }
        }
        break;
      case 0:
        saveProducts(products);
        saveUsers(users);
        cout << "Exiting program. Goodbye!" << endl;
        return 0;
      default:
        cout << "Invalid choice. Please try again." << endl;
    }
  }
  return 0;
}
