//
// Created by Liplum on 6/6/23.
//
#ifndef PRODMANAGESYS_PRODUCT_H
#define PRODMANAGESYS_PRODUCT_H

#include <string>

using namespace std;

// Product class to store product information
class Product {
public:
  int id{};
  string name;
  double price{};
  double discount{};
  double premiumPrice{};
};

class ProductSet {
private:
  int lastId = 0;
  vector<Product> products = vector<Product>();
public:
  Product *findById(int id);

  vector<Product> findByName(const string &name);

  int addProduct(const string &name, double price, double discount, double premiumPrice);

  bool removeProductById(int prod);

  bool updateProduct(Product &product);
};

void saveProductsToFile(const vector<Product> &products, const string &filename);

vector<Product> loadProductsFromFile(const string &filename);

#endif //PRODMANAGESYS_PRODUCT_H
