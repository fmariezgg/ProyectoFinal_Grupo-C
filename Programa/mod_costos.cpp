#include "funciones_externas.h"
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

    if (num_costos_Fijos == 0) {
        cambiar_color(12);
        cout << "\n   No hay costos fijos registrados...";
        Sleep(3000);
        resetear_color();
        return true;
    }

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
        cout << "   Descripción: " << registro_costos_Fijos[i].descripcion << "\n";
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

bool mostrar_costos_Variables() {
    system("cls || clear");
    bool leer = leer_Archivos("registro_costos_Variables.txt");
    if (!leer) return false;

    if (num_costos_Variables == 0) {
        cambiar_color(12);
        cout << "\n   No hay costos variables registrados...";
        Sleep(3000);
        resetear_color();
        return true;
    }

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
        cout << "   Mes: "; cambiar_color(9); cout << registro_costos_Variables[i].mes << "\n";
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

bool editar_costos_Fijos() {
    system("cls || clear");
    bool leer = leer_Archivos("registro_costos_Fijos.txt");
    if (!leer) return false;

    char id[ID] = "";
    pedir_Cstring("ID del costo fijo a editar", id, ID);

    for (int i = 0; i < num_costos_Fijos; i++) {
        if (strcmp(registro_costos_Fijos[i].id, id) == 0) {
            cambiar_color(11);
            cout << endl << "                              Costo Fijo #" << i+1 << ":" << endl;
            cout << "   ***********************************************************************\n";
            resetear_color();
            pedir_Cstring("ID", registro_costos_Fijos[i].id, ID);
            registro_costos_Fijos[i].monto = pedir_float("monto (en C$)");
            pedir_Cstring("descripción", registro_costos_Fijos[i].descripcion);
            cambiar_color(10);
            cout << "   Costo fijo editado...";
            Sleep(1500);
            resetear_color();
            return true;
        }
    }

    cambiar_color(12);
    cout << "\n   Costo fijo no encontrado...";
    Sleep(1500);
    resetear_color();
    return true;
}

bool editar_costos_Variables() {
    system("cls || clear");
    bool leer = leer_Archivos("registro_costos_Variables.txt");
    if (!leer) return false;

    char id[ID] = "";
    pedir_Cstring("ID del costo variable a editar", id, ID);

    for (int i = 0; i < num_costos_Variables; i++) {
        if (strcmp(registro_costos_Variables[i].id, id) == 0) {
            cambiar_color(11);
            cout << endl << "                            Costo Variable #" << i+1 << ":" << endl;
            cout << "   ***********************************************************************\n";
            resetear_color();
            pedir_Cstring("ID", registro_costos_Variables[i].id, ID);
            registro_costos_Variables[i].monto = pedir_float("monto (en C$)");
            pedir_Cstring("descripción", registro_costos_Variables[i].descripcion);
            cambiar_color(10);
            cout << "   Costo variable editado...";
            Sleep(1500);
            resetear_color();
            return true;
        }
    }

    cambiar_color(12);
    cout << "\n   Costo variable no encontrado...";
    Sleep(1500);
    resetear_color();
    return true;
}

//***************************************************************************************************

bool eliminar_costo_Fijo() {
    system("cls || clear");
    bool leer = leer_Archivos("registro_costos_Fijos.txt");
    if (!leer) return false;

    char id[ID] = "";
    pedir_Cstring("ID del costo fijo a eliminar", id, ID);

    for (int i = 0; i < num_costos_Fijos; i++) {
        if (strcmp(registro_costos_Fijos[i].id, id) == 0) {
            for (int j = i; j < num_costos_Fijos; j++) {
                registro_costos_Fijos[j] = registro_costos_Fijos[j+1];
            }
            num_costos_Fijos--;
            cambiar_color(10);
            cout << "\n   Costo fijo eliminado...";
            Sleep(1500);
            resetear_color();
            return true;
        }
    }

    cambiar_color(12);
    cout << "\n   Costo fijo no encontrado...";
    Sleep(1500);
    resetear_color();
    return true;
}

bool eliminar_costo_Variable() {
    system("cls || clear");
    bool leer = leer_Archivos("registro_costos_Variables.txt");
    if (!leer) return false;

    char id[ID] = "";
    pedir_Cstring("ID del costo variable a eliminar", id, ID);

    for (int i = 0; i < num_costos_Variables; i++) {
        if (strcmp(registro_costos_Variables[i].id, id) == 0) {
            for (int j = i; j < num_costos_Variables; j++) {
                registro_costos_Variables[j] = registro_costos_Variables[j+1];
            }
            num_costos_Variables--;
            cambiar_color(10);
            cout << "\n   Costo variable eliminado...";
            Sleep(1500);
            resetear_color();
            return true;
        }
    }

    cambiar_color(12);
    cout << "\n   Costo variable no encontrado...";
    Sleep(1500);
    resetear_color();
    return true;
}

//***************************************************************************************************