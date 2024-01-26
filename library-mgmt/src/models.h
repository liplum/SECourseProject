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
            string name,
            int collection,
            int rest
    ) :
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
    string userAccount;
    int bookId;

    BookRent() = default;

    explicit BookRent(
            const string &userAccount,
            int bookId
    ) :
            userAccount(std::move(userAccount)),
            bookId(bookId) {
    }

    explicit BookRent(const json &obj);

    json toJson() const;
};

#endif //LIBRARYMGMT_MODELS_H
