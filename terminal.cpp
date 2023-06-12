//
// Created by Liplum on 6/8/23.
//

#include "terminal.h"
#include <iostream>

using namespace std;

Terminal::Terminal(const string &userDbPath, const string &productDbPath)
  : userDbPath(userDbPath),
    productDbPath(productDbPath) {
  auth = new Auth(userDbPath);
  products = new ProductSet(productDbPath);
}

Terminal::~Terminal() {
  delete auth;
  delete products;
}

/**
 *
 * @param users all users
 * @return
 */
User *tryLogin(vector<User> &users);

// Function to add a new product
void addProduct(ProductSet &products);

// Function to delete a product
void deleteProduct(ProductSet &products);

// Function to modify a product
void modifyProduct(ProductSet &products);

// Function to search for a product by name or ID
void searchProduct(ProductSet &products);

void Terminal::init() {
  if (curUser == nullptr) {
    cout << "Unauthorized.";
    return;
  }
  // Main menu
  if (curUser->permission.modifyProduct) {
    mainMenu.cmd("add", "Add product", [this]() {
      // Add product callback implementation
      addProduct(*products);
      saveAll();
    });

    mainMenu.cmd("del", "Delete product", [this]() {
      // Delete product callback implementation
      deleteProduct(*products);
      saveAll();
    });

    mainMenu.cmd("edit", "Modify product", [this]() {
      // Modify product callback implementation
      modifyProduct(*products);
      saveAll();
    });
  }
  if (curUser->permission.retrieveProduct) {
    mainMenu.cmd("search", "Search product", [this]() {
      // Search product callback implementation
      searchProduct(*products);
    });

    mainMenu.cmd("show", "Display product rankings", [this]() {
      // Display product rankings callback implementation
    });
  }
  if (curUser->permission.modifyUser) {
    mainMenu.cmd("user", "User management", [this]() {
      userMenu.startLoop();
    });
  }
  // User management
  userMenu.cmd("add", "Add userMenu", [this]() {
    // Add userMenu callback implementation
    // ...
  });

  userMenu.cmd("del", "Delete userMenu", [this]() {
    // Delete userMenu callback implementation
    // ...
  });

  userMenu.cmd("edit", "Modify userMenu", [this]() {
    // Modify userMenu callback implementation
    // ...
  });

  userMenu.cmd("search", "Search userMenu", [this]() {
    // Search userMenu callback implementation
    // ...
  });
}

void Terminal::start() {
  mainMenu.startLoop();
}

void Terminal::saveAll() {
  if (products->clearDirty()) {
    products->saveToFile(productDbPath);
  }
  if (auth->clearDirty()) {
    auth->saveToFile(userDbPath);
  }
}

// Function to authenticate userMenu login
User *tryLogin(Auth &auth) {
  string account, password;

  cout << "Enter account: ";
  cin >> account;
  cout << "Enter password: ";
  cin >> password;

  User *user = auth.findUserByAccount(account);

  if (user != nullptr && user->password == password) {
    cout << "Login successful." << endl;
    return user;
  } else {
    return nullptr;
  }
}

bool Terminal::login() {
  int attempts = 0;
  while (attempts < Terminal::maxAttempts) {
    curUser = tryLogin(*auth);
    if (curUser == nullptr) {
      cout << "Invalid account or password. Please try again." << endl;
      attempts++;
    } else {
      return true;
    }
  }
  cout << "Maximum login attempts exceeded. Exiting program." << endl;
  return false;
}

// Function to add a new product
void addProduct(ProductSet &products) {
  string name;
  double price, discount, premiumPrice;

  // Get input for the new product details
  cout << "Enter the name: ";
  cin.ignore(); // Ignore any remaining newline characters
  getline(cin, name);
  cout << "Enter the price: ";
  cin >> price;
  cout << "Enter the discount: ";
  cin >> discount;
  cout << "Enter the premium price: ";
  cin >> premiumPrice;

  // Add the new product to the ProductSet
  products.addProduct(name, price, discount, premiumPrice);
  cout << "Product added successfully!" << endl;
}

// Function to delete a product
void deleteProduct(ProductSet &products) {
  int productId;

  // Get the ID of the product to delete
  cout << "Enter the product ID to delete: ";
  cin >> productId;

  // Attempt to remove the product by ID
  if (products.removeProductById(productId)) {
    cout << "Product deleted successfully!" << endl;
  } else {
    cout << "Product not found." << endl;
  }
}

// Function to modify a product
void modifyProduct(ProductSet &products) {
  int id;

  // Get the ID of the product to modify
  cout << "Enter the product ID to modify: ";
  cin >> id;

  // Find the product by ID
  auto product = products.findById(id);

  // Check if the product exists
  if (product) {
    // Get input for the updated product details
    string name;
    double price, discount, premiumPrice;

    cout << "Enter the new product name: ";
    cin.ignore(); // Ignore any remaining newline characters
    getline(cin, name);
    cout << "Enter the new product price: ";
    cin >> price;
    cout << "Enter the new product discount: ";
    cin >> discount;
    cout << "Enter the new product premium price: ";
    cin >> premiumPrice;

    // Update the product
    product->name = name;
    product->price = price;
    product->discount = discount;
    product->premiumPrice = premiumPrice;

    cout << "Product modified successfully!" << endl;
  } else {
    cout << "Product not found." << endl;
  }
}

void printProductDetails(const Product &product) {
  cout << "ID: " << product.id << ", Name: " << product.name
       << ", Price: " << product.price << ", Discount: " << product.discount
       << ", Premium Price: " << product.premiumPrice << endl;
}

// Function to search for a product by name or ID
void searchProduct(ProductSet &products) {
  string searchQuery;
  cout << "Enter the product name or ID to search: ";
  cin.ignore(); // Ignore any remaining newline characters
  getline(cin, searchQuery);

  // Search by ID
  int productId = stoi(searchQuery);
  auto productById = products.findById(productId);

  // Search by name
  auto productsByName = products.findByName(searchQuery);

  if (productById) {
    // Product found by ID
    cout << "Product found by ID:" << endl;
    printProductDetails(*productById);
  } else if (!productsByName.empty()) {
    // Products found by name
    cout << "Found " << productsByName.size() << " product(s) by name:" << endl;
    for (const auto &product: productsByName) {
      printProductDetails(product);
    }
  } else {
    // No products found
    cout << "Product not found." << endl;
  }
}