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
optional<User> tryLogin(Auth &auth) {
  string account, password;

  cout << "Enter account: ";
  cin >> account;
  cout << "Enter password: ";
  cin >> password;

  auto user = auth.findUserByAccount(account);

  if (user.has_value() && user->password == password) {
    cout << "Login successful." << endl;
    return *user;
  } else {
    return nullopt;
  }
}

bool Terminal::login() {
  int attempts = 0;
  while (attempts < Terminal::maxAttempts) {
    auto user = tryLogin(*auth);
    if (user.has_value()) {
      curUser = &*user;
      return true;
    } else {
      cout << "Invalid account or password. Please try again." << endl;
      attempts++;
    }
  }
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
  if (product.has_value()) {
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
    products.updateProduct(*product);
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
  string searchQuery;
  cout << "Enter the product name or ID to search: ";
  cin.ignore(); // Ignore any remaining newline characters
  getline(cin, searchQuery);

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