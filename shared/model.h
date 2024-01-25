//
// Created by Liplum on 1/25/24.
//

#ifndef SHARED_MODEL_H
#define SHARED_MODEL_H

#include <utility>
#include <string>
#include "nlohmann/json.hpp"
#include <fstream>
#include <iomanip>
#include "utils.h"
#include <algorithm> // for std::transform
#include <sstream> // for std::istringstream


using namespace std;
using json = nlohmann::json;

template<typename T>
concept JsonSerializable = requires(T t)
{
    { T(std::declval<json>()) } -> std::same_as<T>;
    { t.toJson() } -> std::same_as<json>;
};

template<typename T>
concept Identifiable = requires(T t)
{
    { t.id } -> std::same_as<int &>;
};

template<typename T>
concept Named = requires(T t)
{
    { t.name } -> std::same_as<string &>;
};

template<typename T> requires Identifiable<T> && Named<T> && JsonSerializable<T>
class DataSet : public DirtyMarkMixin {
private:
    int curId{0};
    vector<T> rows{};
public:
    DataSet() = default;

    // Function to load products from JSON file
    DataSet(const string &filename) {
        ifstream file(filename);
        if (file.is_open()) {
            json jsonData;
            file >> jsonData;
            curId = jsonData["curId"];
            readListFromJson(jsonData["rows"], rows);
        }
        // ignore missing file
        file.close();
    }

    optional<T> findById(int id) {
        for (auto &row: rows) {
            if (row.id == id) {
                return row;
            }
        }
        return nullopt;
    }

    /**
     * wildcard enabled.
     * @param query
     * @return
     */
    vector<T> findByName(const string &query) {
        // Convert the search query to lowercase for case-insensitive matching
        // Split the query into separate conditions
        istringstream iss(toLowercase(query));
        vector<string> conditions;
        copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(conditions));

        vector<T> foundProducts;
        for (auto &row: rows) {
            // Convert the product query to lowercase for case-insensitive matching
            auto productName = toLowercase(row.name);

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
                foundProducts.push_back(row);
            }
        }

        return std::move(foundProducts);
    }

    int addRow(T &row) {
        row.id = curId++;
        rows.emplace_back(row);
        markDirty();
        return row.id;
    }

    bool removeById(int id) {
        for (auto it = rows.begin(); it != rows.end(); ++it) {
            if (it->id == id) {
                rows.erase(it);
                markDirty();
                return true;
            }
        }
        return false;
    }

    bool update(T &row) {
        auto it = std::find_if(rows.begin(), rows.end(), [&row](const T &p) {
            return p.id == row.id;
        });

        if (it != rows.end()) {
            // Update the age in place
            *it = row;
            markDirty();
            return true;
        } else {
            // Product not found
            return false;
        }
    }

    bool saveToFile(const string &filename) const {
        json root;
        root["curId"] = curId;
        writeList(root["rows"], rows);

        ofstream file(filename);
        if (file.is_open()) {
            file << setw(2) << root << endl;
            return true;
        } else {
            return false;
        }
    }

    vector<T> getRows() {
        return rows;
    }
};

template<typename T>
requires JsonSerializable<T>
void readListFromJson(const json &arr, vector<T> &in) {
    for (const auto &obj: arr) {
        in.emplace_back(obj);
    }
}

template<typename T>
requires JsonSerializable<T>
void writeList(json &arr, const vector<T> &products) {
    for (const auto &product: products) {
        arr.push_back(product.toJson());
    }
}

#endif //SHARED_MODEL_H
