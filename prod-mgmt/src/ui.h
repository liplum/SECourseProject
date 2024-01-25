//
// Created by Liplum on 6/12/2023.
//

#ifndef PRODMGMT_UI_H
#define PRODMGMT_UI_H

#include "auth.h"
#include "product.h"

namespace ui {
// Function to add a new product
  void addProduct(DataSet<Product> &products);

// Function to delete a product
  bool deleteProduct(DataSet<Product> &products);

// Function to modify a product
  bool modifyProduct(DataSet<Product> &products);

  void showProductRankings(DataSet<Product> &products);

// Function to search for a product by name or ID
  void searchProduct(DataSet<Product> &products);
}
#endif //PRODMGMT_UI_H
