#include "../headers/funciones_externas.h"
using namespace std;

//implementaciones de todas las funciones del modulo de gestion de vacas:
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

    if (checkear_Vacio(num_vacas)) return true; //checkea si esta vacio el registro

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
        cout << "   Estado de salud: " << registro_Vacas[i].estado_salud << endl;
        cout << "   ";
        Sleep(800);
    }

    cambiar_color(11);
    cout << endl << "   ***********************************************************************\n";
    cout << "   Presione cualquier tecla para continuar...";

    //para que system("pause") no muestre el mensaje default, le pongo eso de '> NULL', e imprimo mi propio mensaje (con mi formato y colores) antes
    system("pause > NULL");
    resetear_color();
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

    cambiar_color(9);
    cout << "\n   Buscando vaca...";
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
        cout << "\n   Vaca encontrada!";
        Sleep(750);
        cambiar_color(11);
        cout << endl << "\n                                  Vaca #" << indice+1 << ":" << endl;
        cout << "   ***********************************************************************";
        do {
            cambiar_color(14);
            cout << "\n\n   ¿Qué información quiere editar?" << endl;
            cout << "   1. Edad\n   2. Producción diaria\n   3. Estado de salud\n";
            cambiar_color(9);
            cout << "   Ingrese su opción: ";
            cin >> info;

            cout << endl;
            resetear_color();
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
                    cambiar_color(12);
                    cout << "   Opción inválida...";
                    Sleep(1000);
                    resetear_color();
                    break;
            }
        } while (info < 1 || info > 3);

        cout << "   "; Sleep(500);
        cambiar_color(10);
        escribir = escribir_Archivos("registro_Vacas.txt");
        if (escribir) {
            cambiar_color(10);
            cout << "\n   ***********************************************************************";
            cout << "\n                              Vaca editada...";
        } else return false;
        
        Sleep(2250);
        resetear_color();
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