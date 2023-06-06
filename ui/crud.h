//
// Created by Liplum on 6/6/23.
//

#ifndef PRODMANAGESYS_CRUD_H
#define PRODMANAGESYS_CRUD_H

#include "../entity.h"
#include <iostream>

using namespace std;

namespace ui {
// Function to add a new product
  void addProduct(vector<Product> &products);

// Function to delete a product
  void deleteProduct(vector<Product> &products);

// Function to modify a product
  void modifyProduct(vector<Product> &products);

// Function to search for a product by name or ID
  void searchProduct(const vector<Product> &products);
}
#endif //PRODMANAGESYS_CRUD_H
