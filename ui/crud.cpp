//
// Created by Liplum on 6/6/23.
//

#include "crud.h"

#include <iostream>

using namespace std;
namespace ui {
// Function to add a new product
  void addProduct(vector<Product> &products) {
    Product product;
    cout << "Enter product ID: ";
    cin >> product.id;
    cout << "Enter product name: ";
    cin.ignore();
    getline(cin, product.name);
    cout << "Enter product price: ";
    cin >> product.price;
    cout << "Enter product discount: ";
    cin >> product.discount;
    cout << "Enter product member price: ";
    cin >> product.memberPrice;

    products.push_back(product);
    cout << "Product added successfully." << endl;
  }

// Function to delete a product
  void deleteProduct(vector<Product> &products) {
    int productId;
    cout << "Enter the ID of the product to delete: ";
    cin >> productId;

    auto it = find_if(products.begin(), products.end(), [productId](const Product &product) {
      return product.id == productId;
    });

    if (it != products.end()) {
      products.erase(it);
      cout << "Product deleted successfully." << endl;
    } else {
      cout << "Product not found." << endl;
    }
  }

// Function to modify a product
  void modifyProduct(vector<Product> &products) {
    int productId;
    cout << "Enter the ID of the product to modify: ";
    cin >> productId;

    auto it = find_if(products.begin(), products.end(), [productId](const Product &product) {
      return product.id == productId;
    });

    if (it != products.end()) {
      Product &product = *it;
      cout << "Enter new product name: ";
      cin.ignore();
      getline(cin, product.name);
      cout << "Enter new product price: ";
      cin >> product.price;
      cout << "Enter new product discount: ";
      cin >> product.discount;
      cout << "Enter new product member price: ";
      cin >> product.memberPrice;
      cout << "Product modified successfully." << endl;
    } else {
      cout << "Product not found." << endl;
    }
  }

// Function to search for a product by name or ID
  void searchProduct(const vector<Product> &products) {
    string searchTerm;
    cout << "Enter product name or ID to search: ";
    cin.ignore();
    getline(cin, searchTerm);

    cout << "Search results:" << endl;
    bool found = false;

    for (const auto &product: products) {
      if (product.name.find(searchTerm) != string::npos || to_string(product.id) == searchTerm) {
        cout << "ID: " << product.id << ", Name: " << product.name << ", Price: " << product.price
             << ", Discount: " << product.discount << ", Member Price: " << product.memberPrice << endl;
        found = true;
      }
    }

    if (!found) {
      cout << "No products found." << endl;
    }
  }
}
