//
// Created by Liplum on 6/6/23.
//

#ifndef PRODMANAGESYS_UI_H
#define PRODMANAGESYS_UI_H

#include "../auth.h"

namespace ui {
/**
 *
 * @param users all users
 * @return
 */
  User *tryLogin(vector<User> &users);
}
#endif //PRODMANAGESYS_UI_H
