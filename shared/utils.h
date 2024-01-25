//
// Created by Liplum on 6/12/2023.
//

#ifndef SHARED_UTILS_H
#define SHARED_UTILS_H

#include <string>
#include <optional>

using namespace std;

string toLowercase(const string &str);

namespace ui {
    void clearScreen();

    int inputInt();

    double inputDouble();

    string inputString();

    optional<int> tryStoi(const std::string &input);
}
#endif //SHARED_UTILS_H
