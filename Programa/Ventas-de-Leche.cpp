#include "menus.cpp"
using namespace std;

int main() {
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); //si se esta ejecutando en windows, se cambia el output a UTF-8 para que se impriman los tildes
    #endif

    int start = 0;

    do {
        system("cls || clear");
        start = start_screen();

        if (start == 1) {
            int acceder = 0;
            LLC::_colSET(LLC::cLIGHT_YELLOW);
            cout << "      Abriendo menú...";
            LLC::_colRESET();
            this_thread::sleep_for(chrono::milliseconds(1000));

            while (acceder != 4) acceder = principal();

        } else if (start == 2) {
            LLC::_colSET(LLC::cRED);
            cout << "      Cerrando programa...";
            LLC::_colRESET();
            break;
        } else {
            LLC::_colSET(LLC::cRED);
            cout << "      Opción inválida...";
            LLC::_colRESET();
            this_thread::sleep_for(chrono::milliseconds(1000));
            continue;
        }

    } while (start != 2);

    this_thread::sleep_for(chrono::milliseconds(1500));
    cout << endl;
    return 0;
}