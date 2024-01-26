//
// Created by Liplum on 1/25/24.
//

#include "models.h"
#include "nlohmann/json.hpp"
#include <utility>

using namespace std;

json Book::toJson() const {
    json obj;
    obj["id"] = id;
    obj["name"] = name;
    obj["collection"] = collection;
    obj["rest"] = rest;
    return std::move(obj);
}

Book::Book(const json &obj) {
    id = obj["id"];
    name = obj["name"];
    collection = obj["collection"];
    rest = obj["rest"];
}

json BookRent::toJson() const {
    json obj;
    obj["id"] = id;
    obj["userAccount"] = userAccount;
    obj["bookId"] = bookId;
    return std::move(obj);
}

BookRent::BookRent(const json &obj) {
    id = obj["id"];
    userAccount = obj["userAccount"];
    bookId = obj["bookId"];
}
