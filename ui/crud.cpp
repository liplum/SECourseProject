//
// Created by Liplum on 6/6/23.
//

#include "crud.h"

#include <iostream>

using namespace std;
namespace ui {
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
    int productId;
    Product *product;

    // Get the ID of the product to modify
    cout << "Enter the product ID to modify: ";
    cin >> productId;

    // Find the product by ID
    product = products.findById(productId);

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
    Product *productById = products.findById(productId);

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
}

