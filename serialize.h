//
// Created by Liplum on 6/6/23.
//

#ifndef PRODMANAGESYS_SERIALIZE_H
#define PRODMANAGESYS_SERIALIZE_H

#include "entity.h"

void saveProductsToFile(const vector<Product> &products, const string &filename);

vector<Product> loadProductsFromFile(const string &filename);

#endif //PRODMANAGESYS_SERIALIZE_H
