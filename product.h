//
// Created by Liplum on 6/6/23.
//
#ifndef PRODMANAGESYS_PRODUCT_H
#define PRODMANAGESYS_PRODUCT_H

#include <string>
#include <utility>
#include <vector>
#include "nlohmann/json.hpp"
#include "dirty.h"

using namespace std;
using json = nlohmann::json;

// Product class to store product information
class Product {
public:
  int id{0};
  string name;
  double price{0};
  double discount{0};
  double premiumPrice{0};

  Product() = default;

  explicit Product(const json &obj);

  explicit Product(
    int id,
    string name,
    double price,
    double discount,
    double premiumPrice
  ) : id(id),
      name(std::move(name)),
      price(price),
      discount(discount),
      premiumPrice(premiumPrice) {
  }

  json toJson() const;
};

class ProductSet : public DirtyMarkMixin {
private:
  int curId{0};
  vector<Product> products{};
public:
  ProductSet() = default;

  explicit ProductSet(const string &filename);

  Product *findById(int id);

  vector<Product> findByName(const string &name);

  int addProduct(const string &name, double price, double discount, double premiumPrice);

  bool removeProductById(int prod);

  bool updateProduct(Product &product);

  bool saveToFile(const string &filename);
};

#endif //PRODMANAGESYS_PRODUCT_H
