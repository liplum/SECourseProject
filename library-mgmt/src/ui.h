//
// Created by Liplum on 6/12/2023.
//

#ifndef PRODMGMT_UI_H
#define PRODMGMT_UI_H

#include "auth.h"
#include "models.h"

namespace ui {
// Function to add a new product
  void addBook(DataSet<Book> &products);

// Function to delete a product
  bool deleteBook(DataSet<Book> &products);

// Function to modify a product
  bool modifyBook(DataSet<Book> &products);

// Function to search for a product by name or ID
  void searchBook(DataSet<Book> &products);

}
#endif //PRODMGMT_UI_H
