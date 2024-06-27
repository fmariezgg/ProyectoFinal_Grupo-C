#include <iostream>
#include <cstring>
#include <ctime>
#include <windows.h>
#include "funciones_externas.h"
using namespace std;

/*
pendientes:
-- quitar la estructura de fecha y solo convertir  el tm* a un string?
-- cuando se ingrese una venta de un cliente que no esta registrado, avisarle al usuario que lo registre primero
-- las funciones de editar y eliminar
-- los procesos de salida: calcular produccion, ingresos, costos y utilidad
*/

//***************************************************************************************************

//todas estas retornan bool para que se pueda checkear si se pudo abrir/leer/escribir al archivo
bool ingresar_Precio();
bool registrar_Vacas(int num); //num es la cantidad de cosas que se van a registrar (para que el usuario no tenga que estar ingresando 1 por 1)
bool registrar_Clientes(int num); 
bool registrar_Ventas(int num); //aqui se registran los pagos pendientes tambien, dependiendo de lo que ingresa el usuario
bool registrar_costos_Fijos(int num);
bool registrar_costos_Variables(int num);

bool mostrar_Precio();
bool mostrar_Vacas();
bool mostrar_Clientes();
bool mostrar_Ventas();
bool mostrar_Pendientes();
bool mostrar_costos_Fijos();
bool mostrar_costos_Variables();

//estas retornan la posicion del id en el arreglo:
//retornan -2 si hubo un error con el archivo y -1 si no se encontro el id (si es >=0, es la posicion del id en el arreglo)
int buscar_Vaca(const char id[ID]);
int buscar_Cliente(const char input[MAX_INPUT], bool buscar_nombre); //buscar por el id o nombre dependiendo del segundo parametro
int buscar_Venta(const char id[ID]);
int buscar_Pendiente(const char id[ID]);
int buscar_costo_Fijo(const char id[ID]);
int buscar_costo_Variable(const char id[ID]);

bool editar_Vacas();
bool editar_Clientes();
bool editar_Ventas(); //si se cambia a que ya se pago, quitar la venta del registro de pendientes
bool editar_Pendientes();
bool editar_costos_Fijos();
bool editar_costos_Variables();

bool eliminar_Vacas();
bool eliminar_Clientes();
bool eliminar_Ventas();
bool eliminar_Pendientes(); //cuando se elimine, que actualice el registro de la venta para que no aparezca como pendiente
bool eliminar_costos_Fijos();
bool eliminar_costos_Variables();

//***************************************************************************************************

bool ingresar_Precio() {
    system("cls || clear");
    cambiar_color(14);
    cout << "\n   Ingrese el precio por galón (en C$): ";
    cin >> precio_galon;

    bool escribir = escribir_Archivos("precio_galon.txt");
    if (!escribir) return false;

    cout << "   ";
    Sleep(500);
    cambiar_color(10);
    cout << "Precio actualizado a: C$" << precio_galon << "...";
    Sleep(1500);
    resetear_color();
    return true;
}

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

bool mostrar_Precio() {
    system("cls || clear");
    bool leer = leer_Archivos("precio_galon.txt");
    if (!leer) return false;

    if (precio_galon == 0.00) {
        cambiar_color(12);
        cout << "\n   No hay precio registrado...";
        Sleep(3000);
        resetear_color();
        return true;
    }

    cambiar_color(10);
    cout << "\n   Precio por galón: C$" << precio_galon;
    Sleep(3000);
    resetear_color();
    return true;
}

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

