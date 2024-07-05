#include "../headers/funciones_externas.h"

#ifndef MOD_CLIENTES_CPP
#define MOD_CLIENTES_CPP
#include "mod_clientes.cpp"
#endif

using namespace std;
using namespace LLC;

//implementaciones de todas las funciones del modulo de gestion de ventas y de pagos pendientes:
//como no hay prototipos, el orden esta medio raro para que no hayan errores de undefined reference
//***************************************************************************************************

int buscar_Venta(const char id[ID]) {
    for (int i = 0; i < num_ventas; i++) {
        if (strcmp(registro_Ventas[i].id, id) == 0) return i;
    }
    
    return -1;
}

int buscar_Pendiente(const char id[ID]) { 
    for (int i = 0; i < num_pendientes; i++) {
        if (strcmp(registro_Pendientes[i].id_venta, id) == 0) return i;
    }
    
    return -1;
}

//***************************************************************************************************

bool registrar_Ventas() {
    system("cls || clear");
    char tempID[ID] = "", temp_nombre[MAX_INPUT] = "", input[3] = "";
    bool leer_Ventas = false, leer_Precio = false, leer_Pendientes = false, leer_Clientes = false;
    bool escribir_Ventas = false, escribir_Pendientes = false;

    leer_Ventas = leer_Archivos("registro_Ventas.txt");
    leer_Pendientes = leer_Archivos("registro_Pendientes.txt");
    leer_Clientes = leer_Archivos("registro_Clientes.txt"); //se lee los clientes para poder ver si el cliente ingresado esta registrado o no
    leer_Precio = leer_Archivos("precio_galon.txt"); //se lee el precio para poder calcular el monto de la venta
    if (!leer_Ventas || !leer_Pendientes || !leer_Precio || !leer_Clientes) return false; //si cualquiera de las lecturas falla, retornar false

    //si el archivo precio_galon.txt no existe, se va a crear, pero va a estar vacio, entonces hay que pedir un precio para poder calcular el monto de las ventas
    if (precio_galon == 0.00) {
        _colSET(cRED);
        cout << endl << "   Archivo 'precio_galon.txt' vacío...\n";
        precio_galon = pedir_float("precio");

        bool check = escribir_Archivos("precio_galon.txt");
        _colSET(cGREEN);
        if (check) cout << "   Precio guardado...";
        else return false;
        this_thread::sleep_for(chrono::milliseconds(500));
        cout << endl;
        _colRESET();
    }

    do {
        _colSET(cCYAN);
        cout << endl << "                                  Venta #" << num_ventas+1 << ":" << endl;
        cout << "   ***********************************************************************\n";
        cin.ignore();
        _colRESET();
        
        while (true) {
            pedir_Cstring("ID", tempID, ID);

            if (buscar_Venta(tempID) >= 0) {
                _colSET(cRED);
                cout << "   ERROR: ID ya registrado...";
                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(1500));
                cout << endl;
                continue; //si se encontro el id ingresado, volver a pedirlo
            } else if (buscar_Venta(tempID) == -1) {
                strcpy(registro_Ventas[num_ventas].id, tempID); //si no se encontro, se guarda en el registro
                break;
            } else if (buscar_Venta(tempID) == -2) return false;
        }

        while (true) { //ver si el cliente ingresado esta registrado o no
            pedir_Cstring("nombre del cliente", temp_nombre);

            if (buscar_Cliente(temp_nombre, true) == -1) {
                _colSET(cRED);
                cout << "   ERROR: Cliente debe estar registrado antes de registrar la venta...";
                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(1500));
                cout << endl;

                strcpy(registro_Ventas[num_ventas].id, ""); //si el cliente no esta registrado, se borra el id de la venta
                escribir_Ventas = escribir_Archivos("registro_Ventas.txt"); //y se escriben los cambios que habia hecho el usuario
                escribir_Pendientes = escribir_Archivos("registro_Pendientes.txt");
                return (escribir_Ventas && escribir_Pendientes); //retornar el and de los dos resultados
            }
            
            else if (buscar_Cliente(temp_nombre, true) >= 0) {
                strcpy(registro_Ventas[num_ventas].nombre_cliente, temp_nombre);
                break;
            } else if (buscar_Cliente(temp_nombre, true) == -2) return false;
        }

        continuar("\n   ¿Desea ingresar la fecha manualmente? (si/no) ", input);

        if (si_no(input) == 1) {
            cout << endl;

            while (true) {
                pedir_Cstring("mes (en minúscula)", registro_Ventas[num_ventas].fecha.mes, ID);

                if (checkear_mes(registro_Ventas[num_ventas].fecha.mes) < 0) {
                    _colSET(cRED);
                    cout << "   ERROR: Mes inválido...";
                    _colRESET();
                    this_thread::sleep_for(chrono::milliseconds(1500));
                    cout << endl;
                    continue;
                } else break;
            }

            while (true) {
                registro_Ventas[num_ventas].fecha.dia = pedir_int("día");
                int num_mes = checkear_mes(registro_Ventas[num_ventas].fecha.mes);
                if (registro_Ventas[num_ventas].fecha.dia > dias_meses[num_mes]) {
                    _colSET(cRED);
                    cout << "   ERROR: Día inválido para el mes ingresado...";
                    _colRESET();
                    this_thread::sleep_for(chrono::milliseconds(1500));
                    cout << endl;
                } else break;
            }

            registro_Ventas[num_ventas].fecha.year = pedir_int("año");
        } else if (si_no(input) == 0) {
            _colSET(cTEAL);
            cout << "   De acuerdo, se usará la fecha actual...";
            _colRESET();
            cout << endl << endl;
            tm *time = obtener_fecha(); //obtiene la fecha actual para registrar la venta
            registro_Ventas[num_ventas].fecha.dia = time->tm_mday;
            strcpy(registro_Ventas[num_ventas].fecha.mes, meses[time->tm_mon]); //usar el numero de mes como indice para retornar el nombre del mes
            registro_Ventas[num_ventas].fecha.year = time->tm_year + 1900; //sumarle 1900 pq time->tm_year es el numero de años *desde* 1900
        }        
        
        registro_Ventas[num_ventas].cantidad_leche = pedir_float("cantidad de leche (en galones)");
        registro_Ventas[num_ventas].monto = precio_galon * registro_Ventas[num_ventas].cantidad_leche; //calcular monto automaticamente
        registro_Ventas[num_ventas].pagada = pedir_pagada();

        //si se ingresa que no se ha pagado la compra, agregar los datos del cliente y la compra al registro de pagos pendientes
        if (!registro_Ventas[num_ventas].pagada) {
            strcpy(registro_Pendientes[num_pendientes].id_venta, registro_Ventas[num_ventas].id);
            registro_Pendientes[num_pendientes].fecha = registro_Ventas[num_ventas].fecha;
            strcpy(registro_Pendientes[num_pendientes].nombre_cliente, registro_Ventas[num_ventas].nombre_cliente);
            registro_Pendientes[num_pendientes].monto = registro_Ventas[num_ventas].monto;
            _colSET(cGREEN);
            cout << "   Pago pendiente registrado...";
            this_thread::sleep_for(chrono::milliseconds(500));
            _colRESET();
            cout << endl << endl;
            num_pendientes++;
        }

        num_ventas++;
        strcpy(input, "");
        continuar("   ¿Desea registrar más ventas? (si/no) ", input);

    } while (((strcmp(input, "s") == 0) || (strcmp(input, "S") == 0) || (strcmp(input, "si") == 0) || (strcmp(input, "Si") == 0) || (strcmp(input, "sI") == 0) || (strcmp(input, "SI") == 0)));

    escribir_Ventas = escribir_Archivos("registro_Ventas.txt");
    escribir_Pendientes = escribir_Archivos("registro_Pendientes.txt");
    if (!escribir_Ventas || !escribir_Pendientes) return false; //lo mismo que las operaciones de lectura

    cout << "   ";
    this_thread::sleep_for(chrono::milliseconds(500));
    _colRESET();
    return true;
}

