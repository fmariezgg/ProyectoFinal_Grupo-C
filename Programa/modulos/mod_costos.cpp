#include "../headers/funciones_externas.h"
using namespace std;
using namespace LLC;

//implementaciones de todas las funciones del modulo de gestion de costos (fijos + variables):

//aqui es el mismo cuento que con las funciones de clientes: las explicaciones estan en mod_vacas.cpp
//la unica diferencia que notar es que aunque la estructura de COSTO tiene un atributo de 'mes',
// no se ocupa para los costos fijos (pq son fijos) pero si para los variables
//***************************************************************************************************

int buscar_costo_Fijo(const char id[ID]) {
    for (int i = 0; i < num_costos_Fijos; i++) {
        if (strcmp(registro_costos_Fijos[i].id, id) == 0) return i;
    }
    
    return -1;
}

int buscar_costo_Variable(const char id[ID]) {
    for (int i = 0; i < num_costos_Variables; i++) {
        if (strcmp(registro_costos_Variables[i].id, id) == 0) return i;
    }
    
    return -1;
}

//***************************************************************************************************

bool registrar_costos_Fijos() {
    system("cls || clear");
    char tempID[ID] = "", input[3] = "";
    bool leer = false, escribir = false;

    leer = leer_Archivos("registro_costos_Fijos.txt");
    if (!leer) return false;

    do {
        _colSET(cCYAN);
        cout << endl << "                              Costo Fijo #" << num_costos_Fijos+1 << ":" << endl;
        cout << "   ***********************************************************************\n";
        _colRESET();

        while (true) {
            pedir_Cstring("ID", tempID, ID);

            if (buscar_costo_Fijo(tempID) >= 0) {
                _colSET(cRED);
                cout << "   ERROR: ID ya registrado...";
                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(1500));
                cout << endl;
                continue;
            } else if (buscar_costo_Fijo(tempID) == -1) {
                strcpy(registro_costos_Fijos[num_costos_Fijos].id, tempID);
                break;
            } else if (buscar_costo_Fijo(tempID) == -2) return false;
        }

        registro_costos_Fijos[num_costos_Fijos].monto = pedir_float("monto (en C$)");
        pedir_Cstring("descripción", registro_costos_Fijos[num_costos_Fijos].descripcion);
        num_costos_Fijos++;

        _colSET(cPINK);
        cout << "\n   ¿Desea registrar otra costo? (si/no): ";
        cin >> input;
    } while (((strcmp(input, "s") == 0) || (strcmp(input, "S") == 0) || (strcmp(input, "si") == 0) || (strcmp(input, "Si") == 0) || (strcmp(input, "sI") == 0) || (strcmp(input, "SI") == 0)));

    escribir = escribir_Archivos("registro_costos_Fijos.txt");
    if (!escribir) return false;

    cout << "   ";
    this_thread::sleep_for(chrono::milliseconds(500));
    _colRESET();
    return true;
}

bool registrar_costos_Variables() {
    system("cls || clear");
    char tempID[ID] = "", input[3] = "";
    bool leer = false, escribir = false;
    tm* time = obtener_fecha();

    leer = leer_Archivos("registro_costos_Variables.txt");
    if (!leer) return false;

    do {
        _colSET(cCYAN);
        cout << endl << "                            Costo Variable #" << num_costos_Variables+1 << ":" << endl;
        cout << "   ***********************************************************************\n";
        _colRESET();

        while (true) {
            pedir_Cstring("ID", tempID, ID);

            cout << tempID << endl;

            if (buscar_costo_Variable(tempID) >= 0) {
                _colSET(cRED);
                cout << "   ERROR: ID ya registrado...";
                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(1500));
                cout << endl;
                continue;
            } else if (buscar_costo_Variable(tempID) == -1) {
                cout << tempID << endl;
                strcpy(registro_costos_Variables[num_costos_Variables].id, tempID);
                break;
            } else if (buscar_costo_Variable(tempID) == -2) return false;
        }

        cout << registro_costos_Variables[num_costos_Variables].id << endl;

        registro_costos_Variables[num_costos_Variables].monto = pedir_float("monto (en C$)");
        pedir_Cstring("descripción", registro_costos_Variables[num_costos_Variables].descripcion);
        strcpy(registro_costos_Variables[num_costos_Variables].mes, meses[time->tm_mon]);
        num_costos_Variables++;

        _colSET(cPINK);
        cout << "\n   ¿Desea registrar otra costo? (si/no): ";
        cin >> input;
    } while (((strcmp(input, "s") == 0) || (strcmp(input, "S") == 0) || (strcmp(input, "si") == 0) || (strcmp(input, "Si") == 0) || (strcmp(input, "sI") == 0) || (strcmp(input, "SI") == 0)));

    escribir = escribir_Archivos("registro_costos_Variables.txt");
    if (!escribir) return false;

    cout << "   ";
    this_thread::sleep_for(chrono::milliseconds(500));
    _colRESET();
    return true;
}

