//
// Created by Liplum on 6/8/23.
//

#ifndef PRODMGMT_TERMINAL_H
#define PRODMGMT_TERMINAL_H

#include <utility>

#include <string>
#include "product.h"
#include "auth.h"
#include "../../shared/terminal.h"

using namespace std;
namespace ui {
    class Terminal {
    private:
        KUser *curUser{nullptr};

    public:
        static const int maxAttempts = 3;
        const string userDbPath;
        const string productDbPath;
        ProductSet *products;
        KAuth *auth;
        Menu mainMenu{"Main Menu"};
        Menu userMenu{"User Management"};

        Terminal(const string &userDbPath, const string &productDbPath);

        ~Terminal();

        void saveAll();

        void initMenu();

        bool login();

        void start();
    };
}

#endif //PRODMGMT_TERMINAL_H
