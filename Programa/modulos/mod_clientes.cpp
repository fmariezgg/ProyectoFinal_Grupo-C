#include "../headers/funciones_externas.h"
using namespace std;
using namespace LLC;

//implementaciones de todas las funciones del modulo de gestion de clientes:

//todas estas son basicamente lo mismo que las de vacas, solo que con los datos de los clientes,
//entonces todos los comentarios explicando estan en mod_vacas.cpp
//***************************************************************************************************

int buscar_Cliente(const char input[MAX_INPUT], bool buscar_nombre) {
    if (buscar_nombre) {
        for (int i = 0; i < num_clientes; i++) {
            if (strcmp(registro_Clientes[i].nombre, input) == 0) return i;
        }
    } else {
        for (int i = 0; i < num_clientes; i++) {
            if (strcmp(registro_Clientes[i].id, input) == 0) return i;
        }
    }    
    
    return -1;
}

//***************************************************************************************************

bool registrar_Clientes() {
    system("cls || clear");
    char tempID[ID] = "", input[3] = "";
    bool leer = false, escribir = false;

    leer = leer_Archivos("registro_Clientes.txt");
    if (!leer) return false;

    do {
        _colSET(cCYAN);
        cout << endl << "                                Cliente #" << num_clientes+1 << ":" << endl;
        cout << "   ***********************************************************************\n";
        _colRESET();
        
        while (true) {
            pedir_Cstring("ID", tempID, ID);

            if (buscar_Cliente(tempID, false) >= 0) {
                _colSET(cRED);
                cout << "   ERROR: ID ya registrado...";
                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(1500));
                cout << endl;
                continue;
            } else if (buscar_Cliente(tempID, false) == -1) {
                strcpy(registro_Clientes[num_clientes].id, tempID);
                break;
            } else if (buscar_Cliente(tempID, false) == -2) return false;
        }

        pedir_Cstring("nombre", registro_Clientes[num_clientes].nombre);
        pedir_Cstring("dirección", registro_Clientes[num_clientes].direccion);
        pedir_Cstring("contacto", registro_Clientes[num_clientes].contacto);
        
        num_clientes++;
        continuar("\n   ¿Desea registrar más clientes? (si/no) ", input);

    } while (((strcmp(input, "s") == 0) || (strcmp(input, "S") == 0) || (strcmp(input, "si") == 0) || (strcmp(input, "Si") == 0) || (strcmp(input, "sI") == 0) || (strcmp(input, "SI") == 0)));


    escribir = escribir_Archivos("registro_Clientes.txt");
    if (!escribir) return false;

    cout << "   ";
    this_thread::sleep_for(chrono::milliseconds(500));
    _colRESET();
    return true;
}

//***************************************************************************************************

bool mostrar_Clientes() {
    system("cls || clear");
    bool leer = leer_Archivos("registro_Clientes.txt");
    if (!leer) return false;

    if (checkear_Vacio(num_clientes)) return true;

    _colSET(cGREEN);
    cout << "\n   Mostrando clientes registrados...";
    this_thread::sleep_for(chrono::milliseconds(500));

    cout << endl;
    for (int i = 0; i < num_clientes; i++) {
        _colSET(cCYAN);
        cout << endl << "                                Cliente #" << i+1 << ":" << endl;
        cout << "   ***********************************************************************\n";
        _colSET(cLIGHT_YELLOW);
        cout << "   ID: " << registro_Clientes[i].id << "\n";
        cout << "   Nombre: " << registro_Clientes[i].nombre << "\n";
        cout << "   Dirección: " << registro_Clientes[i].direccion << "\n";
        cout << "   Contacto: " << registro_Clientes[i].contacto << endl;
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

bool editar_Cliente() {
    system("cls || clear");
    bool leer = false, escribir = false;
    int indice = 0, info = 0;
    char id[ID] = "";

    leer = leer_Archivos("registro_Clientes.txt");
    if (!leer) return false;
    if (checkear_Vacio(num_clientes)) return true;

    cout << endl;
    pedir_Cstring("ID del cliente a editar", id, ID);
    indice = buscar_Cliente(id, false);

    _colSET(cTEAL);
    cout << "\n   Buscando cliente...";
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
        cout << "\n   Cliente encontrado!";
        this_thread::sleep_for(chrono::milliseconds(500));
        _colSET(cCYAN);
        cout << endl << "\n                                Cliente #" << indice+1 << ":" << endl;
        cout << "   ***********************************************************************";
        do {
            _colSET(cLIGHT_YELLOW);
            cout << "\n\n   ¿Qué información quiere editar?" << endl;
            cout << "   1. Nombre\n   2. Dirección\n   3. Contacto\n";
            _colSET(cTEAL);
            cout << "   Ingrese su opción: ";
            cin >> info;

            if (cin.fail()) {
                error_opcion();
                continue;
            }

            cout << endl;
            _colRESET();
            switch (info) {
                case 1:
                    pedir_Cstring("nombre", registro_Clientes[indice].nombre);
                    break;
                case 2:
                    pedir_Cstring("dirección", registro_Clientes[indice].direccion);
                    break;
                case 3:
                    pedir_Cstring("contacto", registro_Clientes[indice].contacto);
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
        escribir = escribir_Archivos("registro_Clientes.txt");
        if (escribir) {
            _colSET(cGREEN);
            cout << "\n   ***********************************************************************";
            cout << "\n                              Cliente editado...";
        } else return false;
        
        this_thread::sleep_for(chrono::milliseconds(2250));
        _colRESET();
    }

    return true;
}

//***************************************************************************************************

int eliminar_Cliente(const char id[ID]) {
    int indice = 0;
    bool leer = false, escribir = false;

    leer = leer_Archivos("registro_Clientes.txt");
    if (!leer) return -2;
    if (checkear_Vacio(num_clientes)) return 1;

    indice = buscar_Cliente(id, false);
    if (indice < 0) return indice;

    for (int i = indice; i < num_clientes-1; i++) {
        registro_Clientes[i] = registro_Clientes[i+1];
    } num_clientes--;

    escribir = escribir_Archivos("registro_Clientes.txt");
    if (escribir) return 0;
    else return -2;
}

//***************************************************************************************************