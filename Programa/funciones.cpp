#include <iostream>
#include <cstring>
#include <ctime>
#include <windows.h>
#include "funciones_externas.h"
using namespace std;

//***************************************************************************************************

bool cambiar_Precio(); //todas estas retornan bool para que se pueda checkear si se pudo abrir/leer/escribir al archivo
bool registrar_Vacas(int num); //y num es la cantidad de cosas que se van a registrar (para que el usuario no tenga que estar ingresando 1 por 1)
bool registrar_Clientes(int num);
bool registrar_Ventas(int num);
bool registrar_costos_Fijos(int num);
bool registrar_costos_Variables(int num);

//***************************************************************************************************

bool cambiar_Precio() {
    cambiar_color(14);
    cout << endl << "      Ingrese el nuevo precio por galon: ";
    cin >> precio_galon;
    resetear_color();

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
        cambiar_color(11);
        cout << endl << "                                  Vaca #" << num_vacas+1 << ":" << endl;
        cout << "   ***********************************************************************\n";
        resetear_color();
        pedir_Cstring("ID", registro_Vacas[num_vacas].id, ID);
        pedir_Cstring("estado de salud", registro_Vacas[num_vacas].estado_salud);
        registro_Vacas[num_vacas].edad = pedir_int("edad");
        registro_Vacas[num_vacas].prod_diaria = pedir_int("producción diaria");
        num_vacas++;
    }

    resetear_color();
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
        cambiar_color(11);
        cout << endl << "                                Cliente #" << num_clientes+1 << ":" << endl;
        cout << "   ***********************************************************************\n";
        resetear_color();
        pedir_Cstring("nombre", registro_Clientes[num_clientes].nombre);
        pedir_Cstring("dirección", registro_Clientes[num_clientes].direccion);
        pedir_Cstring("contacto", registro_Clientes[num_clientes].contacto);
        num_clientes++;
    }

    escribir = escribir_archivo("registro_Clientes.txt");
    if (!escribir) return false;

    resetear_color();
    return true;
}

bool registrar_Ventas(int num) {
    system("cls || clear");
    bool leer_Ventas = false, leer_Precio = false, leer_Pendientes = false, escribir_Ventas = false, escribir_Pendientes = false;

    leer_Ventas = leer_archivo("registro_Ventas.txt");
    leer_Pendientes = leer_archivo("registro_Pendientes.txt");
    leer_Precio = leer_archivo("precio_galon.txt");
    if (!leer_Ventas || !leer_Pendientes || !leer_Precio) return false; //si cualquiera de las lecturas falla, retornar false

    //si el archivo precio_galon.txt no existe, se va a crear, pero va a estar vacio, entonces hay que pedir un precio para poder calcular el monto de las ventas
    if (precio_galon == 0.00) {
        cambiar_color(12);
        cout << endl << "   Archivo 'precio.galon.txt' vacío...\n";
        precio_galon = pedir_float("precio");

        bool check = escribir_archivo("precio_galon.txt");
        cambiar_color(10);
        if (check) cout << "   Precio guardado...\n";
        else return false;
        resetear_color();
    }

    for (int i = 0; i < num; i++) {
        cambiar_color(11);
        cout << endl << "                                  Venta #" << num_ventas+1 << ":" << endl;
        cout << "   ***********************************************************************\n";
        cin.ignore();
        resetear_color();
        pedir_Cstring("ID", registro_Ventas[num_ventas].id, ID);
        pedir_Cstring("nombre del cliente", registro_Ventas[num_ventas].nombre_cliente);

        tm *time = obtener_fecha();
        registro_Ventas[num_ventas].fecha.dia = time->tm_mday;
        strcpy(registro_Ventas[num_ventas].fecha.mes, meses[time->tm_mon]); //usar el numero de mes como index para retornar el nombre del mes
        registro_Ventas[num_ventas].fecha.year = time->tm_year + 1900; //sumar 1900 pq time->tm_year es el numero de años desde 1900
        
        registro_Ventas[num_ventas].cantidad_leche = pedir_int("cantidad de leche");
        registro_Ventas[num_ventas].monto = precio_galon * registro_Ventas[num_ventas].cantidad_leche; //calcular monto automaticamente
        registro_Ventas[num_ventas].pagada = pedir_pagada();

        //si se ingresa que no se ha pagado la compra, agregar los datos del cliente y la compra al registro de pagos pendientes
        if (!registro_Ventas[num_ventas].pagada) {
            strcpy(registro_Pendientes[num_pendientes].id_venta, registro_Ventas[num_ventas].id);
            registro_Pendientes[num_pendientes].fecha = registro_Ventas[num_ventas].fecha;
            strcpy(registro_Pendientes[num_pendientes].nombre_cliente, registro_Ventas[num_ventas].nombre_cliente);
            registro_Pendientes[num_pendientes].monto = registro_Ventas[num_ventas].monto;
            cambiar_color(10);
            cout << "   Pago pendiente registrado...\n";
            resetear_color();
            num_pendientes++;
        }

        num_ventas++;
    }

    escribir_Ventas = escribir_archivo("registro_Ventas.txt");
    escribir_Pendientes = escribir_archivo("registro_Pendientes.txt");
    if (!escribir_Ventas || !escribir_Pendientes) return false; //lo mismo que las operaciones de lectura

    resetear_color();
    return true;
}

bool registrar_costos_Fijos(int num) {
    system("cls || clear");
    bool leer = false, escribir = false;

    leer = leer_archivo("registro_costos_Fijos.txt");
    if (!leer) return false;

    for (int i = 0; i < num; i++) {
        cambiar_color(11);
        cout << endl << "                              Costo Fijo #" << num_costos_Fijos+1 << ":" << endl;
        cout << "   ***********************************************************************\n";
        resetear_color();
        registro_costos_Fijos[num_costos_Fijos].monto = pedir_float("monto");
        pedir_Cstring("descripción", registro_costos_Fijos[num_costos_Fijos].descripcion);
        num_costos_Fijos++;
    }

    escribir = escribir_archivo("registro_costos_Fijos.txt");
    if (!escribir) return false;

    resetear_color();
    return true;
}

bool registrar_costos_Variables(int num) {
    system("cls || clear");
    bool leer = false, escribir = false;

    leer = leer_archivo("registro_costos_Variables.txt");
    if (!leer) return false;

    for (int i = 0; i < num; i++) {
        cambiar_color(11);
        cout << endl << "                            Costo Variable #" << num_costos_Variables+1 << ":" << endl;
        cout << "   ***********************************************************************\n";
        resetear_color();
        registro_costos_Variables[num_costos_Variables].monto = pedir_float("monto");
        pedir_Cstring("descripción", registro_costos_Variables[num_costos_Variables].descripcion);
        num_costos_Variables++;
    }

    escribir = escribir_archivo("registro_costos_Variables.txt");
    if (!escribir) return false;

    resetear_color();
    return true;
}