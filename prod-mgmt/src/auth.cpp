//
// Created by Liplum on 1/25/24.
//

#include "auth.h"

PermissionSet PermissionSet::all() {
    return PermissionSet(true, true);
}

PermissionSet::PermissionSet(const json &obj) {
    manageProduct = obj["manageProduct"];
    manageUser = obj["manageUser"];
}

json PermissionSet::toJson() const {
    json obj;
    obj["manageProduct"] = manageProduct;
    obj["manageUser"] = manageUser;
    return std::move(obj);
}