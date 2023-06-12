//
// Created by Liplum on 6/6/23.
//

#include "product.h"
#include "nlohmann/json.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <utility>

using namespace std;

optional<Product> ProductSet::findById(int id) {
  for (auto &product: products) {
    if (product.id == id) {
      return product;
    }
  }
  return nullopt;
}

vector<Product> ProductSet::findByName(const string &name) {
  vector<Product> foundProducts;
  for (auto &product: products) {
    if (product.name.find(name) != string::npos) {
      foundProducts.push_back(product);
    }
  }
  return std::move(foundProducts);
}

int ProductSet::addProduct(const string &name, double price, double discount, double premiumPrice) {
  int id = curId++;
  products.emplace_back(id, name, price, discount, premiumPrice);
  markDirty();
  return id;
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


json Product::toJson() const {
  json obj;
  obj["id"] = id;
  obj["name"] = name;
  obj["price"] = price;
  obj["discount"] = discount;
  obj["premiumPrice"] = premiumPrice;
  return std::move(obj);
}

Product::Product(const json &obj) {
  id = obj["id"];
  name = obj["name"];
  price = obj["price"];
  discount = obj["discount"];
  premiumPrice = obj["premiumPrice"];
}

void writeProductList(json &arr, const vector<Product> &products) {
  for (const auto &product: products) {
    arr.push_back(product.toJson());
  }
}

// Function to serialize products to JSON file
bool ProductSet::saveToFile(const string &filename) {
  json root;
  root["curId"] = curId;
  writeProductList(root["products"], products);

  ofstream file(filename);
  if (file.is_open()) {
    file << setw(2) << root << endl;
    return true;
  } else {
    return false;
  }
}

void readProductListFromJson(const json &arr, vector<Product> &in) {
  for (const auto &obj: arr) {
    in.emplace_back(obj);
  }
}

// Function to load products from JSON file
ProductSet::ProductSet(const string &filename) {
  ifstream file(filename);
  if (file.is_open()) {
    json jsonData;
    file >> jsonData;
    curId = jsonData["curId"];
    readProductListFromJson(jsonData["products"], products);
  }
  // ignore missing file
  file.close();
}
