//
// Created by Liplum on 6/12/2023.
//

#ifndef PRODMANAGESYS_UI_H
#define PRODMANAGESYS_UI_H

#include "auth.h"
#include "product.h"

namespace ui {
// Function to add a new product
  void addProduct(ProductSet &products);

// Function to delete a product
  bool deleteProduct(ProductSet &products);

// Function to modify a product
  bool modifyProduct(ProductSet &products);

  void showProductRankings(ProductSet &products);

// Function to search for a product by name or ID
  void searchProduct(ProductSet &products);

  bool addUser(KAuth &auth);

  bool modifyUser(KAuth &auth);

  bool deleteUser(KAuth &auth, KUser &curUser);

  /**
   * wildcard enabled.
   * @param auth
   */
  void searchUser(KAuth &auth);

  void clearScreen();

  int inputInt();

  double inputDouble();

  string inputString();
}
#endif //PRODMANAGESYS_UI_H
