//
// Created by Liplum on 1/25/24.
//

#include "auth.h"

LibraryPermissionSet LibraryPermissionSet::all() {
    return LibraryPermissionSet(true, true);
}

LibraryPermissionSet::LibraryPermissionSet(const json &obj) {
    manageBook = obj["manageBook"];
    manageUser = obj["manageUser"];
}

json LibraryPermissionSet::toJson() const {
    json obj;
    obj["manageBook"] = manageBook;
    obj["manageUser"] = manageUser;
    return std::move(obj);
}