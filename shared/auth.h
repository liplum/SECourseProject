//
// Created by Liplum on 6/6/23.
//

#ifndef SHARED_AUTH_H
#define SHARED_AUTH_H

#include <utility>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "dirty.h"
#include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

template<typename TPer>
concept IPermission = requires(TPer per)
{
    { per.toJson() } -> std::same_as<json>;
};

template<typename TPer> requires IPermission<TPer>
struct User {
    string account;
    string password;
    TPer permission;

    User() = default;

    explicit User(
            string account,
            string password,
            const TPer &permission
    ) : account(std::move(account)),
        password(std::move(password)),
        permission(permission) {
    }

    explicit User(const json &obj);

    json toJson() const;
};

template<typename TPer> requires IPermission<TPer>
class Auth : public DirtyMarkMixin {
private:
    vector<User<TPer>> users;
public:
    Auth() = default;

    explicit Auth(const string &filename);

    optional<User<TPer>> findUserByAccount(const string &account);

    bool addUser(const string &account, const string &password, const TPer &permission);

    bool removeUserByAccount(const string &account);

    bool updateUser(User<TPer> &user);

    bool saveToFile(const string &filename);

    vector<User<TPer>> getUsers();
};

template<typename TPer>
requires IPermission<TPer>
User<TPer>::User(const json &obj) {
    account = obj["account"];
    password = obj["password"];
    permission = TPer(obj["permission"]);
}

template<typename TPer>
requires IPermission<TPer>
json User<TPer>::toJson() const {
    json obj;
    obj["account"] = account;
    obj["password"] = password;
    obj["permission"] = permission.toJson();
    return std::move(obj);
}

template<typename TPer>
requires IPermission<TPer>
vector<User<TPer>> Auth<TPer>::getUsers() {
    return users;
}

template<typename TPer>
requires IPermission<TPer>
optional<User<TPer>> Auth<TPer>::findUserByAccount(const string &account) {
    auto it = find_if(users.begin(), users.end(), [account](const User<TPer> &user) {
        return user.account == account;
    });

    if (it != users.end()) {
        return *it;
    } else {
        return nullopt;
    }
}

template<typename TPer>
requires IPermission<TPer>
bool Auth<TPer>::addUser(const string &account, const string &password, const TPer &permission) {
    if (!findUserByAccount(account).has_value()) {
        users.emplace_back(account, password, permission);
        markDirty();
        return true;
    } else {
        // already exists.
        return false;
    }
}

template<typename TPer>
requires IPermission<TPer>
bool Auth<TPer>::removeUserByAccount(const string &account) {
    for (auto it = users.begin(); it != users.end(); ++it) {
        if (it->account == account) {
            users.erase(it);
            markDirty();
            return true;
        }
    }
    return false;
}

template<typename TPer>
requires IPermission<TPer>
bool Auth<TPer>::updateUser(User<TPer> &user) {
    for (auto &u: users) {
        if (u.account == user.account) {
            if (u.password != user.password) {
                u = user; // Update the userMenu
                markDirty();
            }
            return true;
        }
    }
    return false; // User not found
}

template<typename TPer>
requires IPermission<TPer>
void writeUserList(json &arr, const vector<User<TPer>> &users) {
    for (const auto &user: users) {
        arr.push_back(user.toJson());
    }
}

template<typename TPer>
requires IPermission<TPer>
bool Auth<TPer>::saveToFile(const string &filename) {
    json root;
    writeUserList(root, users);

    ofstream file(filename);
    if (file.is_open()) {
        file << setw(2) << root << endl;
        return true;
    } else {
        return false;
    }
}

template<typename TPer>
requires IPermission<TPer>
void readUserListFromJson(const json &arr, vector<User<TPer>> &in) {
    for (const auto &obj: arr) {
        in.emplace_back(obj);
    }
}

template<typename TPer>
requires IPermission<TPer>
Auth<TPer>::Auth(const string &filename) {
    ifstream file(filename);
    if (file.is_open()) {
        json jsonData;
        file >> jsonData;
        readUserListFromJson(jsonData, users);
    }
    // ignore missing file
    file.close();
}

#endif //SHARED_AUTH_H