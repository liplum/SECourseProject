//
// Created by Liplum on 6/12/2023.
//

#ifndef SHARED_UTILS_H
#define SHARED_UTILS_H

#include <string>
#include <functional>
#include <optional>
#include <iostream>

using namespace std;

string toLowercase(const string &str) {
    string result;
    result.reserve(str.length());

#ifdef _WIN32
    for (auto c: str) {
      result.push_back(tolower(c));
    }
#else
    auto locale = std::locale();
    for (auto c: str) {
        result.push_back(tolower(c, locale));
    }
#endif

    return std::move(result);
}

namespace ui {
    void clearScreen() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    int inputInt() {
        int i;
        cin >> i;
        cin.ignore();
        return i;
    }

    double inputDouble() {
        double f;
        cin >> f;
        cin.ignore();
        return f;
    }

    string inputString() {
        string s;
        getline(cin, s);
        return std::move(s);
    }

    optional<int> tryStoi(const std::string &input) {
        try {
            return std::stoi(input);
        } catch (const std::invalid_argument &) {
            // Conversion failed due to invalid argument
            return std::nullopt;
        } catch (const std::out_of_range &) {
            // Conversion failed due to out of range
            return std::nullopt;
        }
    }

    template<typename T>
    class InputValidator {
    public:
        function<bool(T)> test;

        string errorPrompt;

        // Constructor that takes a lambda function and an error prompt
        explicit InputValidator(function<bool(T)> testFunc, const std::string &errorPrompt)
                : test(testFunc), errorPrompt(errorPrompt) {
        }
    };

    template<typename T>
    class InputBox {
    private:
        T (*input)();

        vector<InputValidator<T>> validators;;
    public:
        explicit InputBox(
                T (*input)(),
                initializer_list<InputValidator<T>> validators
        ) : input(input), validators(validators) {}

        T getInput(const string &name, ...) {
            while (true) {
                cout << "Enter " << name << " :";
                T t = input();
                for (auto &validator: validators) {
                    if (!validator.test(t)) {
                        cout << "Invalid " << name << "." << validator.errorPrompt << endl;
                    }
                }
                return t;
            }
        }
    };

    template<typename T>
    InputValidator<T> positiveValidator() {
        return InputValidator(
                function<bool(T)>([](T value) { return value > 0; }),
                "Input must be positive."
        );
    }

    template<typename T>
    InputValidator<T> nonNegativeValidator() {
        return InputValidator(
                function<bool(T)>([](T value) { return value >= 0; }),
                "Input must not be negative."
        );
    }

    InputBox<int> intInputBox(initializer_list<InputValidator<int>> validators) {
        return InputBox<int>(inputInt, validators);
    }

    InputBox<double> doubleInputBox(initializer_list<InputValidator<double>> validators) {
        return InputBox<double>(inputDouble, validators);
    }
}
#endif //SHARED_UTILS_H
