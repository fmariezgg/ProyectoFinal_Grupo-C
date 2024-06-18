#include <iostream>
#include <windows.h>
#include "menus.cpp"
using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    int start = 0;

    do {
        system("cls || clear");
        start = start_screen();

        if (start == 1) {
            int acceder = 0;
            cout << "Abriendo menú...";
            Sleep(1000);

            while (acceder != 7) acceder = principal();

        } else if (start == 2) {
            cout << "Cerrando programa...";
            break;
        } else {
            cout << "\nOpción inválida...";
            Sleep(1000);
            continue;
        }

    } while (start != 2); 

    Sleep(1250);
    cout << "\n";
    return 0;
}