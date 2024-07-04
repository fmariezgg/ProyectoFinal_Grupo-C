#include "menus.cpp"
using namespace std;
using namespace LLC;

int main() {
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); //si se esta ejecutando en windows, se cambia el output a UTF-8 para que se impriman los tildes
    #endif

    int start = 0;

    do {
        system("cls || clear");
        start = start_screen(); //iniciar el programa

        if (start == 1) {
            int acceder = 0;
            _colSET(cLIGHT_YELLOW);
            cout << "      Abriendo menú...";
            _colRESET();
            Sleep(1000);

            while (acceder != 4) acceder = principal(); //mientras no se quiera regresar a la pantalla principal

        } else if (start == 2) {
            _colSET(cRED);
            cout << "      Cerrando programa...";
            _colRESET();
            break;
        } else {
            _colSET(cRED);
            cout << "      Opción inválida...";
            _colRESET();
            Sleep(1000);
            continue;
        }

    } while (start != 2); //mientras no se quiera cerrar el programa

    Sleep(2250);
    return 0;
}