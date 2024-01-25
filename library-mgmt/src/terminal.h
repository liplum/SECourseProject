//
// Created by Liplum on 6/8/23.
//

#ifndef LIBRARYMGMT_TERMINAL_H
#define LIBRARYMGMT_TERMINAL_H

#include <utility>

#include <string>
#include "models.h"
#include "auth.h"
#include "../../shared/terminal.h"

using namespace std;
namespace ui {
    class Terminal : public BasicTerminal<LibraryPermissionSet> {
    public:
        const string userDbPath;
        const string productDbPath;
        DataSet<Product> *products;
        Menu mainMenu{"Main Menu"};
        Menu userMenu{"User Management"};
        Menu bookMenu{"Book Management"};

        Terminal(const string &userDbPath, const string &bookDbPath);

        ~Terminal();

        void saveAll();

        void initMenu();

        void start();
    };
}

#endif //LIBRARYMGMT_TERMINAL_H
