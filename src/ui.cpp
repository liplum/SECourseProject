//
// Created by Liplum on 6/12/2023.
//

#include <iostream>
#include "ui.h"

namespace ui {
  void inputProduct(Product &p) {
    cout << "Enter the name: ";
    p.name = inputString();

    // Input and validate price
    while (true) {
      cout << "Enter the price: ";
      p.price = inputDouble();
      if (p.price >= 0) {
        break;
      } else {
        cout << "Invalid price. Please enter a non-negative value." << endl;
      }
    }

    // Input and validate discount
    while (true) {
      cout << "Enter the discount: ";
      p.discount = inputDouble();
      if (p.discount >= 0 && p.discount <= 1) {
        break;
      } else {
        cout << "Invalid discount. Please enter a value between 0 and 1." << endl;
      }
    }

    // Input and validate premium price
    while (true) {
      cout << "Enter the premium price: ";
      p.premiumPrice = inputDouble();
      if (p.premiumPrice >= 0) {
        break;
      } else {
        cout << "Invalid premium price. Please enter a non-negative value." << endl;
      }
    }
  }


  // Function to add a new product
  void addProduct(ProductSet &products) {
    // Get input for the new product details
    Product p;
    inputProduct(p);

    // Add the new product to the ProductSet
    products.addProduct(p.name, p.price, p.discount, p.premiumPrice);
    cout << "Product added successfully!" << endl;
  }

// Function to delete a product
  bool deleteProduct(ProductSet &products) {
    // Get the ID of the product to delete
    cout << "Enter the product ID to delete: ";
    auto id = inputInt();

    auto product = products.findById(id);
    if (!product.has_value()) {
      cout << "Product not found." << endl;
      return false;
    }

    cout << "Ensure to delete product " << product->name << "?";
    bool ensure = inputInt();
    if (!ensure) {
      return false;
    }

    // Attempt to remove the product by ID
    if (products.removeProductById(id)) {
      cout << "Product deleted successfully!" << endl;
      return true;
    } else {
      cout << "Failed to delete product." << endl;
      return false;
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
    inputProduct(*product);
    if (products.updateProduct(*product)) {
      cout << "Product modified successfully!" << endl;
      return true;
    } else {
      cout << "Failed to delete product." << endl;
      return false;
    }
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
  void showProductRankings(ProductSet &products) {
    vector<Product> sorted = products.getProducts();
    sort(sorted.begin(), sorted.end(), [](const Product &p1, const Product &p2) {
      return p1.price < p2.price;
    });

    cout << "Product Rankings (based on price):" << endl;
    for (const auto &product: sorted) {
      printProductDetails(product);
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

    cout << "Ensure to delete user " << user->account << "?";
    bool ensure = inputInt();
    if (!ensure) {
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
      for (auto &user: auth.getUsers()) {
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
