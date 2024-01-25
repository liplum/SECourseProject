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
    return std::move(obj);
}

Book::Book(const json &obj) {
    id = obj["id"];
    name = obj["name"];
}
