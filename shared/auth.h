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
#include "model.h"

using namespace std;

template<typename TPer> requires IToJson<TPer>
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

    explicit User(const json &obj) {
        account = obj["account"];
        password = obj["password"];
        permission = TPer(obj["permission"]);
    }

    json toJson() const {
        json obj;
        obj["account"] = account;
        obj["password"] = password;
        obj["permission"] = permission.toJson();
        return std::move(obj);
    }
};

template<typename TPer> requires IToJson<TPer>
class Auth : public DirtyMarkMixin {
private:
    vector<User<TPer>> users;
public:
    Auth() = default;

    Auth(const string &filename) {
        ifstream file(filename);
        if (file.is_open()) {
            json jsonData;
            file >> jsonData;
            readUserListFromJson(jsonData, users);
        }
        // ignore missing file
        file.close();
    }

    vector<User<TPer>> getUsers() {
        return users;
    }

    optional<User<TPer>> findUserByAccount(const string &account) {
        auto it = find_if(users.begin(), users.end(), [account](const User<TPer> &user) {
            return user.account == account;
        });

        if (it != users.end()) {
            return *it;
        } else {
            return nullopt;
        }
    }

    bool addUser(const string &account, const string &password, const TPer &permission) {
        if (!findUserByAccount(account).has_value()) {
            users.emplace_back(account, password, permission);
            markDirty();
            return true;
        } else {
            // already exists.
            return false;
        }
    }

    bool removeUserByAccount(const string &account) {
        for (auto it = users.begin(); it != users.end(); ++it) {
            if (it->account == account) {
                users.erase(it);
                markDirty();
                return true;
            }
        }
        return false;
    }

    bool updateUser(User<TPer> &user) {
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

    bool saveToFile(const string &filename) {
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

};

template<typename TPer>
requires IToJson<TPer>
void writeUserList(json &arr, const vector<User<TPer>> &users) {
    for (const auto &user: users) {
        arr.push_back(user.toJson());
    }
}

template<typename TPer>
requires IToJson<TPer>
void readUserListFromJson(const json &arr, vector<User<TPer>> &in) {
    for (const auto &obj: arr) {
        in.emplace_back(obj);
    }
}

#endif //SHARED_AUTH_H
