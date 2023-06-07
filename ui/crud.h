//
// Created by Liplum on 6/6/23.
//

#ifndef PRODMANAGESYS_CRUD_H
#define PRODMANAGESYS_CRUD_H

#include "../product.h"
#include <iostream>

using namespace std;

namespace ui {
// Function to add a new product
  void addProduct(ProductSet& products);

// Function to delete a product
  void deleteProduct(ProductSet& products);

// Function to modify a product
  void modifyProduct(ProductSet& products);

// Function to search for a product by name or ID
  void searchProduct(ProductSet& products);
}
#endif //PRODMANAGESYS_CRUD_H
