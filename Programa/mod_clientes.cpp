#include "funciones_externas.h"
using namespace std;

//implementaciones de todas las funciones del modulo de gestion de CLIENTES:
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

    if (num_clientes == 0) {
        cambiar_color(12);
        cout << "\n   No hay clientes registrados...";
        Sleep(3000);
        resetear_color();
        return true;
    }

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
        cout << "   Contacto: " << registro_Clientes[i].contacto << "\n";
        cout << "   ";
        Sleep(800);
    }

    cambiar_color(11);
    cout << endl << "   ***********************************************************************\n";
    cambiar_color(14);
    cout << "   Presione cualquier tecla para continuar...";
    system("pause > NULL");
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