//***************************************************************************************************

bool mostrar_Ventas() {
    system("cls || clear");
    char pagada[3] = "";
    bool leer = leer_Archivos("registro_Ventas.txt");
    if (!leer) return false;

    if (checkear_Vacio(num_ventas)) return true;

    _colSET(cGREEN);
    cout << "\n   Mostrando ventas registradas...";
    this_thread::sleep_for(chrono::milliseconds(800));

    cout << endl;
    for (int i = 0; i < num_ventas; i++) {
        //para que 'pagada' no se imprima como 0 o 1, se le asigna un C-string dependiendo del valor de registro_Ventas[i].pagada usando una operacion ternaria
        strcpy(pagada, registro_Ventas[i].pagada ? "Si" : "No");

        _colSET(cCYAN);
        cout << endl << "                                  Venta #" << i+1 << ":" << endl;
        cout << "   ***********************************************************************\n";
        _colSET(cLIGHT_YELLOW);
        cout << "   ID: " << registro_Ventas[i].id << "\n";
        cout << "   Fecha: " << registro_Ventas[i].fecha.dia << " de " << registro_Ventas[i].fecha.mes << ", " << registro_Ventas[i].fecha.year << "\n";
        cout << "   Nombre de cliente: " << registro_Ventas[i].nombre_cliente << "\n";
        cout << "   Cantidad de leche: " << registro_Ventas[i].cantidad_leche << " galón(es)\n";
        cout << "   Monto: C$" << registro_Ventas[i].monto << "\n";
        cout << "   ¿Está pagada? "; _colSET(cTEAL); cout << pagada << endl;
        cout << "   ";
        this_thread::sleep_for(chrono::milliseconds(800));
    }

    _colSET(cCYAN);
    cout << endl << "   ***********************************************************************\n";
    cout << "   Presione 'Enter' para continuar...";
    cin.ignore();
    cin.get();
    _colRESET();
    return true;
}

