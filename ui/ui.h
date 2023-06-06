//
// Created by Liplum on 6/6/23.
//

#ifndef PRODMANAGESYS_UI_H
#define PRODMANAGESYS_UI_H

#include "../auth.h"
#include "../product.h"

namespace ui {
/**
 *
 * @param users all users
 * @return
 */
  User *tryLogin(vector<User> &users);

  void displayMainMenu();
  void displayUserManagementMenu();
  void displayProductRankings(const std::vector<Product> &products);
}
#endif //PRODMANAGESYS_UI_H
