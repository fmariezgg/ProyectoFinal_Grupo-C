#include <iostream>
#include <cstring>
#include <windows.h>
#include "funciones_soporte.h"
using namespace std;

/*PENDIENTES:
-- mierdas de fecha
-- hacer que se actualicen los pagos pendientes de un cliente si se ingresa que no se ha pagado su compra
-- literalmente el 90% del sistema :D */

//***************************************************************************************************

bool cambiar_Precio(); //todas estas retornan bool para que se pueda checkear si se pudo abrir/leer/escribir al archivo
bool registrar_Vacas(int num); //y num es la cantidad de cosas que se van a registrar (para que el usuario no tenga que estar ingresando 1 por 1)
bool registrar_Clientes(int num);
bool registrar_Ventas(int num);
bool registrar_costos_Fijos(int num);
bool registrar_costos_Variables(int num);

//***************************************************************************************************

bool cambiar_Precio() {
    system("cls || clear");
    cout << "\nIngrese el nuevo precio por galon: ";
    cin >> precio_galon;
    bool escribir = escribir_archivo("precio_galon.txt");
    
    if (!escribir) return false;
    return true;
}

bool registrar_Vacas(int num) {
    system("cls || clear");
    bool leer = false, escribir = false;

    leer = leer_archivo("registro_Vacas.txt");
    if (!leer) return false;

    for (int i = 0; i < num; i++) {
        cout << "\n\tVaca #" << num_vacas+1 << ":" << endl;
        cout << "************************\n";
        cin.ignore();
        pedir_Cstring("ID", registro_Vacas[num_vacas].id, ID);
        pedir_Cstring("estado de salud", registro_Vacas[num_vacas].estado_salud);
        registro_Vacas[num_vacas].edad = pedir_int("edad");
        registro_Vacas[num_vacas].prod_diaria = pedir_int("producción diaria");
        num_vacas++;
    }

    escribir = escribir_archivo("registro_Vacas.txt");
    if (!escribir) return false;

    return true; //si no se ha retornado, significa que las operaciones de leer y escribir funcionaron bien y se guardaron los datos
}

bool registrar_Clientes(int num) {
    system("cls || clear");
    bool leer = false, escribir = false;

    leer = leer_archivo("registro_Clientes.txt");
    if (!leer) return false;

    for (int i = 0; i < num; i++) {
        cout << "\n\tCliente #" << num_clientes+1 << ":" << endl;
        cout << "************************\n";
        cin.ignore();
        pedir_Cstring("nombre", registro_Clientes[num_clientes].nombre);
        pedir_Cstring("dirección", registro_Clientes[num_clientes].direccion);
        pedir_Cstring("contacto", registro_Clientes[num_clientes].contacto);
        num_clientes++;
    }

    escribir = escribir_archivo("registro_Clientes.txt");
    if (!escribir) return false;

    return true;
}

bool registrar_Ventas(int num) {
    system("cls || clear");
    bool leer_V = false, leer_P = false, escribir = false;

    leer_V = leer_archivo("registro_Ventas.txt");
    leer_P = leer_archivo("precio_galon.txt");
    if (!leer_V || !leer_P) return false;

    for (int i = 0; i < num; i++) {
        cout << "\n\tVenta #" << num_ventas+1 << ":" << endl;
        cout << "************************\n";
        cin.ignore();
        pedir_Cstring("ID", registro_Ventas[num_ventas].id, ID);
        pedir_Cstring("nombre del cliente", registro_Ventas[num_ventas].nombre_cliente);
        //fechas
        registro_Ventas[num_ventas].cantidad_leche = pedir_int("cantidad de leche");
        registro_Ventas[num_ventas].monto = precio_galon * registro_Ventas[num_ventas].cantidad_leche;
        cin.ignore();
        registro_Ventas[num_ventas].pagada = pedir_pagada();
        num_ventas++;
    }

    escribir = escribir_archivo("registro_Ventas.txt");
    if (!escribir) return false;

    return true; //si no se ha retornado, significa que las operaciones de leer y escribir funcionaron bien y se guardaron los datos
}

bool registrar_costos_Fijos(int num) {
    system("cls || clear");
    bool leer = false, escribir = false;

    leer = leer_archivo("registro_costos_Fijos.txt");
    if (!leer) return false;

    for (int i = 0; i < num; i++) {
        cout << "\n     Costo Fijo #" << num_costos_Fijos+1 << ":" << endl;
        cout << "************************\n";
        registro_costos_Fijos[num_costos_Fijos].monto = pedir_float("monto");
        cin.ignore();
        pedir_Cstring("descripción", registro_costos_Fijos[num_costos_Fijos].descripcion);
        num_costos_Fijos++;
    }

    escribir = escribir_archivo("registro_costos_Fijos.txt");
    if (!escribir) return false;

    return true; //si no se ha retornado, significa que las operaciones de leer y escribir funcionaron bien y se guardaron los datos
}

bool registrar_costos_Variables(int num) {
    system("cls || clear");
    bool leer = false, escribir = false;

    leer = leer_archivo("registro_costos_Variables.txt");
    if (!leer) return false;

    for (int i = 0; i < num; i++) {
        cout << "\n   Costo Variable #" << num_costos_Variables+1 << ":" << endl;
        cout << "************************\n";
        registro_costos_Variables[num_costos_Variables].monto = pedir_float("monto");
        cin.ignore();
        pedir_Cstring("descripción", registro_costos_Variables[num_costos_Variables].descripcion);
        num_costos_Variables++;
    }

    escribir = escribir_archivo("registro_costos_Variables.txt");
    if (!escribir) return false;

    return true; //si no se ha retornado, significa que las operaciones de leer y escribir funcionaron bien y se guardaron los datos
}