bool mostrar_Pendientes() {
    system("cls || clear");
    bool leer = leer_Archivos("registro_Pendientes.txt");
    if (!leer) return false;

    if (checkear_Vacio(num_pendientes)) return true;

    _colSET(cGREEN);
    cout << "\n   Mostrando pagos pendientes...";
    this_thread::sleep_for(chrono::milliseconds(800));

    cout << endl;
    for (int i = 0; i < num_pendientes; i++) {
        _colSET(cCYAN);
        cout << endl << "                              Pago Pendiente #" << i+1 << ":" << endl;
        cout << "   ***********************************************************************\n";
        _colSET(cLIGHT_YELLOW);
        cout << "   ID de venta: " << registro_Pendientes[i].id_venta << "\n";
        cout << "   Fecha: " << registro_Pendientes[i].fecha.dia << " de " << registro_Pendientes[i].fecha.mes << ", " << registro_Pendientes[i].fecha.year << "\n";
        cout << "   Nombre de cliente: " << registro_Pendientes[i].nombre_cliente << "\n";
        cout << "   Monto a pagar: C$" << registro_Pendientes[i].monto << endl;
        cout << "   ";
        this_thread::sleep_for(chrono::milliseconds(800));
    }

    _colSET(cCYAN);
    cout << endl << "   ***********************************************************************\n";
    cout << "   Presione 'Enter' para continuar...";
    cin.ignore();
    cin.get();
    _colRESET();
    return true;
}

//***************************************************************************************************

