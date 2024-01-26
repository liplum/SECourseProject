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
    int collection;
    int rest;

    Book() = default;

    explicit Book(const json &obj);

    explicit Book(
            int id,
            string name,
            int collection,
            int rest
    ) : id(id),
        name(std::move(name)),
        collection(collection),
        rest(rest) {
    }

    [[nodiscard]]
    json toJson() const;
};

class BookRent {
public:
    int id{0};
    int userId{0};
    vector<int> books;

    BookRent() = default;

    explicit BookRent(
            int id,
            int userId,
            vector<int> books
    ) : id(id),
        userId(userId),
        books(books) {
    }

    explicit BookRent(const json &obj);

    json toJson() const;
};

#endif //LIBRARYMGMT_MODELS_H
