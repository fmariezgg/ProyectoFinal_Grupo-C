#include "funciones_externas.h"
using namespace std;

//implementaciones de todas las funciones del modulo de gestion de ventas y de pagos pendientes:
//las de eliminar van primero para que esten definidas cuando se llaman en las de editar (por eso estan al reves tambien)
//***************************************************************************************************

bool registrar_Ventas(int num) {
    system("cls || clear");
    bool leer_Ventas = false, leer_Precio = false, leer_Pendientes = false;
    bool escribir_Ventas = false, escribir_Pendientes = false;

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

    if (checkear_Vacio(num_ventas)) return true;

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
        cout << "   ¿Está pagada? "; cambiar_color(9); cout << pagada << endl;
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

bool mostrar_Pendientes() {
    system("cls || clear");
    bool leer = leer_Archivos("registro_Pendientes.txt");
    if (!leer) return false;

    if (checkear_Vacio(num_pendientes)) return true;

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
        cout << "   Monto a pagar: C$" << registro_Pendientes[i].monto << endl;
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

int eliminar_Pendiente(const char id[ID]) {
    int indice = 0, indice_venta = 0;
    bool leer = false, escribir = false;

    leer = leer_Archivos("registro_Pendientes.txt");
    if (!leer) return -2;
    if (checkear_Vacio(num_pendientes)) return 1;

    indice = buscar_Pendiente(id);
    if (indice < 0) return indice;

    //si se va a eliminar un pago pendiente, es pq ya se pago, entonces hay que actualizar el registro de la venta correspondiente
    indice_venta = buscar_Venta(registro_Pendientes[indice].id_venta);
    if (indice_venta >= 0) registro_Ventas[indice_venta].pagada = true;
    else return indice_venta;

    for (int i = indice; i < num_pendientes; i++) {
        registro_Pendientes[i] = registro_Pendientes[i+1];
    } num_ventas--;

    escribir = escribir_Archivos("registro_Pendientes.txt");
    if (escribir) return 0;
    else return -2;
}

int eliminar_Venta(const char id[ID]) {
    int indice = 0;
    bool leer = false, escribir = false;

    leer = leer_Archivos("registro_Ventas.txt");
    if (!leer) return -2;
    if (checkear_Vacio(num_ventas)) return 1;

    indice = buscar_Venta(id);
    if (indice < 0) return indice;

    //si la venta no esta pagada, significa que tambien estaba registrada como pendiente, entonces se elimina de ahi igual
    if (!registro_Ventas[indice].pagada) eliminar_Pendiente(id);

    for (int i = indice; i < num_ventas; i++) {
        registro_Ventas[i] = registro_Ventas[i+1];
    } num_ventas--;

    escribir = escribir_Archivos("registro_Ventas.txt");
    if (escribir) return 0;
    else return -2;
}

//***************************************************************************************************

bool editar_Venta() {
    system("cls || clear");
    bool leer = false, escribir = false;
    int indice = 0, indice_pendiente = 0, info = 0;
    char id[ID] = "";

    leer = leer_Archivos("registro_Ventas.txt");
    if (!leer) return false;
    if (checkear_Vacio(num_ventas)) return true;

    cout << endl;
    pedir_Cstring("ID de la venta a editar", id, ID);
    indice = buscar_Venta(id);

    cambiar_color(9);
    cout << "\n   Buscando venta...";
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
        cout << "\n   Venta encontrada!";
        Sleep(750);
        cambiar_color(11);
        cout << endl << "\n                                  Venta #" << indice+1 << ":" << endl;
        cout << "   ***********************************************************************\n";
        do {
            cambiar_color(14);
            cout << "\n\n   ¿Qué información quiere editar?" << endl;
            cout << "   1. Nombre del cliente\n   2. Cantidad de leche comprada\n   3. Monto\n   4. ¿Está pendiente el pago?\n";
            cambiar_color(9);
            cout << "   Ingrese su opción: ";
            cin >> info;

            cout << endl;
            resetear_color();
            switch (info) {
                case 1:
                    pedir_Cstring("nombre del cliente", registro_Ventas[indice].nombre_cliente);

                    indice_pendiente = buscar_Pendiente(id);
                    if (indice_pendiente >= 0) strcpy(registro_Pendientes[indice].nombre_cliente, registro_Ventas[indice_pendiente].nombre_cliente);
                    else return indice_pendiente;

                    break;
                case 2:
                    registro_Ventas[indice].cantidad_leche = pedir_int("cantidad de leche (en galones)");
                    break;
                case 3:
                    registro_Ventas[indice].monto = pedir_float("monto (en C$)");

                    indice_pendiente = buscar_Pendiente(id);
                    if (indice_pendiente >= 0) registro_Pendientes[indice].monto = registro_Ventas[indice_pendiente].monto;
                    else return indice_pendiente;

                    break;
                case 4:
                    registro_Ventas[indice].pagada = pedir_pagada();
                    
                    //si esta pagada, la quita del registro de pendientes, y si no, la agrega
                    if (registro_Ventas[indice].pagada) eliminar_Pendiente(registro_Ventas[indice].id); 
                    else {
                        strcpy(registro_Pendientes[num_pendientes].id_venta, registro_Ventas[indice].id);
                        registro_Pendientes[num_pendientes].fecha = registro_Ventas[indice].fecha;
                        strcpy(registro_Pendientes[num_pendientes].nombre_cliente, registro_Ventas[indice].nombre_cliente);
                        registro_Pendientes[num_pendientes].monto = registro_Ventas[indice].monto;
                        num_pendientes++;
                    }
                    
                    break;
                default:
                    cambiar_color(12);
                    cout << "   Opción inválida...";
                    Sleep(1000);
                    resetear_color();
                    break;
            }
        } while (info < 1 || info > 4);

        cout << "   "; Sleep(500);
        cambiar_color(10);
        escribir = escribir_Archivos("registro_Ventas.txt");
        if (escribir) {
            cambiar_color(10);
            cout << "\n   ***********************************************************************";
            cout << "\n                              Venta editada...";
        } else return false;
        
        Sleep(2250);
        resetear_color();
    }

    return true;
}

bool editar_Pendiente() {
    system("cls || clear");
    bool leer = false, escribir = false;
    int indice = 0, indice_venta = 0, info = 0;
    char id[ID] = "";

    leer = leer_Archivos("registro_Pendientes.txt");
    if (!leer) return false;
    if (checkear_Vacio(num_pendientes)) return true;

    cout << endl;
    pedir_Cstring("ID del pago pendiente a editar", id, ID);
    indice = buscar_Venta(id);

    cambiar_color(9);
    cout << "\n   Buscando pago pendiente...";
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
        cout << "\n   Pago pendiente encontrado!";
        Sleep(750);
        cambiar_color(11);
        cout << endl << "\n                              Pago Pendiente #" << indice+1 << ":" << endl;
        cout << "   ***********************************************************************\n";
        do {
            cambiar_color(14);
            cout << "\n\n   ¿Qué información quiere editar?" << endl;
            cout << "   1. Nombre del cliente\n   2. Monto de la compra\n";
            cambiar_color(9);
            cout << "   Ingrese su opción: ";
            cin >> info;

            cout << endl;
            resetear_color();
            switch (info) {
                case 1:
                    pedir_Cstring("nombre del cliente", registro_Pendientes[indice].nombre_cliente);

                    indice_venta = buscar_Venta(id);
                    if (indice_venta >= 0) strcpy(registro_Ventas[indice_venta].nombre_cliente, registro_Pendientes[indice].nombre_cliente);
                    else return indice_venta;

                    break;
                case 2:
                    registro_Pendientes[indice].monto = pedir_float("monto a pagar (en C$)");

                    indice_venta = buscar_Venta(id);
                    if (indice_venta >= 0) registro_Ventas[indice_venta].monto = registro_Pendientes[indice].monto;
                    else return indice_venta;

                    break;
                default:
                    cambiar_color(12);
                    cout << "   Opción inválida...";
                    Sleep(1000);
                    resetear_color();
                    break;
            }
        } while (info < 1 || info > 4);

        cout << "   "; Sleep(500);
        cambiar_color(10);
        escribir = escribir_Archivos("registro_Ventas.txt");
        if (escribir) {
            cambiar_color(10);
            cout << "\n   ***********************************************************************";
            cout << "\n                              Venta editada...";
        } else return false;
        
        Sleep(2250);
        resetear_color();
    }

    return true;
}

//***************************************************************************************************