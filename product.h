//
// Created by Liplum on 6/6/23.
//
#ifndef PRODMANAGESYS_PRODUCT_H
#define PRODMANAGESYS_PRODUCT_H

#include <string>
#include <vector>

using namespace std;

// Product class to store product information
class Product {
public:
  int id{};
  string name;
  double price{};
  double discount{};
  double premiumPrice{};
};

class ProductSet {
private:
  int lastId = 0;
  vector<Product> products = vector<Product>();
  /***
   * whether the product list or lastId is changed.
   */
  bool dirty = false;

  void markDirty();

public:
  /**
   * Clear the dirty mark.
   * @return whether is dirty.
   */
  bool clearDirty();

  bool isDirty();

  Product *findById(int id);

  vector<Product> findByName(const string &name);

  int addProduct(const string &name, double price, double discount, double premiumPrice);

  bool removeProductById(int prod);

  bool updateProduct(Product &product);

  void saveToFile(const string &filename);

  static ProductSet loadFromFile(const string &filename);
};

#endif //PRODMANAGESYS_PRODUCT_H
