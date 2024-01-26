//
// Created by Liplum on 6/12/2023.
//

#include "utils.h"
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

void createParentFolders(const fs::path &filePath) {
    fs::path parentPath = filePath.parent_path();

    // Check if the parent path exists
    if (!fs::exists(parentPath)) {
        // Create the parent folders recursively
        std::error_code ec;  // Used to check for errors
        fs::create_directories(parentPath, ec);

        // Check for errors during creation
        if (ec) {
            std::cerr << "Error creating directories: " << ec.message() << std::endl;
        }
    }
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
}
