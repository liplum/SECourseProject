//
// Created by Liplum on 1/25/24.
//

#include "models.h"
#include "nlohmann/json.hpp"
#include "../../shared/utils.h"
#include <fstream>
#include <iomanip>
#include <utility>

#include <algorithm> // for std::transform
#include <sstream> // for std::istringstream

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

optional<Book> BookSet::findById(int id) {
    for (auto &product: products) {
        if (product.id == id) {
            return product;
        }
    }
    return nullopt;
}

vector<Product> ProductSet::findByName(const string &query) {
    // Convert the search query to lowercase for case-insensitive matching
    // Split the query into separate conditions
    istringstream iss(toLowercase(query));
    vector<string> conditions;
    copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(conditions));

    vector<Product> foundProducts;
    for (auto &product: products) {
        // Convert the product query to lowercase for case-insensitive matching
        auto productName = toLowercase(product.name);

        // Check if all conditions are satisfied
        bool allConditionsSatisfied = true;
        for (const auto &condition: conditions) {
            if (condition == "*") {
                continue;
            }
            if (productName.find(condition) == string::npos) {
                allConditionsSatisfied = false;
                break;
            }
        }

        // If all conditions are satisfied, add the product to the result
        if (allConditionsSatisfied) {
            foundProducts.push_back(product);
        }
    }

    return std::move(foundProducts);
}

int ProductSet::addProduct(const string &name, double price, double discount, double premiumPrice) {
    int id = curId++;
    products.emplace_back(id, name, price, discount, premiumPrice);
    markDirty();
    return id;
}

bool ProductSet::removeProductById(int prod) {
    for (auto it = products.begin(); it != products.end(); ++it) {
        if (it->id == prod) {
            products.erase(it);
            markDirty();
            return true;
        }
    }
    return false;
}

bool ProductSet::updateProduct(Product &product) {
    for (auto &p: products) {
        if (p.id == product.id) {
            if (
                    p.name != product.name ||
                    p.price != product.price ||
                    p.discount != product.discount ||
                    p.premiumPrice != product.premiumPrice
                    ) {
                p = product; // Update the product
                markDirty();
            }
            return true;
        }
    }
    return false; // Product not found
}

vector<Product> ProductSet::getProducts() {
    return products;
}

void writeProductList(json &arr, const vector<Product> &products) {
    for (const auto &product: products) {
        arr.push_back(product.toJson());
    }
}

// Function to serialize products to JSON file
bool ProductSet::saveToFile(const string &filename) {
    json root;
    root["curId"] = curId;
    writeProductList(root["products"], products);

    ofstream file(filename);
    if (file.is_open()) {
        file << setw(2) << root << endl;
        return true;
    } else {
        return false;
    }
}

void readProductListFromJson(const json &arr, vector<Product> &in) {
    for (const auto &obj: arr) {
        in.emplace_back(obj);
    }
}

// Function to load products from JSON file
ProductSet::ProductSet(const string &filename) {
    ifstream file(filename);
    if (file.is_open()) {
        json jsonData;
        file >> jsonData;
        curId = jsonData["curId"];
        readProductListFromJson(jsonData["products"], products);
    }
    // ignore missing file
    file.close();
}
