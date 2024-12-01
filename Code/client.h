#include <iostream>
#include "password_auth.h"
#include <cstring>
#include"login.h"

class Client    {
    std :: string username, password;
    int ch;
    int option;
    char before_food;
    std ::string medname, time, day, quantity, choice;
    bool before = false;
    public :
        void registration();
        void login();
        void logout();
        void addMedicine();
        std :: string getUsername();
        std :: string getPassword();
        std :: string getMedname();
        std :: string getDay();
        std :: string getTime();
        bool getBefore();
        std :: string getQuantity();
};