//***************************************************************************************************

bool mostrar_costos_Fijos() {
    system("cls || clear");
    bool leer = leer_Archivos("registro_costos_Fijos.txt");
    if (!leer) return false;

    if (checkear_Vacio(num_costos_Fijos)) return true;

    _colSET(cGREEN);
    cout << "\n   Mostrando costos fijos registrados...";
    this_thread::sleep_for(chrono::milliseconds(800));

    cout << endl;
    for (int i = 0; i < num_costos_Fijos; i++) {
        _colSET(cCYAN);
        cout << endl << "                              Costo Fijo #" << i+1 << ":" << endl;
        cout << "   ***********************************************************************\n";
        _colSET(cLIGHT_YELLOW);
        cout << "   ID: " << registro_costos_Fijos[i].id << "\n";
        cout << "   Monto: C$" << registro_costos_Fijos[i].monto << "\n";
        cout << "   Descripción: " << registro_costos_Fijos[i].descripcion << endl;
        cout << "   ";
        this_thread::sleep_for(chrono::milliseconds(800));
    }

    _colSET(cCYAN);
    cout << endl << "   ***********************************************************************\n";
    cout << "   Presione 'Enter' para continuar...";
    cin.ignore();
    cin.get();
    _colRESET();
    return true;
}

bool mostrar_costos_Variables() {
    system("cls || clear");
    bool leer = leer_Archivos("registro_costos_Variables.txt");
    if (!leer) return false;

    if (checkear_Vacio(num_costos_Variables)) return true;

    _colSET(cGREEN);
    cout << "\n   Mostrando costos variables registrados...";
    this_thread::sleep_for(chrono::milliseconds(800));

    cout << endl;
    for (int i = 0; i < num_costos_Variables; i++) {
        _colSET(cCYAN);
        cout << endl << "                            Costo Variable #" << i+1 << ":" << endl;
        cout << "   ***********************************************************************\n";
        _colSET(cLIGHT_YELLOW);
        cout << "   ID: " << registro_costos_Variables[i].id << "\n";
        cout << "   Monto: C$" << registro_costos_Variables[i].monto << "\n";
        cout << "   Descripción: " << registro_costos_Variables[i].descripcion << "\n";
        cout << "   Mes: "; _colSET(cTEAL); cout << registro_costos_Variables[i].mes << endl;
        cout << "   ";
        this_thread::sleep_for(chrono::milliseconds(800));
    }

    _colSET(cCYAN);
    cout << endl << "   ***********************************************************************\n";
    cout << "   Presione 'Enter' para continuar...";
    cin.ignore();
    cin.get();
    _colRESET();
    return true;
}

//***************************************************************************************************

bool editar_costo_Fijo() {
    system("cls || clear");
    bool leer = false, escribir = false;
    int indice = 0, info = 0;
    char id[ID] = "";

    leer = leer_Archivos("registro_costos_Fijos.txt");
    if (!leer) return false;
    else if (checkear_Vacio(num_costos_Fijos)) return true;

    cout << endl;
    pedir_Cstring("ID del costo fijo a editar", id, ID);
    indice = buscar_costo_Fijo(id);

    _colSET(cTEAL);
    cout << "\n   Buscando costo fijo...";
    this_thread::sleep_for(chrono::milliseconds(800));
    _colRESET();

    if (indice == -1) {
        _colSET(cRED);
        cout << "\n   ERROR: ID ingresado no esta registrado...";
        this_thread::sleep_for(chrono::milliseconds(2250));
        _colRESET();
        return true;
    } else if (indice == -2) return false;

    else if (indice >= 0) {
        _colSET(cGREEN);
        cout << "\n   Costo fijo encontrado!";
        this_thread::sleep_for(chrono::milliseconds(500));
        _colSET(cCYAN);
        cout << endl << "\n                              Costo Fijo #" << indice+1 << ":" << endl;
        cout << "   ***********************************************************************";
        do {
            _colSET(cLIGHT_YELLOW);
            cout << "\n\n   ¿Qué información quiere editar?" << endl;
            cout << "   1. Monto\n   2. Descripción\n";
            _colSET(cTEAL);
            cout << "   Ingrese su opción: ";
            cin >> info;

            cout << endl;
            _colRESET();
            switch (info) {
                case 1:
                    registro_costos_Fijos[indice].monto = pedir_float("monto (en C$)");
                    break;
                case 2:
                    pedir_Cstring("descripción", registro_costos_Fijos[indice].descripcion);
                    break;
                default:
                    _colSET(cRED);
                    cout << "   Opción inválida...";
                    this_thread::sleep_for(chrono::milliseconds(1000));
                    _colRESET();
                    break;
            }
        } while (info < 1 || info > 2);

        cout << "   ";
        this_thread::sleep_for(chrono::milliseconds(500));
        escribir = escribir_Archivos("registro_costos_Fijos.txt");
        if (escribir) {
            _colSET(cGREEN);
            cout << "\n   ***********************************************************************";
            cout << "\n                          Costo fijo editado...";
        } else return false;
        
        this_thread::sleep_for(chrono::milliseconds(2250));
        _colRESET();
    }

    return true;
}