int eliminar_Pendiente(const char id[ID]) {
    int indice = 0, indice_venta = 0;
    bool leer_Pendiente = false, leer_Venta = false, escribir_Pendiente = false, escribir_Venta = false;

    leer_Pendiente = leer_Archivos("registro_Pendientes.txt");
    leer_Venta = leer_Archivos("registro_Ventas.txt");
    if (!leer_Pendiente || !leer_Venta) return -2;
    if (checkear_Vacio(num_pendientes)) return 1;

    indice = buscar_Pendiente(id);
    if (indice < 0) return indice;

    //si se va a eliminar un pago pendiente, es pq ya se pago, entonces hay que actualizar el registro de la venta correspondiente
    indice_venta = buscar_Venta(registro_Pendientes[indice].id_venta);
    if (indice_venta >= 0) registro_Ventas[indice_venta].pagada = true;
    else return indice_venta;

    for (int i = indice; i < num_pendientes-1; i++) {
        registro_Pendientes[i] = registro_Pendientes[i+1];
    } num_pendientes--;

    escribir_Pendiente = escribir_Archivos("registro_Pendientes.txt");
    escribir_Venta = escribir_Archivos("registro_Ventas.txt");
    if (escribir_Pendiente && escribir_Venta) return 0;
    else return -2;
}

int eliminar_Venta(const char id[ID]) {
    int indice = 0;
    bool leer_Venta = false, escribir_Venta = false, leer_Pendiente = false, escribir_Pendiente = false;

    leer_Venta = leer_Archivos("registro_Ventas.txt");
    leer_Pendiente = leer_Archivos("registro_Pendientes.txt");
    if (!leer_Venta || !leer_Pendiente) return -2;
    if (checkear_Vacio(num_ventas)) return 1;

    indice = buscar_Venta(id);
    if (indice < 0) return indice;

    //si la venta no esta pagada, significa que tambien estaba registrada como pendiente, entonces se elimina de ahi igual
    if (!registro_Ventas[indice].pagada) eliminar_Pendiente(id);

    for (int i = indice; i < num_ventas-1; i++) {
        registro_Ventas[i] = registro_Ventas[i+1];
    } num_ventas--;

    escribir_Venta = escribir_Archivos("registro_Ventas.txt");
    escribir_Pendiente = escribir_Archivos("registro_Pendientes.txt");
    if (escribir_Venta && escribir_Pendiente) return 0;
    else return -2;
}

//***************************************************************************************************