bool buscar_Vaca(const char id[ID]) {
    system("cls || clear");
    bool leer = leer_Archivos("registro_Vacas.txt");
    if (!leer) return false;

    for (int i = 0; i < num_vacas; i++) {
        if (strcmp(registro_Vacas[i].id, id) == 0) {
            cambiar_color(10);
            cout << "\n   Vaca encontrada...";
            Sleep(1500);
            cout << endl;
            cambiar_color(11);
            cout << endl << "                                  Vaca #" << i+1 << ":" << endl;
            cout << "   ***********************************************************************\n";
            cambiar_color(14);
            cout << "   ID: " << registro_Vacas[i].id << "\n";
            cout << "   Edad: " << registro_Vacas[i].edad << "\n";
            cout << "   Producción diaria: " << registro_Vacas[i].prod_diaria << "\n";
            cout << "   Estado de salud: " << registro_Vacas[i].estado_salud << "\n";
            cout << "   ";
            Sleep(800);
            resetear_color();
            return true;
        }
    }

    cambiar_color(12);
    cout << "\n   Vaca no encontrada...";
    Sleep(1500);
    resetear_color();
    return true;
}

bool buscar_Cliente(const char id[ID]) {
    system("cls || clear");
    bool leer = leer_Archivos("registro_Clientes.txt");
    if (!leer) return false;

    for (int i = 0; i < num_clientes; i++) {
        if (strcmp(registro_Clientes[i].id, id) == 0) {
            cambiar_color(10);
            cout << "\n   Cliente encontrado...";
            Sleep(1500);
            cout << endl;
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
            resetear_color();
            return true;
        }
    }

    cambiar_color(12);
    cout << "\n   Cliente no encontrado...";
    Sleep(1500);
    resetear_color();
    return true;
}

bool buscar_Cliente(const char nombre[MAX_INPUT]) {
    system("cls || clear");
    bool leer = leer_Archivos("registro_Clientes.txt");
    if (!leer) return false;

    for (int i = 0; i < num_clientes; i++) {
        if (strcmp(registro_Clientes[i].nombre, nombre) == 0) {
            cambiar_color(10);
            cout << "\n   Cliente encontrado...";
            Sleep(1500);
            cout << endl;
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
            resetear_color();
            return true;
        }
    }

    cambiar_color(12);
    cout << "\n   Cliente no encontrado...";
    Sleep(1500);
    resetear_color();
    return true;
}

bool buscar_Venta(const char id[ID]) {
    system("cls || clear");
    bool leer = leer_Archivos("registro_Ventas.txt");
    if (!leer) return false;

    for (int i = 0; i < num_ventas; i++) {
        if (strcmp(registro_Ventas[i].id, id) == 0) {
            cambiar_color(10);
            cout << "\n   Venta encontrada...";
            Sleep(1500);
            cout << endl;
            cambiar_color(11);
            cout << endl << "                                  Venta #" << i+1 << ":" << endl;
            cout << "   ***********************************************************************\n";
            cambiar_color(14);
            cout << "   ID: " << registro_Ventas[i].id << "\n";
            cout << "   Fecha: " << registro_Ventas[i].fecha.dia << " de " << registro_Ventas[i].fecha.mes << ", " << registro_Ventas[i].fecha.year << "\n";
            cout << "   Nombre de cliente: " << registro_Ventas[i].nombre_cliente << "\n";
            cout << "   Cantidad de leche: " << registro_Ventas[i].cantidad_leche << "\n";
            cout << "   Monto: " << registro_Ventas[i].monto << "\n";
            cout << "   ";
            Sleep(800);
            resetear_color();
            return true;
        }
    }

    cambiar_color(12);
    cout << "\n   Venta no encontrada...";
    Sleep(1500);
    resetear_color();
    return true;
}

bool buscar_Pendiente(const char id[ID]) {
    system("cls || clear");
    bool leer = leer_Archivos("registro_Pendientes.txt");
    if (!leer) return false;

    for (int i = 0; i < num_pendientes; i++) {
        if (strcmp(registro_Pendientes[i].id_venta, id) == 0) {
            cambiar_color(10);
            cout << "\n   Pago pendiente encontrado...";
            Sleep(1500);
            cout << endl;
            cambiar_color(11);
            cout << endl << "                              Pago Pendiente #" << i+1 << ":" << endl;
            cout << "   ***********************************************************************\n";
            cambiar_color(14);
            cout << "   ID de venta: " << registro_Pendientes[i].id_venta << "\n";
            cout << "   Fecha: " << registro_Pendientes[i].fecha.dia << " de " << registro_Pendientes[i].fecha.mes << ", " << registro_Pendientes[i].fecha.year << "\n";
            cout << "   Nombre de cliente: " << registro_Pendientes[i].nombre_cliente << "\n";
            cout << "   Monto: " << registro_Pendientes[i].monto << "\n";
            cout << "   ";
            Sleep(800);
            resetear_color();
            return true;
        }
    }

    cambiar_color(12);
    cout << "\n   Pago pendiente no encontrado...";
    Sleep(1500);
    resetear_color();
    return true;
}

