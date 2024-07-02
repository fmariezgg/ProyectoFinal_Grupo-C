#include "menus.cpp"
using namespace std;

/*
-- agregar opcion de que se pueda ingresar fecha manualmente
-- validar id's para que no se repitan
-- cuando se ingrese una venta de un cliente que no esta registrado, avisarle al usuario que lo registre primero
*/

int main() {
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