bool editar_Venta() {
    system("cls || clear");
    bool leer_Ventas = false, escribir_Ventas = false, leer_Pendientes = false, escribir_Pendientes = false, leer_Clientes = false, leer_Precio = false;
    int indice = 0, indice_pendiente = 0, info = 0;
    char id[ID] = "", temp_nombre[MAX_INPUT] = "";

    leer_Pendientes = leer_Archivos("registro_Pendientes.txt");
    leer_Ventas = leer_Archivos("registro_Ventas.txt");
    leer_Clientes = leer_Archivos("registro_Clientes.txt");
    leer_Precio = leer_Archivos("precio_galon.txt");
    if (!leer_Pendientes || !leer_Ventas || !leer_Precio || !leer_Clientes) return false;
    if (checkear_Vacio(num_ventas)) return true;

    cout << endl;
    pedir_Cstring("ID de la venta a editar", id, ID);
    indice = buscar_Venta(id);
    indice_pendiente = buscar_Pendiente(id);

    _colSET(cTEAL);
    cout << "\n   Buscando venta...";
    this_thread::sleep_for(chrono::milliseconds(800));
    _colRESET();

    if (indice == -1) {
        _colSET(cRED);
        cout << "\n   ERROR: ID ingresado no esta registrado...";
        this_thread::sleep_for(chrono::milliseconds(2250));
        _colRESET();
        return true;
    } else if (indice == -2) return false;

    else if (indice >= 0) {
        _colSET(cGREEN);
        cout << "\n   Venta encontrada!";
        this_thread::sleep_for(chrono::milliseconds(500));
        _colSET(cCYAN);
        cout << endl << "\n                                  Venta #" << indice+1 << ":" << endl;
        cout << "   ***********************************************************************";
        do {
            _colSET(cLIGHT_YELLOW);
            cout << "\n\n   ¿Qué información quiere editar?" << endl;
            cout << "   1. Fecha\n   2. Nombre del cliente\n   3. Cantidad de leche comprada\n   4. Monto\n   5. ¿Está pagada?\n";
            _colSET(cTEAL);
            cout << "   Ingrese su opción: ";
            cin >> info;

            if (cin.fail()) {
                error_opcion();
                continue;
            }

            cout << endl;
            _colRESET();
            switch (info) {
                case 1:
                    cout << endl;
                    _colSET(cPINK);
                    cout << "   Fecha actual: " << registro_Ventas[indice].fecha.dia << " de " << registro_Ventas[indice].fecha.mes << ", " << registro_Ventas[indice].fecha.year << endl;

                    while (true) {
                        pedir_Cstring("mes (en minúscula)", registro_Ventas[indice].fecha.mes, ID);

                        if (checkear_mes(registro_Ventas[indice].fecha.mes) < 0) {
                            _colSET(cRED);
                            cout << "   ERROR: Mes inválido...";
                            _colRESET();
                            this_thread::sleep_for(chrono::milliseconds(1500));
                            cout << endl;
                            continue;
                        } else break;
                    }

                    while (true) {
                        registro_Ventas[indice].fecha.dia = pedir_int("día");
                        int num_mes = checkear_mes(registro_Ventas[indice].fecha.mes);
                        if (registro_Ventas[indice].fecha.dia > dias_meses[num_mes]) {
                            _colSET(cRED);
                            cout << "   ERROR: Día inválido para el mes ingresado...";
                            _colRESET();
                            this_thread::sleep_for(chrono::milliseconds(1500));
                            cout << endl;
                        } else break;
                    }

                    registro_Ventas[indice].fecha.year = pedir_int("año");
                    
                    //si la venta no esta pagada, tambien actualizar la fecha en el registro de pendientes
                    if (!registro_Ventas[indice].pagada) registro_Pendientes[indice_pendiente].fecha = registro_Ventas[indice].fecha;

                    break;
                case 2:
                    while (true) {
                        pedir_Cstring("nombre del cliente", temp_nombre);

                        if (buscar_Cliente(temp_nombre, true) >= 0) {
                            _colSET(cRED);
                            cout << "   ERROR: Cliente debe estar registrado para editar la venta...";
                            _colRESET();
                            this_thread::sleep_for(chrono::milliseconds(1500));
                            return true;
                        } else if (buscar_Cliente(temp_nombre, true) == -1) {
                            strcpy(registro_Ventas[indice].nombre_cliente, temp_nombre);
                            break;
                        } else if (buscar_Cliente(temp_nombre, true) == -2) return false;
                    }

                    //si la venta tambien estaba registrada como pendiente, actualizar el nombre en el registro de pendientes
                    if (!registro_Ventas[indice].pagada) strcpy(registro_Pendientes[indice_pendiente].nombre_cliente, registro_Ventas[indice].nombre_cliente);

                    break;
                case 3:
                    registro_Ventas[indice].cantidad_leche = pedir_float("cantidad de leche (en galones)");

                    if (precio_galon == 0.00) { //si el precio es 0, no se puede calcular la cantidad de leche
                        _colSET(cRED);
                        cout << "   ERROR: Precio por galón no registrado...";
                        this_thread::sleep_for(chrono::milliseconds(2250));
                        _colRESET();
                        return true;
                    }

                    registro_Ventas[indice].monto = precio_galon * registro_Ventas[indice].cantidad_leche; //si se cambio la cantidad de leche, actualizar el monto

                    //si no esta pagada, tambien actualizar el monto en el registro de pendientes
                    if (!registro_Ventas[indice].pagada && indice_pendiente >= 0) registro_Pendientes[indice_pendiente].monto = registro_Ventas[indice].monto;
                    break;
                case 4:
                    registro_Ventas[indice].monto = pedir_float("monto (en C$)");

                    if (precio_galon == 0.00) {
                        _colSET(cRED);
                        cout << "   ERROR: Precio por galón no registrado...";
                        this_thread::sleep_for(chrono::milliseconds(2250));
                        _colRESET();
                        return true;
                    }

                    registro_Ventas[indice].cantidad_leche = registro_Ventas[indice].monto / precio_galon; //si se cambio el monto, actualizar la cantidad de leche

                    //si no esta pagada, tambien actualizar el monto en el registro de pendientes
                    if (!registro_Ventas[indice].pagada && indice_pendiente >= 0) registro_Pendientes[indice_pendiente].monto = registro_Ventas[indice].monto;

                    break;
                case 5:
                    registro_Ventas[indice].pagada = pedir_pagada();
                    
                    //si esta pagada, la quita del registro de pendientes, y si no, la agrega
                    if (registro_Ventas[indice].pagada) eliminar_Pendiente(registro_Pendientes[indice_pendiente].id_venta);
                    else {  
                        strcpy(registro_Pendientes[num_pendientes].id_venta, registro_Ventas[indice].id);
                        registro_Pendientes[num_pendientes].fecha = registro_Ventas[indice].fecha;
                        strcpy(registro_Pendientes[num_pendientes].nombre_cliente, registro_Ventas[indice].nombre_cliente);
                        registro_Pendientes[num_pendientes].monto = registro_Ventas[indice].monto;
                        num_pendientes++;
                    }
                    
                    break;
                default:
                    _colSET(cRED);
                    cout << "   Opción inválida...";
                    this_thread::sleep_for(chrono::milliseconds(1000));
                    _colRESET();
                    break;
            }
        } while (info < 1 || info > 5);

        cout << "   ";
        this_thread::sleep_for(chrono::milliseconds(500));
        _colSET(cGREEN);
        escribir_Ventas = escribir_Archivos("registro_Ventas.txt");
        escribir_Pendientes = escribir_Archivos("registro_Pendientes.txt");
        if (escribir_Ventas && escribir_Pendientes) {
            _colSET(cGREEN);
            cout << "\n   ***********************************************************************";
            cout << "\n                              Venta editada...";
        } else return false;
        
        this_thread::sleep_for(chrono::milliseconds(2250));
        _colRESET();
    }

    return true;
}

