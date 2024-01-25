//
// Created by Liplum on 1/25/24.
//

#ifndef SHARED_MODEL_H
#define SHARED_MODEL_H

#include <utility>
#include <string>
#include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

template<typename T>
concept IToJson = requires(T per)
{
    { per.toJson() } -> std::same_as<json>;
};

template<typename T>
concept IIdentifiable = requires(T per)
{
    { per.id } -> std::same_as<int>;
};

template<typename T>
concept INamed = requires(T per)
{
    { per.name } -> std::same_as<string>;
};


#endif //SHARED_MODEL_H
