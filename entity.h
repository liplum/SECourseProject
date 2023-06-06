//
// Created by Liplum on 6/6/23.
//
#ifndef PRODMANAGESYS_ENTITY_H
#define PRODMANAGESYS_ENTITY_H

#include <string>
using namespace std;

// Product class to store product information
class Product {
public:
  int id{};
  string name;
  double price{};
  double discount{};
  double memberPrice{};
};

#endif //PRODMANAGESYS_ENTITY_H
