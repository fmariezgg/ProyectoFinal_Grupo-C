#include "funciones_externas.h"
using namespace std;

//implementaciones de todas las funciones del modulo de gestion de VENTAS y PENDIENTES:
//***************************************************************************************************

bool registrar_Ventas(int num) {
    system("cls || clear");
    bool leer_Ventas = false, leer_Precio = false, leer_Pendientes = false, escribir_Ventas = false, escribir_Pendientes = false;

    leer_Ventas = leer_Archivos("registro_Ventas.txt");
    leer_Pendientes = leer_Archivos("registro_Pendientes.txt");
    leer_Precio = leer_Archivos("precio_galon.txt");
    if (!leer_Ventas || !leer_Pendientes || !leer_Precio) return false; //si cualquiera de las lecturas falla, retornar false

    //si el archivo precio_galon.txt no existe, se va a crear, pero va a estar vacio, entonces hay que pedir un precio para poder calcular el monto de las ventas
    if (precio_galon == 0.00) {
        cambiar_color(12);
        cout << endl << "   Archivo 'precio.galon.txt' vacío...\n";
        precio_galon = pedir_float("precio");

        bool check = escribir_Archivos("precio_galon.txt");
        cambiar_color(10);
        if (check) cout << "   Precio guardado...";
        else return false;
        Sleep(500);
        cout << endl;
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
        strcpy(registro_Ventas[num_ventas].fecha.mes, meses[time->tm_mon]); //usar el numero de mes como indice para retornar el nombre del mes
        registro_Ventas[num_ventas].fecha.year = time->tm_year + 1900; //sumarle 1900 pq time->tm_year es el numero de años *desde* 1900
        
        registro_Ventas[num_ventas].cantidad_leche = pedir_int("cantidad de leche (en galones)");
        registro_Ventas[num_ventas].monto = precio_galon * registro_Ventas[num_ventas].cantidad_leche; //calcular monto automaticamente
        registro_Ventas[num_ventas].pagada = pedir_pagada();

        //si se ingresa que no se ha pagado la compra, agregar los datos del cliente y la compra al registro de pagos pendientes
        if (!registro_Ventas[num_ventas].pagada) {
            strcpy(registro_Pendientes[num_pendientes].id_venta, registro_Ventas[num_ventas].id);
            registro_Pendientes[num_pendientes].fecha = registro_Ventas[num_ventas].fecha;
            strcpy(registro_Pendientes[num_pendientes].nombre_cliente, registro_Ventas[num_ventas].nombre_cliente);
            registro_Pendientes[num_pendientes].monto = registro_Ventas[num_ventas].monto;
            cambiar_color(10);
            cout << "   Pago pendiente registrado...";
            Sleep(650);
            resetear_color();
            cout << endl;
            num_pendientes++;
        }

        num_ventas++;
    }

    escribir_Ventas = escribir_Archivos("registro_Ventas.txt");
    escribir_Pendientes = escribir_Archivos("registro_Pendientes.txt");
    if (!escribir_Ventas || !escribir_Pendientes) return false; //lo mismo que las operaciones de lectura

    cout << "   ";
    Sleep(500);
    resetear_color();
    return true;
}

//***************************************************************************************************

bool mostrar_Ventas() {
    system("cls || clear");
    char pagada[3] = "";
    bool leer = leer_Archivos("registro_Ventas.txt");
    if (!leer) return false;

    if (num_ventas == 0) {
        cambiar_color(12);
        cout << "\n   No hay ventas registradas...";
        Sleep(3000);
        resetear_color();
        return true;
    }

    cambiar_color(10);
    cout << "\n   Mostrando ventas registradas...";
    Sleep(800);

    cout << endl;
    for (int i = 0; i < num_ventas; i++) {
        //para que 'pagada' no se imprima como 0 o 1, se le asigna un C-string dependiendo del valor de registro_Ventas[i].pagada usando una operacion ternaria
        strcpy(pagada, registro_Ventas[i].pagada ? "Si" : "No");

        cambiar_color(11);
        cout << endl << "                                  Venta #" << i+1 << ":" << endl;
        cout << "   ***********************************************************************\n";
        cambiar_color(14);
        cout << "   ID: " << registro_Ventas[i].id << "\n";
        cout << "   Fecha: " << registro_Ventas[i].fecha.dia << " de " << registro_Ventas[i].fecha.mes << ", " << registro_Ventas[i].fecha.year << "\n";
        cout << "   Nombre de cliente: " << registro_Ventas[i].nombre_cliente << "\n";
        cout << "   Cantidad de leche: " << registro_Ventas[i].cantidad_leche << " galone(s)\n";
        cout << "   Monto: C$" << registro_Ventas[i].monto << "\n";
        cout << "   ¿Está pagada? "; cambiar_color(9); cout << pagada << "\n";
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

bool mostrar_Pendientes() {
    system("cls || clear");
    bool leer = leer_Archivos("registro_Pendientes.txt");
    if (!leer) return false;

    if (num_pendientes == 0) {
        cambiar_color(12);
        cout << "\n   No hay pagos pendientes...";
        Sleep(3000);
        resetear_color();
        return true;
    }

    cambiar_color(10);
    cout << "\n   Mostrando pagos pendientes...";
    Sleep(800);

    cout << endl;
    for (int i = 0; i < num_pendientes; i++) {
        cambiar_color(11);
        cout << endl << "                              Pago Pendiente #" << i+1 << ":" << endl;
        cout << "   ***********************************************************************\n";
        cambiar_color(14);
        cout << "   ID de venta: " << registro_Pendientes[i].id_venta << "\n";
        cout << "   Fecha: " << registro_Pendientes[i].fecha.dia << " de " << registro_Pendientes[i].fecha.mes << ", " << registro_Pendientes[i].fecha.year << "\n";
        cout << "   Nombre de cliente: " << registro_Pendientes[i].nombre_cliente << "\n";
        cout << "   Monto: C$" << registro_Pendientes[i].monto << "\n";
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

int buscar_Venta(const char id[ID]) {
    bool leer = leer_Archivos("registro_Ventas.txt");
    if (!leer) return -2;
    
    for (int i = 0; i < num_ventas; i++) {
        if (strcmp(registro_Ventas[i].id, id) == 0) return i;
    }
    
    return -1;
}

int buscar_Pendiente(const char id[ID]) {
    bool leer = leer_Archivos("registro_Pendientes.txt");
    if (!leer) return -2;
    
    for (int i = 0; i < num_pendientes; i++) {
        if (strcmp(registro_Pendientes[i].id_venta, id) == 0) return i;
    }
    
    return -1;
}

//***************************************************************************************************