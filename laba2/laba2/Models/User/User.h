#pragma once
#include <iostream>
#include <string>
#include "../Mails/Mail.h"
using namespace std;

class USER {
public:
    std::string name;
    std::string surname;
    unsigned int age;
    std::string login;
    std::string password;

};

class User : public USER {
public: 
    User() {
        cout << "Enter user login:";
        cin >> this->login;

        cout << endl << "Enter user password: ";
        cin >> this->password;
        cout << endl;
    }
    Mail mails[10];

};

class Admin : public USER {
public:
    Admin() {
        cout << "Enter Admin login: ";
        cin >> this->login;

        cout << endl << "Enter Admin password: ";
        cin >> this->password;
        cout << endl;
    }
};
