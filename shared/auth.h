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


template<typename T>
concept IPermission = JsonSerializable<T> && requires
{
    { T() } -> std::same_as<T>;
    { T::all() } -> std::same_as<T>;
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

template<typename TPer> requires IPermission<TPer>
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
requires JsonSerializable<TPer>
void writeUserList(json &arr, const vector<User<TPer>> &users) {
    for (const auto &user: users) {
        arr.push_back(user.toJson());
    }
}

template<typename TPer>
requires JsonSerializable<TPer>
void readUserListFromJson(const json &arr, vector<User<TPer>> &in) {
    for (const auto &obj: arr) {
        in.emplace_back(obj);
    }
}

namespace ui {
    template<typename TPer>
    requires JsonSerializable<TPer>
    bool addUser(Auth <TPer> &auth, TPer inputPermission()) {
        cout << "Enter the account name: ";
        auto account = inputString();

        auto existingUser = auth.findUserByAccount(account);
        if (existingUser.has_value()) {
            cout << "User with the same account already exists." << endl;
            return false;
        }

        cout << "Enter the password: ";
        auto password = inputString();

        auto permission = inputPermission();

        if (auth.addUser(account, password, permission)) {
            cout << "User added successfully." << endl;
            return true;
        } else {
            cout << "Failed to add user." << endl;
            return false;
        }
    }

    template<typename TPer>
    requires JsonSerializable<TPer>
    bool modifyUser(Auth <TPer> &auth, TPer inputPermission()) {
        cout << "Enter the account of the user to modify: ";
        auto account = inputString();

        auto user = auth.findUserByAccount(account);
        if (!user.has_value()) {
            cout << "User not found." << endl;
            return false;
        }

        User<TPer> &targetUser = user.value();

        // Prevent modifying the account.
        cout << "Modifying user: " << targetUser.account << endl;

        cout << "Enter the new password (leave empty to keep current password): ";
        auto newPassword = inputString();

        if (!newPassword.empty()) {
            targetUser.password = newPassword;
        }

        auto permission = inputPermission();
        targetUser.permission = permission;

        if (auth.updateUser(targetUser)) {
            cout << "User modified successfully." << endl;
            return true;
        } else {
            cout << "Failed to modify user." << endl;
            return false;
        }
    }

    template<typename TPer>
    requires JsonSerializable<TPer>
    bool deleteUser(Auth <TPer> &auth, User <TPer> &curUser) {
        cout << "Enter the account of the user to delete: ";
        auto account = inputString();

        if (account == curUser.account) {
            cout << "Cannot delete the current user." << endl;
            return false;
        }

        auto user = auth.findUserByAccount(account);
        if (!user.has_value()) {
            cout << "User not found." << endl;
            return false;
        }

        cout << "Ensure to delete user " << user->account << "?";
        bool ensure = inputInt();
        if (!ensure) {
            return false;
        }

        if (auth.removeUserByAccount(account)) {
            cout << "User deleted successfully." << endl;
            return true;
        } else {
            cout << "Failed to delete user." << endl;
            return false;
        }
    }

    template<typename TPer> requires JsonSerializable<TPer>
    vector<User < TPer>>
    searchUser(Auth<TPer>
    &auth) {
    cout << "Enter the account or wildcard(*) to search: ";
    vector<User < TPer>>
    result;
    string account = inputString();
    if (account == "*") {
    for (
    auto &user
    : auth.

    getUsers()

    ) {
    result.
    push_back(user);
}
} else {
auto user = auth.findUserByAccount(account);
if (user.

has_value()

) {
result.
push_back(user
.

value()

);
}
}
return
result;
}
}
#endif //SHARED_AUTH_H
