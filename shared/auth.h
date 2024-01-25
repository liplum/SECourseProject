//
// Created by Liplum on 6/6/23.
//

#ifndef SHARED_AUTH_H
#define SHARED_AUTH_H

#include <utility>
#include <vector>
#include "string"
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

#endif //SHARED_AUTH_H
