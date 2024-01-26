//
// Created by Liplum on 6/13/23.
//

#include <catch2/catch_test_macros.hpp>
#include "src/models.h"

TEST_CASE("Add Product") {
  DataSet<Product> products;
  auto id = products.addProduct("test case 101", 999, 0.1, 999);
  REQUIRE(products.findById(id).has_value());
}

TEST_CASE("Delete Product") {
  DataSet<Product> products;
  auto id = products.addProduct("test case 101", 999, 0.1, 999);
  REQUIRE(products.removeProductById(id));
}

TEST_CASE("Modify Product") {
  DataSet<Product> products;
  auto id = products.addProduct("test case 101", 999, 0.1, 999);
  Product p(id, "test case 202", 799, 0, 199);
  products.updateProduct(p);
  auto found = products.findById(id);
  REQUIRE(found.has_value());
  REQUIRE((*found).name == "test case 202");
}
