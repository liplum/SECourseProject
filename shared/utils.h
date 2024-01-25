//
// Created by Liplum on 6/12/2023.
//

#ifndef SHARED_UTILS_H
#define SHARED_UTILS_H

#include <string>
using namespace std;

string toLowercase(const string &str);

namespace ui {
    void clearScreen();

    int inputInt();

    double inputDouble();

    string inputString();
}
#endif //SHARED_UTILS_H
