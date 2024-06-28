#include "funciones_externas.h"
using namespace std;

//implementaciones de todas las funciones del modulo de gestion de clientes:
//***************************************************************************************************

bool registrar_Clientes(int num) {
    system("cls || clear");
    bool leer = false, escribir = false;

    leer = leer_Archivos("registro_Clientes.txt");
    if (!leer) return false;

    for (int i = 0; i < num; i++) {
        cambiar_color(11);
        cout << endl << "                                Cliente #" << num_clientes+1 << ":" << endl;
        cout << "   ***********************************************************************\n";
        resetear_color();
        pedir_Cstring("ID", registro_Clientes[num_clientes].id, ID);
        pedir_Cstring("nombre", registro_Clientes[num_clientes].nombre);
        pedir_Cstring("dirección", registro_Clientes[num_clientes].direccion);
        pedir_Cstring("contacto", registro_Clientes[num_clientes].contacto);
        num_clientes++;
    }

    escribir = escribir_Archivos("registro_Clientes.txt");
    if (!escribir) return false;

    cout << "   ";
    Sleep(500);
    resetear_color();
    return true;
}

//***************************************************************************************************

bool mostrar_Clientes() {
    system("cls || clear");
    bool leer = leer_Archivos("registro_Clientes.txt");
    if (!leer) return false;

    if (checkear_Vacio(num_clientes)) return true;

    cambiar_color(10);
    cout << "\n   Mostrando clientes registrados...";
    Sleep(800);

    cout << endl;
    for (int i = 0; i < num_clientes; i++) {
        cambiar_color(11);
        cout << endl << "                                Cliente #" << i+1 << ":" << endl;
        cout << "   ***********************************************************************\n";
        cambiar_color(14);
        cout << "   ID: " << registro_Clientes[i].id << "\n";
        cout << "   Nombre: " << registro_Clientes[i].nombre << "\n";
        cout << "   Dirección: " << registro_Clientes[i].direccion << "\n";
        cout << "   Contacto: " << registro_Clientes[i].contacto << endl;
        cout << "   ";
        Sleep(800);
    }

    cambiar_color(11);
    cout << endl << "   ***********************************************************************\n";
    cout << "   Presione cualquier tecla para continuar...";
    system("pause > NULL");
    resetear_color();
    return true;
}

//***************************************************************************************************

int buscar_Cliente(const char input[MAX_INPUT], bool buscar_nombre) {
    bool leer = leer_Archivos("registro_Clientes.txt");
    if (!leer) return -2;

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

    cambiar_color(9);
    cout << "\n   Buscando cliente...";
    Sleep(800);
    resetear_color();

    if (indice == -1) {
        cambiar_color(12);
        cout << "\n   ERROR: ID ingresado no esta registrado...";
        Sleep(2250);
        resetear_color();
        return true;
    } else if (indice == -2) return false;

    else if (indice >= 0) {
        cambiar_color(10);
        cout << "\n   Cliente encontrado!";
        Sleep(750);
        cambiar_color(11);
        cout << endl << "\n                                Cliente #" << indice+1 << ":" << endl;
        cout << "   ***********************************************************************";
        do {
            cambiar_color(14);
            cout << "\n\n   ¿Qué información quiere editar?" << endl;
            cout << "   1. Nombre\n   2. Dirección\n   3. Contacto\n";
            cambiar_color(9);
            cout << "   Ingrese su opción: ";
            cin >> info;

            cout << endl;
            resetear_color();
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
                    cambiar_color(12);
                    cout << "   Opción inválida...";
                    Sleep(1000);
                    resetear_color();
                    break;
            }
        } while (info < 1 || info > 3);

        cout << "   "; Sleep(500);
        cambiar_color(10);
        escribir = escribir_Archivos("registro_Clientes.txt");
        if (escribir) {
            cambiar_color(10);
            cout << "\n   ***********************************************************************";
            cout << "\n                              Cliente editado...";
        } else return false;
        
        Sleep(2250);
        resetear_color();
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

    for (int i = indice; i < num_clientes; i++) {
        registro_Clientes[i] = registro_Clientes[i+1];
    } num_clientes--;

    escribir = escribir_Archivos("registro_Clientes.txt");
    if (escribir) return 0;
    else return -2;
}

//***************************************************************************************************