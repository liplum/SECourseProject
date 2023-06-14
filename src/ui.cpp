//
// Created by Liplum on 6/12/2023.
//

#include <iostream>
#include "ui.h"

namespace ui {
// Function to add a new product
  void addProduct(ProductSet &products) {
    // Get input for the new product details
    cout << "Enter the name: ";
    auto name = inputString();
    cout << "Enter the price: ";
    auto price = inputDouble();
    cout << "Enter the discount: ";
    auto discount = inputDouble();
    cout << "Enter the premium price: ";
    auto premiumPrice = inputDouble();

    // Add the new product to the ProductSet
    products.addProduct(name, price, discount, premiumPrice);
    cout << "Product added successfully!" << endl;
  }

// Function to delete a product
  void deleteProduct(ProductSet &products) {
    // Get the ID of the product to delete
    cout << "Enter the product ID to delete: ";
    auto id = inputInt();

    // Attempt to remove the product by ID
    if (products.removeProductById(id)) {
      cout << "Product deleted successfully!" << endl;
    } else {
      cout << "Product not found." << endl;
    }
  }

// Function to modify a product
  bool modifyProduct(ProductSet &products) {
    // Get the ID of the product to modify
    cout << "Enter the product ID to modify: ";
    auto id = inputInt();

    // Find the product by ID
    auto product = products.findById(id);

    // Check if the product exists
    if (!product.has_value()) {
      cout << "Product not found." << endl;
      return false;
    }
    // Get input for the updated product details
    cout << "Enter the name: ";
    auto name = inputString();
    cout << "Enter the price: ";
    auto price = inputDouble();
    cout << "Enter the discount: ";
    auto discount = inputDouble();
    cout << "Enter the premium price: ";
    auto premiumPrice = inputDouble();

    // Update the product
    product->name = name;
    product->price = price;
    product->discount = discount;
    product->premiumPrice = premiumPrice;
    products.updateProduct(*product);
    cout << "Product modified successfully!" << endl;
    return true;
  }

  void printProductDetails(const Product &product) {
    cout << "ID: " << product.id << ", Name: " << product.name
         << ", Price: " << product.price << ", Discount: " << product.discount
         << ", Premium Price: " << product.premiumPrice << endl;
  }

  optional<int> tryStoi(const std::string &input) {
    try {
      return std::stoi(input);
    } catch (const std::invalid_argument &) {
      // Conversion failed due to invalid argument
      return std::nullopt;
    } catch (const std::out_of_range &) {
      // Conversion failed due to out of range
      return std::nullopt;
    }
  }

// Function to search for a product by name or ID
  void searchProduct(ProductSet &products) {
    cout << "Enter the product name or ID to search: ";
    auto searchQuery = inputString();

    // Search by name
    auto found = products.findByName(searchQuery);

    // Search by ID
    auto productId = tryStoi(searchQuery);
    if (productId.has_value()) {
      auto productById = products.findById(*productId);
      if (productById.has_value()) {
        found.push_back(*productById);
      }
    }
    if (!found.empty()) {
      // Products found by name
      cout << "Found " << found.size() << " product(s) by name:" << endl;
      for (const auto &product: found) {
        printProductDetails(product);
      }
    } else {
      // No products found
      cout << "Product not found." << endl;
    }
  }

// Function to display product rankings based on discount price
  void displayProductRankings(const vector<Product> &products) {
    vector<Product> sortedProducts = products;
    sort(sortedProducts.begin(), sortedProducts.end(), [](const Product &p1, const Product &p2) {
      return p1.discount < p2.discount;
    });

    cout << "Product Rankings (based on discount price):" << endl;
    for (const auto &product: sortedProducts) {
      cout << "ID: " << product.id << ", Name: " << product.name << ", Discount: " << product.discount
           << endl;
    }
  }

  bool deleteUser(Auth &auth, User &curUser) {
    cout << "Enter the account of the user to delete: ";
    auto account = inputString();

    if (account == curUser.account) {
      cout << "Cannot delete the current user." << endl;
      return false;
    }

    auto user = auth.findUserByAccount(account);
    if (!user.has_value()) {
      cout << "User not found." << endl;
      return false;
    }

    if (auth.removeUserByAccount(account)) {
      cout << "User deleted successfully." << endl;
      return true;
    } else {
      cout << "Failed to delete user." << endl;
      return false;
    }
  }

  PermissionSet inputPermission() {
    cout << "Enter the permission level (0 for regular, 1 for admin): ";
    auto permissionLevel = inputInt();

    PermissionSet permission;
    if (permissionLevel >= 0) {
    }
    if (permissionLevel >= 1) {
      permission.manageProduct = true;
      permission.manageUser = true;
    }
    return permission;
  }

  bool addUser(Auth &auth) {
    cout << "Enter the account name: ";
    auto account = inputString();

    auto existingUser = auth.findUserByAccount(account);
    if (existingUser.has_value()) {
      cout << "User with the same account already exists." << endl;
      return false;
    }

    cout << "Enter the password: ";
    auto password = inputString();

    auto permission = inputPermission();

    if (auth.addUser(account, password, permission)) {
      cout << "User added successfully." << endl;
      return true;
    } else {
      cout << "Failed to add user." << endl;
      return false;
    }
  }

  bool modifyUser(Auth &auth) {
    cout << "Enter the account of the user to modify: ";
    auto account = inputString();

    auto user = auth.findUserByAccount(account);
    if (!user.has_value()) {
      cout << "User not found." << endl;
      return false;
    }

    User &targetUser = user.value();

    // Prevent modifying the account.
    cout << "Modifying user: " << targetUser.account << endl;

    cout << "Enter the new password (leave empty to keep current password): ";
    auto newPassword = inputString();

    if (!newPassword.empty()) {
      targetUser.password = newPassword;
    }

    auto permission = inputPermission();
    targetUser.permission = permission;

    if (auth.updateUser(targetUser)) {
      cout << "User modified successfully." << endl;
      return true;
    } else {
      cout << "Failed to modify user." << endl;
      return false;
    }
  }

  void printUser(User &user) {
    cout << "Account: " << user.account
         << ", Can manage product: " << user.permission.manageProduct
         << ", Can manage user: " << user.permission.manageUser << endl;
  }

  void searchUser(Auth &auth) {
    cout << "Enter the account or wildcard(*) to search: ";
    string account = inputString();

    if (account == "*") {
      for (auto &user: auth) {
        printUser(user);
      }
    } else {
      auto user = auth.findUserByAccount(account);
      if (!user.has_value()) {
        cout << "User not found." << endl;
        return;
      }
      printUser(*user);
    }
  }

  void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
  }

  int inputInt() {
    int i;
    cin >> i;
    cin.ignore();
    return i;
  }

  double inputDouble() {
    double f;
    cin >> f;
    cin.ignore();
    return f;
  }

  string inputString() {
    string s;
    getline(cin, s);
    return std::move(s);
  }
}
