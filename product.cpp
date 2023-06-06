//
// Created by Liplum on 6/6/23.
//

#include "product.h"
#include "nlohmann/json.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <utility>

using json = nlohmann::json;
using namespace std;

// Function to serialize products to JSON file
void saveProductsToFile(const vector<Product> &products, const string &filename) {
  json jsonData;
  for (const auto &product: products) {
    json productData;
    productData["id"] = product.id;
    productData["name"] = product.name;
    productData["price"] = product.price;
    productData["discount"] = product.discount;
    productData["premiumPrice"] = product.premiumPrice;
    jsonData.push_back(productData);
  }

  ofstream file(filename);
  if (file.is_open()) {
    file << setw(4) << jsonData << endl;
    cout << "Product data saved to " << filename << endl;
  } else {
    cerr << "Unable to save product data to file." << endl;
  }
  file.close();
}

// Function to load products from JSON file
vector<Product> loadProductsFromFile(const string &filename) {
  vector<Product> products;
  ifstream file(filename);
  if (file.is_open()) {
    json jsonData;
    file >> jsonData;
    for (const auto &productData: jsonData) {
      Product product;
      product.id = productData["id"];
      product.name = productData["name"];
      product.price = productData["price"];
      product.discount = productData["discount"];
      product.premiumPrice = productData["premiumPrice"];
      products.push_back(product);
    }
    cout << "Product data loaded from " << filename << endl;
  }
  // ignore missing file
  file.close();
  return std::move(products);
}

Product *ProductSet::findById(int id) {
  for (auto &product: products) {
    if (product.id == id) {
      return &product;
    }
  }
  return nullptr;
}

vector<Product> ProductSet::findByName(const string &name) {
  vector<Product> foundProducts;
  for (auto &product: products) {
    if (product.name == name) {
      foundProducts.push_back(product);
    }
  }
  return std::move(foundProducts);
}

int ProductSet::addProduct(const string &name, double price, double discount, double premiumPrice) {
  Product p;
  p.id = ++lastId;
  p.name = name;
  p.price = price;
  p.discount = discount;
  p.premiumPrice = premiumPrice;
  products.push_back(p);
  return p.id;
}

bool ProductSet::removeProductById(int prod) {
  for (auto it = products.begin(); it != products.end(); ++it) {
    if (it->id == prod) {
      products.erase(it);
      return true;
    }
  }
  return false;
}

bool ProductSet::updateProduct(Product& product) {
  for (auto& p : products) {
    if (p.id == product.id) {
      p = product; // Update the product
      return true;
    }
  }
  return false; // Product not found
}