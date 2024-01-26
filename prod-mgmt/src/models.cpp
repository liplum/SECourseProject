//
// Created by Liplum on 6/6/23.
//
#include "models.h"
#include "nlohmann/json.hpp"
#include <utility>

using namespace std;

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

