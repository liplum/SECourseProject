//
// Created by Liplum on 6/12/2023.
//

#ifndef SHARED_UTILS_H
#define SHARED_UTILS_H

#include <string>
#include <functional>
#include <filesystem>
#include <optional>
#include <iostream>

using namespace std;
namespace fs = std::filesystem;

string toLowercase(const string &str);

void createParentFolders(const fs::path &filePath);

optional<int> tryStoi(const std::string &input);

namespace ui {
    void clearScreen();

    int inputInt();

    double inputDouble();

    string inputString();

    template<typename T>
    class InputBox {
    private:
        T (*input)();

        function<bool(T)> test;

        string errorPrompt;
    public:
        explicit InputBox(
                T (*input)(),
                function<bool(T)> test, const std::string &errorPrompt
        ) : input(input), test(test), errorPrompt(errorPrompt) {}

        T getInput(const string &name) {
            while (true) {
                cout << "Enter " << name << ": ";
                T t = input();
                if (!test(t)) {
                    cout << "Invalid " << name << "." << errorPrompt << endl;
                    continue;
                }
                return t;
            }
        }
    };

    template<typename T>
    InputBox<T> positiveInputBox(T (*input)()) {
        return InputBox<T>(input, [](T value) { return value > 0; }, "Input must be positive.");
    }

    template<typename T>
    InputBox<T> nonNegativeInputBox(T (*input)()) {
        return InputBox<T>(input, [](T value) { return value >= 0; }, "Input must not be negative.");
    }
}
#endif //SHARED_UTILS_H
