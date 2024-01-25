//
// Created by Liplum on 1/25/24.
//

#include "auth.h"

ProductPermissionSet ProductPermissionSet::all() {
    return ProductPermissionSet(true, true);
}

ProductPermissionSet::ProductPermissionSet(const json &obj) {
    manageProduct = obj["manageProduct"];
    manageUser = obj["manageUser"];
}

json ProductPermissionSet::toJson() const {
    json obj;
    obj["manageProduct"] = manageProduct;
    obj["manageUser"] = manageUser;
    return std::move(obj);
}