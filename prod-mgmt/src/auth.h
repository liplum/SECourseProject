//
// Created by Liplum on 1/25/24.
//

#ifndef PRODMANAGESYS_AUTH_H
#define PRODMANAGESYS_AUTH_H

#include "../../shared/auth.h"

// User type with hardcoded permissions
struct PermissionSet {
    bool manageProduct = false;
    bool manageUser = false;

    explicit PermissionSet(
            bool modifyProduct = false,
            bool modifyUser = false
    ) : manageProduct(modifyProduct),
        manageUser(modifyUser) {}

    explicit PermissionSet(const json &obj);

    static PermissionSet all();

    json toJson() const;
};

using KUser = User<PermissionSet>;
using KAuth = Auth<PermissionSet>;

#endif //PRODMANAGESYS_AUTH_H