bool buscar_costo_Fijo(const char id[ID]) {
    system("cls || clear");
    bool leer = leer_Archivos("registro_costos_Fijos.txt");
    if (!leer) return false;

    for (int i = 0; i < num_costos_Fijos; i++) {
        if (strcmp(registro_costos_Fijos[i].id, id) == 0) {
            cambiar_color(10);
            cout << "\n   Costo fijo encontrado...";
            Sleep(1500);
            cout << endl;
            cambiar_color(11);
            cout << endl << "                              Costo Fijo #" << i+1 << ":" << endl;
            cout << "   ***********************************************************************\n";
            cambiar_color(14);
            cout << "   ID: " << registro_costos_Fijos[i].id << "\n";
            cout << "   Monto: " << registro_costos_Fijos[i].monto << "\n";
            cout << "   Descripción: " << registro_costos_Fijos[i].descripcion << "\n";
            cout << "   ";
            Sleep(800);
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

bool buscar_costo_Variable(const char id[ID]) {
    system("cls || clear");
    bool leer = leer_Archivos("registro_costos_Variables.txt");
    if (!leer) return false;

    for (int i = 0; i < num_costos_Variables; i++) {
        if (strcmp(registro_costos_Variables[i].id, id) == 0) {
            cambiar_color(10);
            cout << "\n   Costo variable encontrado...";
            Sleep(1500);
            cout << endl;
            cambiar_color(11);
            cout << endl << "                            Costo Variable #" << i+1 << ":" << endl;
            cout << "   ***********************************************************************\n";
            cambiar_color(14);
            cout << "   ID: " << registro_costos_Variables[i].id << "\n";
            cout << "   Monto: " << registro_costos_Variables[i].monto << "\n";
            cout << "   Descripción: " << registro_costos_Variables[i].descripcion << "\n";
            cout << "   ";
            Sleep(800);
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

bool editar_Vacas() {
    system("cls || clear");
    bool leer = leer_Archivos("registro_Vacas.txt");
    if (!leer) return false;

    char id[ID] = "";
    pedir_Cstring("ID de la vaca a editar", id, ID);

    for (int i = 0; i < num_vacas; i++) {
        if (strcmp(registro_Vacas[i].id, id) == 0) {
            cambiar_color(11);
            cout << endl << "                                  Vaca #" << i+1 << ":" << endl;
            cout << "   ***********************************************************************\n";
            resetear_color();
            pedir_Cstring("ID", registro_Vacas[i].id, ID);
            registro_Vacas[i].edad = pedir_int("edad (en años)");
            registro_Vacas[i].prod_diaria = pedir_int("producción diaria (en galones)");
            pedir_Cstring("estado de salud", registro_Vacas[i].estado_salud);
            cambiar_color(10);
            cout << "   Vaca editada...";
            Sleep(1500);
            resetear_color();
            return true;
        }
    }

    cambiar_color(12);
    cout << "\n   Vaca no encontrada...";
    Sleep(1500);
    resetear_color();
    return true;
}

bool editar_Clientes() {
    system("cls || clear");
    bool leer = leer_Archivos("registro_Clientes.txt");
    if (!leer) return false;

    char id[ID] = "";
    pedir_Cstring("ID del cliente a editar", id, ID);

    for (int i = 0; i < num_clientes; i++) {
        if (strcmp(registro_Clientes[i].id, id) == 0) {
            cambiar_color(11);
            cout << endl << "                                Cliente #" << i+1 << ":" << endl;
            cout << "   ***********************************************************************\n";
            resetear_color();
            pedir_Cstring("ID", registro_Clientes[i].id, ID);
            pedir_Cstring("nombre", registro_Clientes[i].nombre);
            pedir_Cstring("dirección", registro_Clientes[i].direccion);
            pedir_Cstring("contacto", registro_Clientes[i].contacto);
            cambiar_color(10);
            cout << "   Cliente editado...";
            Sleep(1500);
            resetear_color();
            return true;
        }
    }

    cambiar_color(12);
    cout << "\n   Cliente no encontrado...";
    Sleep(1500);
    resetear_color();
    return true;
}

bool editar_Ventas() {
    system("cls || clear");
    bool leer_Ventas = leer_Archivos("registro_Ventas.txt");
    bool leer_Pendientes = leer_Archivos("registro_Pendientes.txt");
    if (!leer_Ventas || !leer_Pendientes) return false;

    char id[ID] = "";
    pedir_Cstring("ID de la venta a editar", id, ID);

    for (int i = 0; i < num_ventas; i++) {
        if (strcmp(registro_Ventas[i].id, id) == 0) {
            cambiar_color(11);
            cout << endl << "                                  Venta #" << i+1 << ":" << endl;
            cout << "   ***********************************************************************\n";
            resetear_color();
            pedir_Cstring("ID", registro_Ventas[i].id, ID);
            pedir_Cstring("nombre del cliente", registro_Ventas[i].nombre_cliente);

            tm *time = obtener_fecha();
            registro_Ventas[i].fecha.dia = time->tm_mday;
            strcpy(registro_Ventas[i].fecha.mes, meses[time->tm_mon]);
            registro_Ventas[i].fecha.year = time->tm_year + 1900;

            registro_Ventas[i].cantidad_leche = pedir_int("cantidad de leche (en galones)");
            registro_Ventas[i].monto = precio_galon * registro_Ventas[i].cantidad_leche;
            registro_Ventas[i].pagada = pedir_pagada();

            if (!registro_Ventas[i].pagada) {
                strcpy(registro_Pendientes[num_pendientes].id_venta, registro_Ventas[i].id);
                registro_Pendientes[num_pendientes].fecha = registro_Ventas[i].fecha;
                strcpy(registro_Pendientes[num_pendientes].nombre_cliente, registro_Ventas[i].nombre_cliente);
                registro_Pendientes[num_pendientes].monto = registro_Ventas[i].monto;
                cambiar_color(10);
                cout << "   Pago pendiente registrado...";
                Sleep(650);
                resetear_color();
                cout << endl;
                num_pendientes++;
            }

            cambiar_color(10);
            cout << "   Venta editada...";
            Sleep(1500);
            resetear
            return true;
        }
    }
    cambiar_color(11);
    cout << "\n   Venta no encontrada...";
    Sleep(1500);
    resetear_color();
    return true;
}

bool editar_Pendientes() {
    system("cls || clear");
    bool leer = leer_Archivos("registro_Pendientes.txt");
    if (!leer) return false;

    char id[ID] = "";
    pedir_Cstring("ID del pago pendiente a editar", id, ID);

    for (int i = 0; i < num_pendientes; i++) {
        if (strcmp(registro_Pendientes[i].id_venta, id) == 0) {
            cambiar_color(11);
            cout << endl << "                              Pago Pendiente #" << i+1 << ":" << endl;
            cout << "   ***********************************************************************\n";
            resetear_color();
            pedir_Cstring("ID de la venta", registro_Pendientes[i].id_venta, ID);
            registro_Pendientes[i].fecha = pedir_fecha();
            pedir_Cstring("nombre del cliente", registro_Pendientes[i].nombre_cliente);
            registro_Pendientes[i].monto = pedir_float("monto (en C$)");
            cambiar_color(10);
            cout << "   Pago pendiente editado...";
            Sleep(1500);
            resetear_color();
            return true;
        }
    }

    cambiar_color(12);
    cout << "\n   Pago pendiente no encontrado...";
    Sleep(1500);
    resetear_color();
    return true;
}

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

bool eliminar_Vaca() {
    system("cls || clear");
    bool leer = leer_Archivos("registro_Vacas.txt");
    if (!leer) return false;

    char id[ID] = "";
    pedir_Cstring("ID de la vaca a eliminar", id, ID);

    for (int i = 0; i < num_vacas; i++) {
        if (strcmp(registro_Vacas[i].id, id) == 0) {
            for (int j = i; j < num_vacas; j++) {
                registro_Vacas[j] = registro_Vacas[j+1];
            }
            num_vacas--;
            cambiar_color(10);
            cout << "\n   Vaca eliminada...";
            Sleep(1500);
            resetear_color();
            return true;
        }
    }

    cambiar_color(12);
    cout << "\n   Vaca no encontrada...";
    Sleep(1500);
    resetear_color();
    return true;
}

bool eliminar_Cliente() {
    system("cls || clear");
    bool leer = leer_Archivos("registro_Clientes.txt");
    if (!leer) return false;

    char id[ID] = "";
    pedir_Cstring("ID del cliente a eliminar", id, ID);

    for (int i = 0; i < num_clientes; i++) {
        if (strcmp(registro_Clientes[i].id, id) == 0) {
            for (int j = i; j < num_clientes; j++) {
                registro_Clientes[j] = registro_Clientes[j+1];
            }
            num_clientes--;
            cambiar_color(10);
            cout << "\n   Cliente eliminado...";
            Sleep(1500);
            resetear_color();
            return true;
        }
    }

    cambiar_color(12);
    cout << "\n   Cliente no encontrado...";
    Sleep(1500);
    resetear_color();
    return true;
}

bool eliminar_Venta() {
    system("cls || clear");
    bool leer_Ventas = leer_Archivos("registro_Ventas.txt");
    bool leer_Pendientes = leer_Archivos("registro_Pendientes.txt");
    if (!leer_Ventas || !leer_Pendientes) return false;

    char id[ID] = "";
    pedir_Cstring("ID de la venta a eliminar", id, ID);

    for (int i = 0; i < num_ventas; i++) {
        if (strcmp(registro_Ventas[i].id, id) == 0) {
            for (int j = i; j < num_ventas; j++) {
                registro_Ventas[j] = registro_Ventas[j+1];
            }
            num_ventas--;
            for (int j = 0; j < num_pendientes; j++) {
                if (strcmp(registro_Pendientes[j].id_venta, id) == 0) {
                    for (int k = j; k < num_pendientes; k++) {
                        registro_Pendientes[k] = registro_Pendientes[k+1];
                    }
                    num_pendientes--;
                    break;
                }
            }
            cambiar_color(10);
            cout << "\n   Venta eliminada...";
            Sleep(1500);
            resetear_color();
            return true;
        }
    }

    cambiar_color(12);
    cout << "\n   Venta no encontrada...";
    Sleep(1500);
    resetear_color();
    return true;
}

bool eliminar_Pendiente() {
    system("cls || clear");
    bool leer = leer_Archivos("registro_Pendientes.txt");
    if (!leer) return false;

    char id[ID] = "";
    pedir_Cstring("ID del pago pendiente a eliminar", id, ID);

    for (int i = 0; i < num_pendientes; i++) {
        if (strcmp(registro_Pendientes[i].id_venta, id) == 0) {
            for (int j = i; j < num_pendientes; j++) {
                registro_Pendientes[j] = registro_Pendientes[j+1];
            }
            num_pendientes--;
            cambiar_color(10);
            cout << "\n   Pago pendiente eliminado...";
            Sleep(1500);
            resetear_color();
            return true;
        }
    }

    cambiar_color(12);
    cout << "\n   Pago pendiente no encontrado...";
    Sleep(1500);
    resetear_color();
    return true;
}

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



