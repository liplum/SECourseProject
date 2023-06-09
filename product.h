//
// Created by Liplum on 6/6/23.
//
#ifndef PRODMANAGESYS_PRODUCT_H
#define PRODMANAGESYS_PRODUCT_H

#include <string>
#include <vector>
#include "nlohmann/json.hpp"

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

  json toJson() const;
};

class ProductSet {
private:
  int lastId{0};
  vector<Product> products{};
  /**
   * whether the product list or lastId is changed.
   */
  bool dirty{false};

  void markDirty();

public:
  ProductSet() = default;

  explicit ProductSet(const string &filename);
  /**
   * Clear the dirty mark.
   * @return whether is dirty.
   */
  bool clearDirty();

  bool isDirty();

  Product *findById(int id);

  vector<Product> findByName(const string &name);

  int addProduct(const string &name, double price, double discount, double premiumPrice);

  bool removeProductById(int prod);

  bool updateProduct(Product &product);

  bool saveToFile(const string &filename);

  static ProductSet *loadFromFile(const string &filename);
};

#endif //PRODMANAGESYS_PRODUCT_H
