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

void ProductSet::markDirty() {
  dirty = true;
}

bool ProductSet::clearDirty() {
  bool isDirty = dirty;
  dirty = false;
  return isDirty;
}

bool ProductSet::isDirty() {
  return dirty;
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
  markDirty();
  return p.id;
}

bool ProductSet::removeProductById(int prod) {
  for (auto it = products.begin(); it != products.end(); ++it) {
    if (it->id == prod) {
      products.erase(it);
      markDirty();
      return true;
    }
  }
  return false;
}

bool ProductSet::updateProduct(Product &product) {
  for (auto &p: products) {
    if (p.id == product.id) {
      p = product; // Update the product
      markDirty();
      return true;
    }
  }
  return false; // Product not found
}

void writeProductToJson(json &obj, const Product &product) {
  obj["id"] = product.id;
  obj["name"] = product.name;
  obj["price"] = product.price;
  obj["discount"] = product.discount;
  obj["premiumPrice"] = product.premiumPrice;
}

void writeProductList(json &arr, const vector<Product> &products) {
  for (const auto &product: products) {
    json productData;
    writeProductToJson(productData, product);
    arr.push_back(productData);
  }
}

// Function to serialize products to JSON file
void ProductSet::saveToFile(const string &filename) {
  json root;
  root["lastId"] = lastId;
  writeProductList(root["products"], products);

  ofstream file(filename);
  if (file.is_open()) {
    file << setw(2) << root << endl;
    cout << "Product data saved to " << filename << endl;
  } else {
    cerr << "Unable to save product data to file." << endl;
  }
  file.close();
}

Product readProductFromJson(const json &obj) {
  Product product;
  product.id = obj["id"];
  product.name = obj["name"];
  product.price = obj["price"];
  product.discount = obj["discount"];
  product.premiumPrice = obj["premiumPrice"];
  return std::move(product);
}

void readProductListFromJson(const json &arr, vector<Product> &in) {
  for (const auto &obj: arr) {
    in.push_back(readProductFromJson(obj));
  }
}

// Function to load products from JSON file
ProductSet ProductSet::loadFromFile(const string &filename) {
  ProductSet set;
  ifstream file(filename);
  if (file.is_open()) {
    json jsonData;
    file >> jsonData;
    set.lastId = jsonData["lastId"];
    readProductListFromJson(jsonData["products"], set.products);
  }
  cout << "Product data loaded from " << filename << endl;

  // ignore missing file
  file.close();

  return std::move(set);
}
