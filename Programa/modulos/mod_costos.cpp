#include "../headers/funciones_externas.h"
using namespace std;

//implementaciones de todas las funciones del modulo de gestion de costos (fijos + variables):
//***************************************************************************************************

bool registrar_costos_Fijos(int num) {
    system("cls || clear");
    bool leer = false, escribir = false;

    leer = leer_Archivos("registro_costos_Fijos.txt");
    if (!leer) return false;

    for (int i = 0; i < num; i++) {
        cambiar_color(11);
        cout << endl << "                              Costo Fijo #" << num_costos_Fijos+1 << ":" << endl;
        cout << "   ***********************************************************************\n";
        resetear_color();
        pedir_Cstring("ID", registro_costos_Fijos[num_costos_Fijos].id, ID);
        registro_costos_Fijos[num_costos_Fijos].monto = pedir_float("monto (en C$)");
        pedir_Cstring("descripción", registro_costos_Fijos[num_costos_Fijos].descripcion);
        num_costos_Fijos++;
    }

    escribir = escribir_Archivos("registro_costos_Fijos.txt");
    if (!escribir) return false;

    cout << "   ";
    Sleep(500);
    resetear_color();
    return true;
}

bool registrar_costos_Variables(int num) {
    system("cls || clear");
    bool leer = false, escribir = false;
    tm* time = obtener_fecha();

    leer = leer_Archivos("registro_costos_Variables.txt");
    if (!leer) return false;

    for (int i = 0; i < num; i++) {
        cambiar_color(11);
        cout << endl << "                            Costo Variable #" << num_costos_Variables+1 << ":" << endl;
        cout << "   ***********************************************************************\n";
        resetear_color();
        pedir_Cstring("ID", registro_costos_Variables[num_costos_Variables].id, ID);
        registro_costos_Variables[num_costos_Variables].monto = pedir_float("monto (en C$)");
        pedir_Cstring("descripción", registro_costos_Variables[num_costos_Variables].descripcion);
        strcpy(registro_costos_Variables[num_costos_Variables].mes, meses[time->tm_mon]);
        num_costos_Variables++;
    }

    escribir = escribir_Archivos("registro_costos_Variables.txt");
    if (!escribir) return false;

    cout << "   ";
    Sleep(500);
    resetear_color();
    return true;
}

//***************************************************************************************************

bool mostrar_costos_Fijos() {
    system("cls || clear");
    bool leer = leer_Archivos("registro_costos_Fijos.txt");
    if (!leer) return false;

    if (checkear_Vacio(num_costos_Fijos)) return true;

    cambiar_color(10);
    cout << "\n   Mostrando costos fijos registrados...";
    Sleep(800);

    cout << endl;
    for (int i = 0; i < num_costos_Fijos; i++) {
        cambiar_color(11);
        cout << endl << "                              Costo Fijo #" << i+1 << ":" << endl;
        cout << "   ***********************************************************************\n";
        cambiar_color(14);
        cout << "   ID: " << registro_costos_Fijos[i].id << "\n";
        cout << "   Monto: C$" << registro_costos_Fijos[i].monto << "\n";
        cout << "   Descripción: " << registro_costos_Fijos[i].descripcion << endl;
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

bool mostrar_costos_Variables() {
    system("cls || clear");
    bool leer = leer_Archivos("registro_costos_Variables.txt");
    if (!leer) return false;

    if (checkear_Vacio(num_costos_Variables)) return true;

    cambiar_color(10);
    cout << "\n   Mostrando costos variables registrados...";
    Sleep(800);

    cout << endl;
    for (int i = 0; i < num_costos_Variables; i++) {
        cambiar_color(11);
        cout << endl << "                            Costo Variable #" << i+1 << ":" << endl;
        cout << "   ***********************************************************************\n";
        cambiar_color(14);
        cout << "   ID: " << registro_costos_Variables[i].id << "\n";
        cout << "   Monto: C$" << registro_costos_Variables[i].monto << "\n";
        cout << "   Descripción: " << registro_costos_Variables[i].descripcion << "\n";
        cout << "   Mes: "; cambiar_color(9); cout << registro_costos_Variables[i].mes << endl;
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

int buscar_costo_Fijo(const char id[ID]) {
    bool leer = leer_Archivos("registro_costos_Fijos.txt");
    if (!leer) return -2;
    
    for (int i = 0; i < num_costos_Fijos; i++) {
        if (strcmp(registro_costos_Fijos[i].id, id) == 0) return i;
    }
    
    return -1;
}

int buscar_costo_Variable(const char id[ID]) {
    bool leer = leer_Archivos("registro_costos_Variables.txt");
    if (!leer) return -2;
    
    for (int i = 0; i < num_costos_Variables; i++) {
        if (strcmp(registro_costos_Variables[i].id, id) == 0) return i;
    }
    
    return -1;
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

    cambiar_color(9);
    cout << "\n   Buscando costo fijo...";
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
        cout << "\n   Costo fijo encontrado!";
        Sleep(750);
        cambiar_color(11);
        cout << endl << "\n                              Costo Fijo #" << indice+1 << ":" << endl;
        cout << "   ***********************************************************************";
        do {
            cambiar_color(14);
            cout << "\n\n   ¿Qué información quiere editar?" << endl;
            cout << "   1. Monto\n   2. Descripción\n";
            cambiar_color(9);
            cout << "   Ingrese su opción: ";
            cin >> info;

            cout << endl;
            resetear_color();
            switch (info) {
                case 1:
                    registro_costos_Fijos[indice].monto = pedir_float("monto (en C$)");
                    break;
                case 2:
                    pedir_Cstring("descripción", registro_costos_Fijos[indice].descripcion);
                    break;
                default:
                    cambiar_color(12);
                    cout << "   Opción inválida...";
                    Sleep(1000);
                    resetear_color();
                    break;
            }
        } while (info < 1 || info > 2);

        cout << "   "; Sleep(500);
        escribir = escribir_Archivos("registro_costos_Fijos.txt");
        if (escribir) {
            cambiar_color(10);
            cout << "\n   ***********************************************************************";
            cout << "\n                          Costo fijo editado...";
        } else return false;
        
        Sleep(2250);
        resetear_color();
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

    cambiar_color(9);
    cout << "\n   Buscando costo variable...";
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
        cout << "\n   Costo variable encontrado!";
        Sleep(750);
        cambiar_color(11);
        cout << endl << "\n                            Costo Variable #" << indice+1 << ":" << endl;
        cout << "   ***********************************************************************";
        do {
            cambiar_color(14);
            cout << "\n\n   ¿Qué información quiere editar?" << endl;
            cout << "   1. Monto\n   2. Descripción\n   3. Mes\n";
            cambiar_color(9);
            cout << "   Ingrese su opción: ";
            cin >> info;

            cout << endl;
            resetear_color();
            switch (info) {
                case 1:
                    registro_costos_Variables[indice].monto = pedir_float("monto (en C$)");
                    break;
                case 2:
                    pedir_Cstring("descripción", registro_costos_Variables[indice].descripcion);
                    break;
                case 3:
                    pedir_Cstring("mes", registro_costos_Variables[indice].mes, ID);
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
        escribir = escribir_Archivos("registro_costos_Variables.txt");
        if (escribir) {
            cout << "\n   ***********************************************************************";
            cout << "\n                          Costo variable editado...";
        } else return false;
        
        Sleep(2250);
        resetear_color();
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