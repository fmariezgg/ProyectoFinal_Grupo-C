#include "../headers/funciones_externas.h"
using namespace std;

//implementaciones de todas las funciones del modulo de gestion de vacas:
//***************************************************************************************************

int buscar_Vaca(const char id[ID]) {
    bool leer = leer_Archivos("registro_Vacas.txt");
    if (!leer) return -2; //-2 significa que no se pudo leer el archivo
    
    for (int i = 0; i < num_vacas; i++) {
        if (strcmp(registro_Vacas[i].id, id) == 0) return i;
    }
    
    return -1; //si no se ha retornado, significa que no se encontro el id
}

//***************************************************************************************************

bool registrar_Vacas(int num) {
    system("cls || clear");
    bool leer = false, escribir = false;
    char tempID[ID] = "";

    leer = leer_Archivos("registro_Vacas.txt");
    if (!leer) return false;

    for (int i = 0; i < num; i++) {
        LLC::_colSET(LLC::cCYAN);
        cout << endl << "                                  Vaca #" << num_vacas+1 << ":" << endl;
        cout << "   ***********************************************************************\n";
        LLC::_colRESET();
        
        while (true) { //checkear que el ID no este registrado
            pedir_Cstring("ID", tempID, ID);

            if (buscar_Vaca(tempID) >= 0) {
                LLC::_colSET(LLC::cRED);
                cout << "   ERROR: ID ya registrado...";
                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(1500));
                continue;
            } else if (buscar_Vaca(tempID) == -1) {
                strcpy(registro_Vacas[num_vacas].id, tempID);
                break;
            } else if (buscar_Vaca(tempID) == -2) return false;
        }

        registro_Vacas[num_vacas].edad = pedir_int("edad (en años)");
        registro_Vacas[num_vacas].prod_diaria = pedir_int("producción diaria (en galones)");
        pedir_Cstring("estado de salud", registro_Vacas[num_vacas].estado_salud);
        num_vacas++;
    }

    escribir = escribir_Archivos("registro_Vacas.txt");
    if (!escribir) return false;

    cout << "   ";
    this_thread::sleep_for(chrono::milliseconds(500));
    LLC::_colRESET();
    return true; //si no se ha retornado, significa que las operaciones de leer y escribir funcionaron bien y se guardaron los datos
}

//***************************************************************************************************

bool mostrar_Vacas() {
    system("cls || clear");
    bool leer = leer_Archivos("registro_Vacas.txt");
    if (!leer) return false;

    if (checkear_Vacio(num_vacas)) return true; //checkea si esta vacio el registro

    LLC::_colSET(LLC::cGREEN);
    cout << "\n   Mostrando vacas registradas...";
    this_thread::sleep_for(chrono::milliseconds(800));

    cout << endl;
    for (int i = 0; i < num_vacas; i++) {
        LLC::_colSET(LLC::cCYAN);
        cout << endl << "                                  Vaca #" << i+1 << ":" << endl;
        cout << "   ***********************************************************************\n";
        LLC::_colSET(LLC::cLIGHT_YELLOW);
        cout << "   ID: " << registro_Vacas[i].id << "\n";
        cout << "   Edad: " << registro_Vacas[i].edad << " año(s)\n";
        cout << "   Producción diaria: " << registro_Vacas[i].prod_diaria << " galón(es)\n";
        cout << "   Estado de salud: " << registro_Vacas[i].estado_salud << endl;
        cout << "   ";
        this_thread::sleep_for(chrono::milliseconds(800));
    }

    LLC::_colSET(LLC::cCYAN);
    cout << endl << "   ***********************************************************************\n";
    cout << "   Presione cualquier tecla para continuar...";

    //para no usar system("pause"), primero se limpia el ultimo caracter en el buffer y se espera a que el usuario presione una tecla
    if (cin.peek() == '\n') cin.ignore();
    cin.get();
    LLC::_colRESET();
    return true;
}

//***************************************************************************************************

bool editar_Vaca() {
    system("cls || clear");
    bool leer = false, escribir = false;
    int indice = 0, info = 0;
    char id[ID] = "";

    leer = leer_Archivos("registro_Vacas.txt");
    if (!leer) return false;
    if (checkear_Vacio(num_vacas)) return true;

    cout << endl;
    pedir_Cstring("ID de la vaca a editar", id, ID);
    indice = buscar_Vaca(id);

    LLC::_colSET(LLC::cTEAL);
    cout << "\n   Buscando vaca...";
    this_thread::sleep_for(chrono::milliseconds(800));
    LLC::_colRESET();

    if (indice == -1) {
        LLC::_colSET(LLC::cRED);
        cout << "\n   ERROR: ID ingresado no esta registrado...";
        this_thread::sleep_for(chrono::milliseconds(2250));
        LLC::_colRESET();
        return true;
    } else if (indice == -2) return false;

    else if (indice >= 0) {
        LLC::_colSET(LLC::cGREEN);
        cout << "\n   Vaca encontrada!";
        this_thread::sleep_for(chrono::milliseconds(750));
        LLC::_colSET(LLC::cCYAN);
        cout << endl << "\n                                  Vaca #" << indice+1 << ":" << endl;
        cout << "   ***********************************************************************";
        do {
            LLC::_colSET(LLC::cLIGHT_YELLOW);
            cout << "\n\n   ¿Qué información quiere editar?" << endl;
            cout << "   1. Edad\n   2. Producción diaria\n   3. Estado de salud\n";
            LLC::_colSET(LLC::cTEAL);
            cout << "   Ingrese su opción: ";
            cin >> info;

            cout << endl;
            LLC::_colRESET();
            switch (info) {
                case 1:
                    registro_Vacas[indice].edad = pedir_int("edad (en años)");
                    break;
                case 2:
                    registro_Vacas[indice].edad = pedir_int("producción diaria (en galones)");
                    break;
                case 3:
                    pedir_Cstring("estado de salud", registro_Vacas[indice].estado_salud);
                    break;
                default:
                    LLC::_colSET(LLC::cRED);
                    cout << "   Opción inválida...";
                    this_thread::sleep_for(chrono::milliseconds(1000));
                    LLC::_colRESET();
                    break;
            }
        } while (info < 1 || info > 3);

        cout << "   "; this_thread::sleep_for(chrono::milliseconds(500));
        LLC::_colSET(LLC::cGREEN);
        escribir = escribir_Archivos("registro_Vacas.txt");
        if (escribir) {
            LLC::_colSET(LLC::cGREEN);
            cout << "\n   ***********************************************************************";
            cout << "\n                              Vaca editada...";
        } else return false;
        
        this_thread::sleep_for(chrono::milliseconds(2250));
        LLC::_colRESET();
    }

    return true;
}

//***************************************************************************************************

int eliminar_Vaca(const char id[ID]) {
    int indice = 0;
    bool leer = false, escribir = false;

    leer = leer_Archivos("registro_Vacas.txt");
    if (!leer) return -2;
    if (checkear_Vacio(num_vacas)) return 1;

    indice = buscar_Vaca(id);
    if (indice < 0) return indice;

    for (int i = indice; i < num_vacas-1; i++) {
        registro_Vacas[i] = registro_Vacas[i+1];
    } num_vacas--;

    escribir = escribir_Archivos("registro_Vacas.txt");
    if (escribir) return 0;
    else return -2;
}

//***************************************************************************************************