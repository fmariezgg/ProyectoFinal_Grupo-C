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
            cambiar_color(14);
            cout << "      Abriendo menú...";
            resetear_color();
            Sleep(1000);

            while (acceder != 4) acceder = principal();

        } else if (start == 2) {
            cambiar_color(12);
            cout << "      Cerrando programa...";
            resetear_color();
            break;
        } else {
            cambiar_color(12);
            cout << "      Opción inválida...";
            resetear_color();
            Sleep(1000);
            continue;
        }

    } while (start != 2);

    Sleep(1250);
    cout << endl;
    return 0;
}