//
// Created by Liplum on 6/6/23.
//

#include "serialize.h"
#include "nlohmann/json.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>

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
    productData["memberPrice"] = product.memberPrice;
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
      product.memberPrice = productData["memberPrice"];
      products.push_back(product);
    }
    cout << "Product data loaded from " << filename << endl;
  } else {
    cerr << "Unable to load product data from file." << endl;
  }
  file.close();
  return products;
}