#include <iostream>
#include <string>
#include "Models/User/User.h"
#include "Models/Mails/Mail.h"

#include <windows.h>
using namespace std;

void PrintMenu() {
    cout << "\n=== Тестовое меню ===\n";
    cout << "1. Создать пользователя\n";
    cout << "2. Написать письмо (в файл)\n";
    cout << "3. Прочитать письмо (из файла)\n";
    cout << "0. Выход\n";
    cout << "Выберите пункт: ";
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    User* user = nullptr; // пока пользователя нет
    Mail mail;
    bool running = true;

    while (running) {
        PrintMenu();
        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            delete user;         // если уже был, очищаем
            user = new User();   // вызовется твой конструктор с вводом логина/пароля
            cout << "✅ Пользователь создан\n";
            break;
        }
        case 2:
            mail.send_mail(); // письмо сохраняется в файл
            break;
        case 3:
            mail.get_mails();  // письмо читается из файла
            mail.PrintInfo();  // вывод на экран
            break;
        case 0:
            running = false;
            cout << "👋 Выход...\n";
            break;
        default:
            cout << "❌ Неверный выбор\n";
        }
    }

    delete user; // освобождаем память
    return 0;
}