bool editar_Pendiente() {
    system("cls || clear");
    bool leer_Ventas = false, escribir_Ventas = false, leer_Pendientes = false, escribir_Pendientes = false, leer_Clientes = false, leer_Precio = false;
    int indice = 0, indice_venta = 0, info = 0;
    char id[ID] = "", temp_nombre[MAX_INPUT] = "";

    leer_Pendientes = leer_Archivos("registro_Pendientes.txt");
    leer_Ventas = leer_Archivos("registro_Ventas.txt");
    leer_Clientes = leer_Archivos("registro_Clientes.txt");
    leer_Precio = leer_Archivos("precio_galon.txt");
    if (!leer_Pendientes || !leer_Ventas || !leer_Precio || !leer_Clientes) return false;
    if (checkear_Vacio(num_pendientes)) return true;

    cout << endl;
    pedir_Cstring("ID del pago pendiente a editar", id, ID);
    indice = buscar_Pendiente(id);
    indice_venta = buscar_Venta(id);

    _colSET(cTEAL);
    cout << "\n   Buscando pago pendiente...";
    this_thread::sleep_for(chrono::milliseconds(800));
    _colRESET();

    if (indice == -1) {
        _colSET(cRED);
        cout << "\n   ERROR: ID ingresado no esta registrado...";
        this_thread::sleep_for(chrono::milliseconds(2250));
        _colRESET();
        return true;
    } else if (indice == -2) return false;

    else if (indice >= 0) {
        _colSET(cGREEN);
        cout << "\n   Pago pendiente encontrado!";
       this_thread::sleep_for(chrono::milliseconds(500));
        _colSET(cCYAN);
        cout << endl << "\n                              Pago Pendiente #" << indice+1 << ":" << endl;
        cout << "   ***********************************************************************";
        do {
            _colSET(cLIGHT_YELLOW);
            cout << "\n\n   ¿Qué información quiere editar?" << endl;
            cout << "   1. Fecha\n   2. Nombre del cliente\n   3. Monto de la compra\n";
            _colSET(cTEAL);
            cout << "   Ingrese su opción: ";
            cin >> info;

            if (cin.fail()) {
                error_opcion();
                continue;
            }

            cout << endl;
            _colRESET();
            switch (info) {
                case 1:
                    cout << endl;
                    _colSET(cPINK);
                    cout << "   Fecha actual: " << registro_Pendientes[indice].fecha.dia << " de " << registro_Pendientes[indice].fecha.mes << ", " << registro_Pendientes[indice].fecha.year << endl;

                    while (true) {
                        pedir_Cstring("mes (en minúscula)", registro_Pendientes[indice].fecha.mes, ID);

                        if (checkear_mes(registro_Pendientes[indice].fecha.mes) < 0) {
                            _colSET(cRED);
                            cout << "   ERROR: Mes inválido...";
                            _colRESET();
                            this_thread::sleep_for(chrono::milliseconds(1500));
                            cout << endl;
                            continue;
                        } else break;
                    }

                    while (true) {
                        registro_Pendientes[indice].fecha.dia = pedir_int("día");
                        int num_mes = checkear_mes(registro_Pendientes[indice].fecha.mes);
                        if (registro_Pendientes[indice].fecha.dia > dias_meses[num_mes]) {
                            _colSET(cRED);
                            cout << "   ERROR: Día inválido para el mes ingresado...";
                            _colRESET();
                            this_thread::sleep_for(chrono::milliseconds(1500));
                            cout << endl;
                        } else break;
                    }

                    registro_Pendientes[indice].fecha.year = pedir_int("año");
                    
                    //tambien actualizar la fecha en el registro de ventas
                    registro_Ventas[indice_venta].fecha = registro_Pendientes[indice].fecha;

                    break;
                case 2:
                    while (true) { 
                        pedir_Cstring("nombre del cliente", temp_nombre);

                        if (buscar_Cliente(temp_nombre, true) >= 0) {
                            _colSET(cRED);
                            cout << "   ERROR: Cliente debe estar registrado para editar el pago pendiente...";
                            _colRESET();
                            this_thread::sleep_for(chrono::milliseconds(1500));
                            return true;
                        } else if (buscar_Cliente(temp_nombre, true) == -1) {
                            strcpy(registro_Pendientes[indice].nombre_cliente, temp_nombre);
                            break;
                        } else if (buscar_Cliente(temp_nombre, true) == -2) return false;
                    }

                    //hay que actualizar el nombre del cliente en la venta correspondiente
                    if (indice_venta >= 0) strcpy(registro_Ventas[indice_venta].nombre_cliente, registro_Pendientes[indice].nombre_cliente);
                    else if (indice_venta == -2) return false;

                    break;
                case 3:
                    registro_Pendientes[indice].monto = pedir_float("monto a pagar (en C$)");

                    indice_venta = buscar_Venta(id);
                    if (indice_venta >= 0) { //si se cambia el monto a pagar, hay que actualizar el monto de la venta (y la cantidad de leche)
                        registro_Ventas[indice_venta].monto = registro_Pendientes[indice].monto;

                        if (precio_galon == 0.00) {
                            _colSET(cRED);
                            cout << "   ERROR: Precio por galón no registrado...";
                            this_thread::sleep_for(chrono::milliseconds(2250));
                            _colRESET();
                            return true;
                        }

                        registro_Ventas[indice_venta].cantidad_leche = registro_Pendientes[indice].monto / precio_galon;
                    } else if (indice_venta == -2) return false;

                    break;
                default:
                    _colSET(cRED);
                    cout << "   Opción inválida...";
                    this_thread::sleep_for(chrono::milliseconds(1000));
                    _colRESET();
                    break;
            }
        } while (info < 1 || info > 3);

        cout << "   ";
        this_thread::sleep_for(chrono::milliseconds(500));
        _colSET(cGREEN);
        escribir_Pendientes = escribir_Archivos("registro_Pendientes.txt");
        escribir_Ventas = escribir_Archivos("registro_Ventas.txt");
        if (escribir_Pendientes && escribir_Ventas) {
            _colSET(cGREEN);
            cout << "\n   ***********************************************************************";
            cout << "\n                          Pago pendiente editado...";
        } else return false;
        
        this_thread::sleep_for(chrono::milliseconds(2250));
        _colRESET();
    }

    return true;
}

//***************************************************************************************************