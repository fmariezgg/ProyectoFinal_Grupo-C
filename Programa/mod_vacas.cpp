#include "funciones_externas.h"
using namespace std;

//implementaciones de todas las funciones del modulo de gestion de VACAS:
//***************************************************************************************************

bool registrar_Vacas(int num) {
    system("cls || clear");
    bool leer = false, escribir = false;

    leer = leer_Archivos("registro_Vacas.txt");
    if (!leer) return false;

    for (int i = 0; i < num; i++) {
        cambiar_color(11);
        cout << endl << "                                  Vaca #" << num_vacas+1 << ":" << endl;
        cout << "   ***********************************************************************\n";
        resetear_color();
        pedir_Cstring("ID", registro_Vacas[num_vacas].id, ID);
        registro_Vacas[num_vacas].edad = pedir_int("edad (en años)");
        registro_Vacas[num_vacas].prod_diaria = pedir_int("producción diaria (en galones)");
        pedir_Cstring("estado de salud", registro_Vacas[num_vacas].estado_salud);
        num_vacas++;
    }

    escribir = escribir_Archivos("registro_Vacas.txt");
    if (!escribir) return false;

    cout << "   ";
    Sleep(500);
    resetear_color();
    return true; //si no se ha retornado, significa que las operaciones de leer y escribir funcionaron bien y se guardaron los datos
}

//***************************************************************************************************

bool mostrar_Vacas() {
    system("cls || clear");
    bool leer = leer_Archivos("registro_Vacas.txt");
    if (!leer) return false;

    if (num_vacas == 0) { //checkear si el archivo estaba vacio
        cambiar_color(12);
        cout << "\n   No hay vacas registradas...";
        Sleep(3000);
        resetear_color();
        return true;
    }

    cambiar_color(10);
    cout << "\n   Mostrando vacas registradas...";
    Sleep(800);

    cout << endl;
    for (int i = 0; i < num_vacas; i++) {
        cambiar_color(11);
        cout << endl << "                                  Vaca #" << i+1 << ":" << endl;
        cout << "   ***********************************************************************\n";
        cambiar_color(14);
        cout << "   ID: " << registro_Vacas[i].id << "\n";
        cout << "   Edad: " << registro_Vacas[i].edad << " año(s)\n";
        cout << "   Producción diaria: " << registro_Vacas[i].prod_diaria << " galón(es)\n";
        cout << "   Estado de salud: " << registro_Vacas[i].estado_salud << "\n";
        cout << "   ";
        Sleep(800);
    }

    cambiar_color(11);
    cout << endl << "   ***********************************************************************\n";
    cambiar_color(14);
    cout << "   Presione cualquier tecla para continuar...";

    //para que system("pause") no muestre el mensaje default, le pongo eso de '> NULL', e imprimo mi propio mensaje (con mi formato y colores) antes
    system("pause > NULL");
    return true;
}

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