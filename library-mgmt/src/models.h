//
// Created by Liplum on 1/25/24.
//

#ifndef LIBRARYMGMT_MODELS_H
#define LIBRARYMGMT_MODELS_H

#include <string>
#include <utility>
#include <vector>
#include "nlohmann/json.hpp"
#include "../../shared/dirty.h"

using namespace std;
using json = nlohmann::json;

// Product class to store product information
class Book {
public:
    int id{0};
    string name;

    Book() = default;

    explicit Book(const json &obj);

    explicit Book(
            int id,
            string name
    ) : id(id),
        name(std::move(name)) {
    }

    [[nodiscard]]
    json toJson() const;
};

#endif //LIBRARYMGMT_MODELS_H
