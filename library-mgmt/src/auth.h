//
// Created by Liplum on 6/6/23.
//

#ifndef LIBRARYMGMT_AUTH_H
#define LIBRARYMGMT_AUTH_H

#include <utility>
#include <vector>
#include "string"
#include "../../shared/dirty.h"
#include "nlohmann/json.hpp"

#include "../../shared/auth.h"

// User type with hardcoded permissions
struct LibraryPermissionSet {
    bool manageBook = false;
    bool manageUser = false;

    explicit LibraryPermissionSet(
            bool manageBook = false,
            bool modifyUser = false
    ) : manageBook(manageBook),
        manageUser(modifyUser) {}

    explicit LibraryPermissionSet(const json &obj);

    static LibraryPermissionSet admin() {
        return LibraryPermissionSet(true, true);
    }

    json toJson() const;
};

#endif //LIBRARYMGMT_AUTH_H
