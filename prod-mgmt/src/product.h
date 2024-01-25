//
// Created by Liplum on 6/6/23.
//
#ifndef PRODMGMT_PRODUCT_H
#define PRODMGMT_PRODUCT_H

#include <string>
#include <utility>
#include <vector>
#include "nlohmann/json.hpp"
#include "../../shared/dirty.h"

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

  [[nodiscard]]
  json toJson() const;
};

class ProductSet : public DirtyMarkMixin {
private:
  int curId{0};
  vector<Product> products{};
public:
  ProductSet() = default;

  explicit ProductSet(const string &filename);

  optional<Product> findById(int id);

  /**
   * wildcard enabled.
   * @param query
   * @return
   */
  vector<Product> findByName(const string &query);

  int addProduct(const string &name, double price, double discount, double premiumPrice);

  bool removeProductById(int prod);

  bool updateProduct(Product &product);

  bool saveToFile(const string &filename);

  vector<Product> getProducts();
};

#endif //PRODMGMT_PRODUCT_H
