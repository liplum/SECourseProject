//
// Created by Liplum on 6/6/23.
//

#ifndef PRODMGMT_AUTH_H
#define PRODMGMT_AUTH_H

#include <utility>
#include <vector>
#include "string"
#include "../../shared/dirty.h"
#include "nlohmann/json.hpp"

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

#endif //PRODMGMT_AUTH_H
