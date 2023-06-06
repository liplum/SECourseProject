#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "entity.h"
#include "serialize.h"

// Function to add a new product
void addProduct(std::vector<Product>& products) {
  Product product;
  std::cout << "Enter product ID: ";
  std::cin >> product.id;
  std::cout << "Enter product name: ";
  std::cin.ignore();
  std::getline(std::cin, product.name);
  std::cout << "Enter product price: ";
  std::cin >> product.price;
  std::cout << "Enter product discount: ";
  std::cin >> product.discount;
  std::cout << "Enter product member price: ";
  std::cin >> product.memberPrice;

  products.push_back(product);
  std::cout << "Product added successfully." << std::endl;
}

// Function to delete a product
void deleteProduct(std::vector<Product>& products) {
  int productId;
  std::cout << "Enter the ID of the product to delete: ";
  std::cin >> productId;

  auto it = std::find_if(products.begin(), products.end(), [productId](const Product& product) {
    return product.id == productId;
  });

  if (it != products.end()) {
    products.erase(it);
    std::cout << "Product deleted successfully." << std::endl;
  } else {
    std::cout << "Product not found." << std::endl;
  }
}

// Function to modify a product
void modifyProduct(std::vector<Product>& products) {
  int productId;
  std::cout << "Enter the ID of the product to modify: ";
  std::cin >> productId;

  auto it = std::find_if(products.begin(), products.end(), [productId](const Product& product) {
    return product.id == productId;
  });

  if (it != products.end()) {
    Product& product = *it;
    std::cout << "Enter new product name: ";
    std::cin.ignore();
    std::getline(std::cin, product.name);
    std::cout << "Enter new product price: ";
    std::cin >> product.price;
    std::cout << "Enter new product discount: ";
    std::cin >> product.discount;
    std::cout << "Enter new product member price: ";
    std::cin >> product.memberPrice;
    std::cout << "Product modified successfully." << std::endl;
  } else {
    std::cout << "Product not found." << std::endl;
  }
}

// Function to search for a product by name or ID
void searchProduct(const std::vector<Product>& products) {
  std::string searchTerm;
  std::cout << "Enter product name or ID to search: ";
  std::cin.ignore();
  std::getline(std::cin, searchTerm);

  std::cout << "Search results:" << std::endl;
  bool found = false;

  for (const auto& product : products) {
    if (product.name.find(searchTerm) != std::string::npos || std::to_string(product.id) == searchTerm) {
      std::cout << "ID: " << product.id << ", Name: " << product.name << ", Price: " << product.price
                << ", Discount: " << product.discount << ", Member Price: " << product.memberPrice << std::endl;
      found = true;
    }
  }

  if (!found) {
    std::cout << "No products found." << std::endl;
  }
}

// Function to display product rankings based on discount price
void displayProductRankings(const std::vector<Product>& products) {
  std::vector<Product> sortedProducts = products;
  std::sort(sortedProducts.begin(), sortedProducts.end(), [](const Product& p1, const Product& p2) {
    return p1.discount < p2.discount;
  });

  std::cout << "Product Rankings (based on discount price):" << std::endl;
  for (const auto& product : sortedProducts) {
    std::cout << "ID: " << product.id << ", Name: " << product.name << ", Discount: " << product.discount << std::endl;
  }
}

// Function to manage user login
bool userLogin() {
  std::string username, password;
  int attempts = 0;

  while (attempts < 3) {
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    // Add your login verification logic here

    if (username == "admin" && password == "admin") {
      std::cout << "Login successful." << std::endl;
      return true;
    } else {
      std::cout << "Invalid username or password. Please try again." << std::endl;
      attempts++;
    }
  }

  std::cout << "Maximum login attempts exceeded. Exiting program." << std::endl;
  return false;
}

// Main menu
void displayMainMenu() {
  std::cout << "===== Product Management System =====" << std::endl;
  std::cout << "1. Create product price information file" << std::endl;
  std::cout << "2. Add product price information" << std::endl;
  std::cout << "3. Delete product price information" << std::endl;
  std::cout << "4. Modify product price information" << std::endl;
  std::cout << "5. Search product price" << std::endl;
  std::cout << "6. Display product rankings" << std::endl;
  std::cout << "7. User management" << std::endl;
  std::cout << "8. User login" << std::endl;
  std::cout << "0. Exit" << std::endl;
  std::cout << "=====================================" << std::endl;
  std::cout << "Enter your choice: ";
}

// User management menu
void displayUserManagementMenu() {
  std::cout << "===== User Management Menu =====" << std::endl;
  std::cout << "1. Add user" << std::endl;
  std::cout << "2. Delete user" << std::endl;
  std::cout << "3. Modify user" << std::endl;
  std::cout << "4. Search user" << std::endl;
  std::cout << "0. Back to main menu" << std::endl;
  std::cout << "===============================" << std::endl;
  std::cout << "Enter your choice: ";
}

int main() {
  std::vector<Product> products;
  bool loggedIn = false;

  while (true) {
    if (!loggedIn) {
      if (!userLogin()) {
        break;
      }
      loggedIn = true;
    }

    displayMainMenu();
    int choice;
    std::cin >> choice;

    switch (choice) {
      case 1:
        saveProductsToFile(products, "product_data.json");
        break;
      case 2:
        addProduct(products);
        break;
      case 3:
        deleteProduct(products);
        break;
      case 4:
        modifyProduct(products);
        break;
      case 5:
        searchProduct(products);
        break;
      case 6:
        displayProductRankings(products);
        break;
      case 7:
        while (true) {
          displayUserManagementMenu();
          int userChoice;
          std::cin >> userChoice;

          // Implement user management functions here
          // Add, delete, modify, search user

          if (userChoice == 0) {
            break;
          }
        }
        break;
      case 8:
        loggedIn = false;
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