bool editar_costo_Variable() {
    system("cls || clear");
    bool leer = false, escribir = false;
    int indice = 0, info = 0;
    char id[ID] = "";

    leer = leer_Archivos("registro_costos_Variables.txt");
    if (!leer) return false;
    else if (checkear_Vacio(num_costos_Variables)) return true;

    cout << endl;
    pedir_Cstring("ID del costo variable a editar", id, ID);
    indice = buscar_costo_Variable(id);

    _colSET(cTEAL);
    cout << "\n   Buscando costo variable...";
    this_thread::sleep_for(chrono::milliseconds(800));
    _colRESET();

    if (indice == -1) {
        _colSET(cRED);
        cout << "\n   ERROR: ID ingresado no esta registrado...";
        this_thread::sleep_for(chrono::milliseconds(2250));
        _colRESET();
        return true;
    } else if (indice == -2) return false;

    else if (indice >= 0) {
        _colSET(cGREEN);
        cout << "\n   Costo variable encontrado!";
        this_thread::sleep_for(chrono::milliseconds(500));
        _colSET(cCYAN);
        cout << endl << "\n                            Costo Variable #" << indice+1 << ":" << endl;
        cout << "   ***********************************************************************";
        do {
            _colSET(cLIGHT_YELLOW);
            cout << "\n\n   ¿Qué información quiere editar?" << endl;
            cout << "   1. Monto\n   2. Descripción\n   3. Mes\n";
            _colSET(cTEAL);
            cout << "   Ingrese su opción: ";
            cin >> info;

            cout << endl;
            _colRESET();
            switch (info) {
                case 1:
                    registro_costos_Variables[indice].monto = pedir_float("monto (en C$)");
                    break;
                case 2:
                    pedir_Cstring("descripción", registro_costos_Variables[indice].descripcion);
                    break;
                case 3:
                    while (true) { //mientras no se ingrese mes valido, seguir pidiendolo
                        pedir_Cstring("mes", registro_costos_Variables[indice].mes, ID);

                        if (!checkear_mes(registro_costos_Variables[indice].mes)) {
                            _colSET(cRED);
                            cout << "   ERROR: Mes inválido...";
                            _colRESET();
                            this_thread::sleep_for(chrono::milliseconds(1500));
                            cout << endl;
                            continue;
                        } else break;
                    }

                    break;
                default:
                    _colSET(cRED);
                    cout << "   Opción inválida...";
                    this_thread::sleep_for(chrono::milliseconds(1000));
                    _colRESET();
                    break;
            }
        } while (info < 1 || info > 3);

        cout << "   ";
        this_thread::sleep_for(chrono::milliseconds(500));
        _colSET(cGREEN);
        escribir = escribir_Archivos("registro_costos_Variables.txt");
        if (escribir) {
            cout << "\n   ***********************************************************************";
            cout << "\n                          Costo variable editado...";
        } else return false;
        
        this_thread::sleep_for(chrono::milliseconds(2250));
        _colRESET();
    }

    return true;
}

//***************************************************************************************************

int eliminar_costo_Fijo(const char id[ID]) {
    int indice = 0;
    bool leer = false, escribir = false;

    leer = leer_Archivos("registro_costos_Fijos.txt");
    if (!leer) return -2;
    else if (checkear_Vacio(num_costos_Fijos)) return 1;

    indice = buscar_costo_Fijo(id);
    if (indice < 0) return indice;

    for (int i = indice; i < num_costos_Fijos-1; i++) {
        registro_costos_Fijos[i] = registro_costos_Fijos[i+1];
    } num_costos_Fijos--;

    escribir = escribir_Archivos("registro_costos_Fijos.txt");
    if (escribir) return 0;
    else return -2;
}

int eliminar_costo_Variable(const char id[ID]) {
    int indice = 0;
    bool leer = false, escribir = false;

    leer = leer_Archivos("registro_costos_Variables.txt");
    if (!leer) return -2;
    else if (checkear_Vacio(num_costos_Variables)) return 1;

    indice = buscar_costo_Variable(id);
    if (indice < 0) return indice;

    for (int i = indice; i < num_costos_Variables-1; i++) {
        registro_costos_Variables[i] = registro_costos_Variables[i+1];
    } num_costos_Variables--;

    escribir = escribir_Archivos("registro_costos_Variables.txt");
    if (escribir) return 0;
    else return -2;
}

//***************************************************************************************************