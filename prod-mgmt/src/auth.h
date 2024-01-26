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
struct ProductPermissionSet {
    bool manageProduct = false;
    bool manageUser = false;

    explicit ProductPermissionSet(
            bool modifyProduct = false,
            bool modifyUser = false
    ) : manageProduct(modifyProduct),
        manageUser(modifyUser) {}

    explicit ProductPermissionSet(const json &obj);

    static ProductPermissionSet all();

    json toJson() const;
};

#endif //PRODMGMT_AUTH_H
