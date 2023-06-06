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
  double memberPrice{};
};


void saveProductsToFile(const vector<Product> &products, const string &filename);

vector<Product> &loadProductsFromFile(const string &filename);

#endif //PRODMANAGESYS_PRODUCT_H
