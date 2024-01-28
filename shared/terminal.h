#ifndef SHARED_TERMINAL_H
#define SHARED_TERMINAL_H

#include <utility>

#include <string>
#include "menu.h"
#include "utils.h"

using namespace std;
namespace ui {
    template<typename TPer> requires IPermission<TPer>
    class BasicTerminal {
    protected:
        optional<User<TPer>> curUser{nullopt};
        Auth<TPer> auth;
        static const int maxAttempts = 3;

    public:
        virtual void initMenu() = 0;

        virtual void start() = 0;

        virtual void saveAll() = 0;

        // Function to authenticate userMenu login
        optional<User<TPer>> tryLogin() {
            cout << "Enter account: ";
            auto account = inputString();
            cout << "Enter password: ";
            auto password = inputString();

            auto user = auth.findUserByAccount(account);

            if (user.has_value() && user->password == password) {
                cout << "Login successful." << endl;
                return user;
            } else {
                return nullopt;
            }
        }

        bool login() {
            // check if any user is available
            if (auth.getUsers().empty()) {
                auth.addUser("admin", "admin", TPer::admin());
                cout << "Because there's no user available for now, an administrator was created." << endl;
                cout << R"(account: "admin", password: "admin".)" << endl;
                saveAll();
            }

            int attempts = 0;
            while (attempts < maxAttempts) {
                auto user = tryLogin();
                if (user.has_value()) {
                    curUser = user;
                    return true;
                } else {
                    cout << "Invalid account or password. Please try again." << endl;
                    attempts++;
                }
            }
            return false;
        }
    };
}

#endif //SHARED_TERMINAL_H
