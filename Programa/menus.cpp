#include "modulos/prototipos.h"
using namespace std;

//menus y submenus:
int start_screen();
int principal();
//---------------------------------
int produccion();
int clientes();
//---------------------------------
int finanzas();
int ventas();
int pendientes();
int costos_Fijos();
int costos_Variables();

//***************************************************************************************************

int start_screen() {
    int option = 0;
    title_splash();

    LLC::_colSET(LLC::cLIGHT_YELLOW);
    cout << endl;
    cout << "   1. Acceder a menú principal\n";
    LLC::_colSET(LLC::cRED);
    cout << "   2. Cerrar programa\n";
    LLC::_colSET(LLC::cTEAL);
    cout << "\n   => Ingrese su opción: ";
    cin >> option;
    LLC::_colRESET();

    return option;
}

int principal() {
    int option = 0, submenu = 0;
    
    do {
        system("cls || clear");
        menu_principal();

        LLC::_colSET(LLC::cLIGHT_YELLOW);
        cout << endl;
        cout << "   1. Acceder a Gestión de Producción\n";
        cout << "   2. Acceder a Gestión de Clientes\n";
        cout << "   3. Acceder a Gestión de Finanzas\n";
        LLC::_colSET(LLC::cCYAN);
        cout << "\n   4. Regresar a pantalla principal\n";
        LLC::_colSET(LLC::cTEAL);
        cout << "\n   => Ingrese su opción: ";
        cin >> option;
        LLC::_colRESET();

        switch (option) {
            case 1:
                LLC::_colSET(LLC::cLIGHT_YELLOW);
                cout << "      Accediendo a Gestión de Producción...";
                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));

                submenu = produccion(); //llamar al submenu
                if (submenu == 7) continue; //si el submenu retorna la opcion de regresar al menu principal, ir a la proxima iteracion
                break;
            case 2:
                LLC::_colSET(LLC::cLIGHT_YELLOW);
                cout << "      Accediendo a Gestión de Clientes...";
                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));

                submenu = clientes(); //^^
                if (submenu == 6) continue;
                break;
            case 3:
                LLC::_colSET(LLC::cLIGHT_YELLOW);
                cout << "      Accediendo a Gestión de Finanzas...";
                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));

                submenu = finanzas(); //^^
                if (submenu == 9) continue;
                break;
            case 4:
                LLC::_colSET(LLC::cCYAN);
                cout << "      Regresando a pantalla principal...";
                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));
                break;
            default:
                LLC::_colSET(LLC::cRED);
                cout << "      Opción inválida...";
                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));
                break;
        }
    } while (option != 4);

    LLC::_colRESET();
    return option;
}

//***************************************************************************************************

int produccion() {
    int option = 0, num = 0, indice = 0;
    char input_id[ID] = "";
    bool check = false;

    do {
        system("cls || clear");
        titulo_prod();
        
        cout << endl << "   1. Calcular producción total\n";
        LLC::_colSET(LLC::cLIGHT_YELLOW);
        cout << "\n   2. Registrar vacas\n";
        cout << "   3. Mostrar vacas\n";
        cout << "   4. Buscar vaca\n";
        cout << "   5. Modificar datos de vaca\n";
        cout << "   6. Eliminar vaca\n";
        LLC::_colSET(LLC::cCYAN);
        cout << "\n   7. Regresar a menú principal\n";
        LLC::_colSET(LLC::cTEAL);
        cout << "\n   => Ingrese su opción: ";
        cin >> option;
        LLC::_colRESET();

        switch (option) {
            case 1:
                check = calcular_Produccion();
                if (!check) {
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_Vacas.txt'...";
                    LLC::_colRESET();
                    this_thread::sleep_for(chrono::milliseconds(2250));
                }
                
                break;
            case 2:
                LLC::_colSET(LLC::cLIGHT_YELLOW);
                cout << "     ¿Cuántas vacas desea registrar? ";
                cin >> num;
                LLC::_colRESET();
                check = registrar_Vacas(num);

                if (!check) {
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo abrir, leer y/o escribir al archivo 'registro_Vacas.txt'...";
                } else {
                    LLC::_colSET(LLC::cGREEN);
                    cout << "\n   ***********************************************************************";
                    cout << "\n                           Vaca(s) registrada(s)...";
                }

                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(2250));
                break;
            case 3:
                check = mostrar_Vacas();
                if (!check) {
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_Vacas.txt'...";
                    LLC::_colRESET();
                    this_thread::sleep_for(chrono::milliseconds(2250));
                }

                break;
            case 4:
                system("cls || clear");
                cout << endl;
                pedir_Cstring("ID de la vaca a buscar", input_id, ID);
                indice = buscar_Vaca(input_id);

                LLC::_colSET(LLC::cTEAL);
                cout << "\n   Buscando vaca...";
                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(800));

                if (indice == -1) {
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR: el ID '" << input_id << "' no se encontró en el registro...";
                    this_thread::sleep_for(chrono::milliseconds(2250));
                } else if (indice == -2) {
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_Vacas.txt'...";
                    this_thread::sleep_for(chrono::milliseconds(2250));
                } else if (indice >= 0) {
                    LLC::_colSET(LLC::cGREEN);
                    cout << "\n   Vaca encontrada!";
                    this_thread::sleep_for(chrono::milliseconds(800));

                    LLC::_colSET(LLC::cCYAN);
                    cout << endl << "\n                                  Vaca #" << indice+1 << ":" << endl;
                    cout << "   ***********************************************************************\n";
                    LLC::_colSET(LLC::cLIGHT_YELLOW);
                    cout << "   ID: " << registro_Vacas[indice].id << "\n";
                    cout << "   Edad: " << registro_Vacas[indice].edad << "\n";
                    cout << "   Producción diaria: " << registro_Vacas[indice].prod_diaria << "\n";
                    cout << "   Estado de salud: " << registro_Vacas[indice].estado_salud << endl;
                    LLC::_colSET(LLC::cCYAN);
                    cout << endl << "   ***********************************************************************\n";
                    cout << "   Presione cualquier tecla para continuar...";
                    cin.get();
                }
                
                LLC::_colRESET();
                break;
            case 5:
                check = editar_Vaca();
                if (!check) {
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_Vacas.txt'...";
                    this_thread::sleep_for(chrono::milliseconds(2250));
                }

                break;
            case 6: //se palmo la vaca :(
                system("cls || clear");
                cout << endl;
                pedir_Cstring("ID de la vaca a eliminar", input_id, ID);
                indice = eliminar_Vaca(input_id);

                LLC::_colSET(LLC::cTEAL);
                cout << "\n   Buscando vaca...";
                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(800));

                if (indice == -1) {
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR: el ID '" << input_id << "' no se encontró en el registro...";
                } else if (indice == -2) {
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_Vacas.txt'...";
                } else if (indice == 0) {
                    LLC::_colSET(LLC::cGREEN);
                    cout << "\n   Vaca eliminada!";     
                }
                
                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(2250));
                break;
            case 7:
                LLC::_colSET(LLC::cCYAN);
                cout << "      Regresando a menú principal...";
                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));
                break;
            default:
                LLC::_colSET(LLC::cRED);
                cout << "      Opción inválida...";
                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));
                break;
        }
    } while (option != 7);

    LLC::_colRESET();
    return option;
}

int clientes() {
    int option = 0, num = 0, indice = 0;
    char input_id[ID] = "";
    bool check = false;

    do {
        system("cls || clear");
        titulo_clientes();

        LLC::_colSET(LLC::cLIGHT_YELLOW);
        cout << endl;
        cout << "   1. Registrar clientes\n";
        cout << "   2. Mostrar clientes\n";
        cout << "   3. Buscar cliente\n";
        cout << "   4. Modificar datos de cliente\n";
        cout << "   5. Eliminar cliente\n";
        LLC::_colSET(LLC::cCYAN);
        cout << "\n   6. Regresar a menú principal\n";
        LLC::_colSET(LLC::cTEAL);
        cout << "\n   => Ingrese su opción: ";
        cin >> option;
        LLC::_colRESET();

        switch (option) {
            case 1:
                LLC::_colSET(LLC::cLIGHT_YELLOW);
                cout << "     ¿Cuántos clientes desea registrar? ";
                cin >> num;
                LLC::_colRESET();
                check = registrar_Clientes(num);

                if (!check) {
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo abrir, leer y/o escribir al archivo 'registro_Clientes.txt'...";
                } else {
                    LLC::_colSET(LLC::cGREEN);
                    cout << "\n   ***********************************************************************";
                    cout << "\n                          Cliente(s) registrado(s)...";
                }

                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(2250));
                break;
            case 2:
                check = mostrar_Clientes();
                if (!check) {
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_Clientes.txt'...";
                    LLC::_colRESET();
                    this_thread::sleep_for(chrono::milliseconds(2250));
                }
                
                break;
            case 3:
                system("cls || clear");
                cout << endl;
                pedir_Cstring("ID del cliente a buscar", input_id, ID);
                indice = buscar_Cliente(input_id, false);

                LLC::_colSET(LLC::cTEAL);
                cout << "\n   Buscando cliente...";
                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(800));

                if (indice == -1) {
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR: el ID '" << input_id << "' no se encontró en el registro...";
                    this_thread::sleep_for(chrono::milliseconds(2250));
                } else if (indice == -2) {
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_Clientes.txt'...";
                    this_thread::sleep_for(chrono::milliseconds(2250));
                } else if (indice >= 0) {
                    LLC::_colSET(LLC::cGREEN);
                    cout << "\n   Cliente encontrado!";
                    this_thread::sleep_for(chrono::milliseconds(800));

                    LLC::_colSET(LLC::cCYAN);
                    cout << endl << "\n                                  Cliente #" << indice+1 << ":" << endl;
                    cout << "   ***********************************************************************\n";
                    LLC::_colSET(LLC::cLIGHT_YELLOW);
                    cout << "   ID: " << registro_Clientes[indice].id << "\n";
                    cout << "   Nombre: " << registro_Clientes[indice].nombre << "\n";
                    cout << "   Dirección: " << registro_Clientes[indice].direccion << "\n";
                    cout << "   Contacto: " << registro_Clientes[indice].contacto << endl;
                    LLC::_colSET(LLC::cCYAN);
                    cout << endl << "   ***********************************************************************\n";
                    cout << "   Presione cualquier tecla para continuar...";
                    cin.get();
                }

                LLC::_colRESET();
                break;
            case 4:
                check = editar_Cliente();
                if (!check) {
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_Clientes.txt'...";
                    LLC::_colRESET();
                    this_thread::sleep_for(chrono::milliseconds(2250));
                }

                break;
            case 5:
                system("cls || clear");
                cout << endl;
                pedir_Cstring("ID del cliente a eliminar", input_id, ID);
                indice = eliminar_Cliente(input_id);

                LLC::_colSET(LLC::cTEAL);
                cout << "\n   Buscando cliente...";
                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(800));

                if (indice == -1) {
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR: el ID '" << input_id << "' no se encontró en el registro...";
                } else if (indice == -2) {
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_Clientes.txt'...";
                } else if (indice == 0) {
                    LLC::_colSET(LLC::cGREEN);
                    cout << "\n   Cliente eliminado!";     
                }
                
                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(2250));
                break;
            case 6:
                LLC::_colSET(LLC::cCYAN);
                cout << "      Regresando a menú principal...";
                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));
                break;
            default:
                LLC::_colSET(LLC::cRED);
                cout << "      Opción inválida...";
                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));
                break;
        }
    } while (option != 6);

    LLC::_colRESET();
    return option;
}

//***************************************************************************************************

int finanzas() {
    int option = 0, submenu = 0;
    bool check = false;

    do {
        system("cls || clear");
        titulo_finanzas();

        LLC::_colSET(LLC::cLIGHT_YELLOW);
        cout << endl;
        cout << "   1. Acceder a menú de ventas\n";
        cout << "   2. Acceder a menú de pagos pendientes\n";
        cout << "   3. Acceder a menú de costos fijos\n";
        cout << "   4. Acceder a menú de costos variables\n";
        LLC::_colSET(LLC::cGREEN);
        cout << "\n   5. Calcular ingresos totales\n";
        LLC::_colSET(LLC::cRED);
        cout << "   6. Calcular costos totales\n";
        LLC::_colRESET();
        cout << "   7. Calcular utilidad\n";
        LLC::_colSET(LLC::cLIGHT_YELLOW);
        cout << "\n   8. Mostrar precio por galón\n";
        cout << "   9. Cambiar precio por galón\n";
        LLC::_colSET(LLC::cCYAN);
        cout << "\n   10. Regresar a menú principal\n";
        LLC::_colSET(LLC::cTEAL);
        cout << "\n   => Ingrese su opción: ";
        cin >> option;
        LLC::_colRESET();

        /*si se escogio entrar a los menus de costos fijos/variables y se quiere mover
        directamente entre los dos sin tener que regresar al menu de finanzas*/
        while (option == 3 || option == 4) { 
            if (option == 3) {
                LLC::_colSET(LLC::cLIGHT_YELLOW);
                cout << "      Accediendo a submenú de costos fijos...";
                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));

                submenu = costos_Fijos();
                if (submenu == 6) option = 4; //ir al menu de costos variables
            } else if (option == 4) {
                LLC::_colSET(LLC::cLIGHT_YELLOW);
                cout << "      Accediendo a submenú de costos variables...";
                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));

                submenu = costos_Variables();
                if (submenu == 6) option = 3; //ir al menu de costos fijos
            }

            //si se escogio regresar al menu de finanzas, salir del while
            if (submenu == 7) {
                LLC::_colSET(LLC::cCYAN);
                cout << "      Regresando a menú de finanzas...";
                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));
                break;
            }

            /*si se escogio regresar al menu de principal directamente desde
            los menus de costos fijos/variables, asignar option al valor de este menu
            que nos regresa a al menu principal y nos saca de este while*/
            else if (submenu == 8) option = 10;
        }

        switch (option) {
            case 1:
                LLC::_colSET(LLC::cLIGHT_YELLOW);
                cout << "      Accediendo a menú de ventas...";
                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));

                submenu = ventas();
                if (submenu == 6) continue; //si el submenu retorna la opcion de regresar al menu de finanzas, ir a la proxima iteracion
                else if (submenu == 7) return 10; //retorna la opcion que hace que se regrese al menu principal
                break;
            case 2:
                LLC::_colSET(LLC::cLIGHT_YELLOW);
                cout << "      Accediendo a menú de pagos pendientes...";
                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));

                submenu = pendientes();
                if (submenu == 5) continue; //^^
                else if (submenu == 6) return 10; //^^
                break;

            case 3: break; //para que el switch no se vaya al caso default si option es 2 o 3
            case 4: break; //^^

            case 5:
                check = calcular_Ingresos();
                if (!check) {
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer uno o más de los siguientes archivos: 'registro_Ventas.txt', 'registro_Pendientes.txt'...";
                    LLC::_colRESET();
                }

                break;
            case 6:
                check = calcular_Costos();
                if (!check) {
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer uno o más de los siguientes archivos: 'costos_Fijos.txt', 'costos_Variables.txt'...";
                    LLC::_colRESET();
                }

                break;
            case 7:
                check = calcular_Utilidad();
                if (!check) {
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer uno o más de los siguientes archivos: 'registro_Ventas.txt', 'registro_Pendientes.txt', 'costos_Fijos.txt', 'costos_Variables.txt'...";
                    LLC::_colRESET();
                }

                break;
            case 8:
                check = mostrar_Precio();
                if (!check) {
                    this_thread::sleep_for(chrono::milliseconds(500));
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'precio_galon.txt'...";
                    LLC::_colRESET();
                }

                this_thread::sleep_for(chrono::milliseconds(2250));
                break;
            case 9:
                check = ingresar_Precio();
                if (!check) {
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo escribir el precio ingresado al archivo 'precio_galon.txt'...";
                    LLC::_colRESET();
                }
                
                this_thread::sleep_for(chrono::milliseconds(2250));
                break;
            case 10:
                LLC::_colSET(LLC::cCYAN);
                cout << "      Regresando a menú principal...";
                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));
                break;
            default:
                LLC::_colSET(LLC::cRED);
                cout << "      Opción inválida...";
                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));
                break;
        }
    } while (option != 10);

    LLC::_colRESET();
    return option;
}

int ventas() {
    int option = 0, num = 0, indice = 0;
    char input_id[ID] = "", pagada[3] = "";
    bool check = false;

    do {
        system("cls || clear");
        titulo_ventas();

        LLC::_colSET(LLC::cLIGHT_YELLOW);
        cout << endl;
        cout << "   1. Registrar ventas\n";
        cout << "   2. Mostrar ventas\n";
        cout << "   3. Buscar venta\n";
        cout << "   4. Modificar venta\n";
        cout << "   5. Eliminar venta\n";
        LLC::_colSET(LLC::cCYAN);
        cout << "\n   6. Regresar a menú de finanzas\n";
        cout << "   7. Regresar a menú principal\n";
        LLC::_colSET(LLC::cTEAL);
        cout << "\n   => Ingrese su opción: ";
        cin >> option;
        LLC::_colRESET();
        
        switch (option) {
            case 1:
                LLC::_colSET(LLC::cLIGHT_YELLOW);
                cout << "     ¿Cuántas ventas desea registrar? ";
                cin >> num;
                LLC::_colRESET();
                check = registrar_Ventas(num);

                if (!check) {
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo abrir, leer y/o escribir a uno o más los siguientes archivos: 'registro_Ventas.txt', 'registro_Pendientes.txt', 'precio_galon.txt'...";
                } else {
                    LLC::_colSET(LLC::cGREEN);
                    cout << "\n   ***********************************************************************";
                    cout << "\n                           Venta(s) registrada(s)...";
                }

                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(2250));
                break;
            case 2:
                check = mostrar_Ventas();
                if (!check) {
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_Ventas.txt'...";
                    LLC::_colRESET();
                    this_thread::sleep_for(chrono::milliseconds(2250));
                }
                
                break;
            case 3:
                system("cls || clear");
                cout << endl;
                pedir_Cstring("ID de la venta a buscar", input_id, ID);
                indice = buscar_Venta(input_id);

                LLC::_colSET(LLC::cTEAL);
                cout << "\n   Buscando venta...";
                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(800));

                if (indice == -1) {
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR: el ID '" << input_id << "' no se encontró en el registro...";
                    this_thread::sleep_for(chrono::milliseconds(2250));
                } else if (indice == -2) {
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_Ventas.txt'...";
                    this_thread::sleep_for(chrono::milliseconds(2250));
                } else if (indice >= 0) {
                    strcpy(pagada, (registro_Ventas[indice].pagada ? "Sí" : "No"));
                    LLC::_colSET(LLC::cGREEN);
                    cout << "\n   Venta encontrada!";
                    this_thread::sleep_for(chrono::milliseconds(800));

                    LLC::_colSET(LLC::cCYAN);
                    cout << endl << "\n                                  Venta #" << indice+1 << ":" << endl;
                    cout << "   ***********************************************************************\n";
                    LLC::_colSET(LLC::cLIGHT_YELLOW);
                    cout << "   ID: " << registro_Ventas[indice].id << "\n";
                    cout << "   Fecha: " << registro_Ventas[indice].fecha.dia << " de " << registro_Ventas[indice].fecha.mes << ", " << registro_Ventas[indice].fecha.year << "\n";
                    cout << "   Nombre del cliente: " << registro_Ventas[indice].nombre_cliente << "\n";
                    cout << "   Cantidad de leche: " << registro_Ventas[indice].cantidad_leche << " galones\n";
                    cout << "   Monto: C$" << registro_Ventas[indice].monto << "\n";
                    cout << "   ¿Está pagada? "; LLC::_colSET(LLC::cTEAL); cout << pagada << endl;
                    LLC::_colSET(LLC::cCYAN);
                    cout << endl << "   ***********************************************************************\n";
                    cout << "   Presione cualquier tecla para continuar...";
                    cin.get();
                }

                LLC::_colRESET();
                break;
            case 4:
                check = editar_Venta();
                if (!check) {
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo abrir, leer y/o escribir a uno o más de los siguientes archivos: 'registro_Ventas.txt', 'registro_Pendientes.txt'...";
                    LLC::_colRESET();
                    this_thread::sleep_for(chrono::milliseconds(2250));
                }
                
                break;
            case 5:
                system("cls || clear");
                cout << endl;
                pedir_Cstring("ID de la venta a eliminar", input_id, ID);
                indice = eliminar_Venta(input_id);

                LLC::_colSET(LLC::cTEAL);
                cout << "\n   Buscando venta...";
                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(800));

                if (indice == -1) {
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR: el ID '" << input_id << "' no se encontró en el registro...";
                } else if (indice == -2) {
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo abrir, leer y/o escribir a uno o más los siguientes archivos: 'registro_Ventas.txt', 'registro_Pendientes.txt', 'precio_galon.txt...";
                } else if (indice >= 0) {
                    LLC::_colSET(LLC::cGREEN);
                    cout << "\n   Venta eliminada!";
                }

                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(2250));
                break;
            case 6:
                LLC::_colSET(LLC::cCYAN);
                cout << "      Regresando a menú de finanzas...";
                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));
                break;
            case 7:
                LLC::_colSET(LLC::cCYAN);
                cout << "      Regresando a menú principal...";
                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));
                break;
            default:
                LLC::_colSET(LLC::cRED);
                cout << "      Opción inválida...";
                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));
                break;
        }
    } while ((option != 6) && (option != 7)); //mientras no se quiera regresar a otro menu, permanecer en el bucle

    LLC::_colRESET();
    return option; //retornar la opcion del menu al que se quiere regresar
}

int pendientes() {
    int option = 0, indice = 0;
    char input_id[ID] = "";
    bool check = false;

    do {
        system("cls || clear");
        titulo_pendientes();

        LLC::_colSET(LLC::cLIGHT_YELLOW);
        cout << endl;
        cout << "   1. Mostrar pagos pendientes\n";
        cout << "   2. Buscar pago pendiente\n";
        cout << "   3. Modificar pago pendiente\n";
        cout << "   4. Eliminar pago pendiente\n";
        LLC::_colSET(LLC::cCYAN);
        cout << "\n   5. Regresar a menú de finanzas\n";
        cout << "   6. Regresar a menú principal\n";
        LLC::_colSET(LLC::cTEAL);
        cout << "\n   => Ingrese su opción: ";
        cin >> option;

        switch (option) {
            case 1:
                check = mostrar_Pendientes();
                if (!check) {
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_Pendientes.txt'...";
                    LLC::_colRESET();
                    this_thread::sleep_for(chrono::milliseconds(2250));
                }
                
                break;
            case 2:
                system("cls || clear");
                cout << endl;
                pedir_Cstring("ID del pago pendiente a buscar", input_id, ID);
                indice = buscar_Pendiente(input_id);

                LLC::_colSET(LLC::cTEAL);
                cout << "\n   Buscando pago pendiente...";
                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(800));

                if (indice == -1) {
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR: el ID '" << input_id << "' no se encontró en el registro...";
                    this_thread::sleep_for(chrono::milliseconds(2250));
                } else if (indice == -2) {
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_Pendientes.txt'...";
                    this_thread::sleep_for(chrono::milliseconds(2250));
                } else if (indice >= 0) {
                    LLC::_colSET(LLC::cGREEN);
                    cout << "\n   Pago pendiente encontrado!";
                    this_thread::sleep_for(chrono::milliseconds(800));

                    LLC::_colSET(LLC::cCYAN);
                    cout << endl << "\n                                  Pago pendiente #" << indice+1 << ":" << endl;
                    cout << "   ***********************************************************************\n";
                    LLC::_colSET(LLC::cLIGHT_YELLOW);
                    cout << "   ID de la venta: " << registro_Pendientes[indice].id_venta << "\n";
                    cout << "   Fecha: " << registro_Pendientes[indice].fecha.dia << " de " << registro_Pendientes[indice].fecha.mes << ", " << registro_Pendientes[indice].fecha.year << "\n";
                    cout << "   Nombre del cliente: " << registro_Pendientes[indice].nombre_cliente << endl;
                    cout << "   Monto: C$" << registro_Pendientes[indice].monto << "\n";
                    LLC::_colSET(LLC::cCYAN);
                    cout << endl << "   ***********************************************************************\n";
                    cout << "   Presione cualquier tecla para continuar...";
                    cin.get();
                }

                LLC::_colRESET();
                break;
            case 3:
                check = editar_Pendiente();
                if (!check) {
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer uno o más de los siguientes archivos: 'registro_Pendientes.txt', 'registro_Ventas.txt...";
                    LLC::_colRESET();
                    this_thread::sleep_for(chrono::milliseconds(2250));
                }
                
                break;
            case 4:
                system("cls || clear");
                cout << endl;
                pedir_Cstring("ID del pago pendiente a eliminar", input_id, ID);
                indice = eliminar_Pendiente(input_id);

                LLC::_colSET(LLC::cTEAL);
                cout << "\n   Buscando pago pendiente...";
                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(800));

                if (indice == -1) {
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR: el ID '" << input_id << "' no se encontró en el registro...";
                } else if (indice == -2) {
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo abrir/leer uno o más de los siguientes archivos: 'registro_Pendientes.txt', 'registro_Ventas.txt', 'precio_galon.txt'...";
                } else if (indice >= 0) {
                    LLC::_colSET(LLC::cGREEN);
                    cout << "\n   Pago pendiente eliminado!";
                }

                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(2250));
                break;
            case 5:
                LLC::_colSET(LLC::cCYAN);
                cout << "      Regresando a menú de finanzas...";
                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));
                break;
            case 6:
                LLC::_colSET(LLC::cCYAN);
                cout << "      Regresando a menú principal...";
                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));
                break;
            default:
                LLC::_colSET(LLC::cRED);
                cout << "      Opción inválida...";
                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));
                break;
        }
    } while ((option != 5) && (option != 6));

    LLC::_colRESET();
    return option;
}

int costos_Fijos() {
    int option = 0, num = 0, indice = 0;
    char input_id[ID] = "";
    bool check = false;

    do {
        system("cls || clear");
        titulo_costos_Fijos();

        LLC::_colSET(LLC::cLIGHT_YELLOW);
        cout << endl;
        cout << "   1. Registrar costos\n";
        cout << "   2. Mostrar costos\n";
        cout << "   3. Buscar costo\n";
        cout << "   4. Modificar costo\n";
        cout << "   5. Eliminar costo\n";
        LLC::_colSET(LLC::cCYAN);
        cout << "\n   6. Ir a menú de costos variables\n";
        cout << "   7. Regresar a menú de finanzas\n";
        cout << "   8. Regresar a menú principal\n";
        LLC::_colSET(LLC::cTEAL);
        cout << "\n   => Ingrese su opción: ";
        cin >> option;
        LLC::_colRESET();

        switch (option) {
            case 1:
                LLC::_colSET(LLC::cLIGHT_YELLOW);
                cout << "     ¿Cuántos costos fijos desea registrar? ";
                cin >> num;
                LLC::_colRESET();
                check = registrar_costos_Fijos(num);

                if (!check) {
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo abrir, leer y/o escribir al archivo 'registro_costos_Fijos.txt'...";
                } else {
                    LLC::_colSET(LLC::cGREEN);
                    cout << "\n   ***********************************************************************";
                    cout << "\n                          Costo(s) registrado(s)...";
                }

                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(2250));
                break;
            case 2:
                check = mostrar_costos_Fijos();
                if (!check) {
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_costos_Fijos.txt'...";
                    LLC::_colRESET();
                    this_thread::sleep_for(chrono::milliseconds(2250));
                }

                break;
            case 3:
                system("cls || clear");
                cout << endl;
                pedir_Cstring("ID del costo fijo a buscar", input_id, ID);
                indice = buscar_costo_Fijo(input_id);

                LLC::_colSET(LLC::cTEAL);
                cout << "\n   Buscando costo fijo...";
                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(800));

                if (indice == -1) {
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR: el ID '" << input_id << "' no se encontró en el registro...";
                    this_thread::sleep_for(chrono::milliseconds(2250));
                } else if (indice == -2) {
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_costos_Fijos.txt'...";
                    this_thread::sleep_for(chrono::milliseconds(2250));
                } else if (indice >= 0) {
                    LLC::_colSET(LLC::cGREEN);
                    cout << "\n   Costo fijo encontrado!";
                    this_thread::sleep_for(chrono::milliseconds(800));

                    LLC::_colSET(LLC::cCYAN);
                    cout << endl << "\n                                  Costo Fijo #" << indice+1 << ":" << endl;
                    cout << "   ***********************************************************************\n";
                    LLC::_colSET(LLC::cLIGHT_YELLOW);
                    cout << "   ID: " << registro_costos_Fijos[indice].id << "\n";
                    cout << "   Monto: C$" << registro_costos_Fijos[indice].monto << "\n";
                    cout << "   Descripción: " << registro_costos_Fijos[indice].descripcion << endl;
                    LLC::_colSET(LLC::cCYAN);
                    cout << endl << "   ***********************************************************************\n";
                    cout << "   Presione cualquier tecla para continuar...";
                    cin.get();
                }

                LLC::_colRESET();
                break;
            case 4:
                check = editar_costo_Fijo();
                if (!check) {
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_costos_Fijos.txt'...";
                    LLC::_colRESET();
                    this_thread::sleep_for(chrono::milliseconds(2250));
                }

                break;
            case 5:
                system("cls || clear");
                cout << endl;
                pedir_Cstring("ID del costo fijo a eliminar", input_id, ID);
                indice = eliminar_costo_Fijo(input_id);

                LLC::_colSET(LLC::cTEAL);
                cout << "\n   Buscando costo fijo...";
                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(800));

                if (indice == -1) {
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR: el ID '" << input_id << "' no se encontró en el registro...";
                } else if (indice == -2) {
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_costos_Fijos.txt'...";
                } else if (indice == 0) {
                    LLC::_colSET(LLC::cGREEN);
                    cout << "\n   Costo fijo eliminado!";
                }

                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(2250));
                break;

            case 6: break; //el mensaje y el sleep se llaman en finanzas()
            case 7: break; //^^
            case 8: break; //^^

            default:
                LLC::_colSET(LLC::cRED);
                cout << "      Opción inválida...";
                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));
                break;
        }
    } while ((option < 6) || (option > 8)); //mientras no se quiera salir del submenu, quedarse en el do while

    LLC::_colRESET();
    return option;
}

int costos_Variables() {
    int option = 0, num = 0, indice = 0;
    char input_id[ID] = "";
    bool check = false;

    do {
        system("cls || clear");
        titulo_costos_Variables();

        LLC::_colSET(LLC::cLIGHT_YELLOW);
        cout << endl;
        cout << "   1. Registrar costos\n";
        cout << "   2. Mostrar costos\n";
        cout << "   3. Buscar costo\n";
        cout << "   4. Modificar costo\n";
        cout << "   5. Eliminar costo\n";
        LLC::_colSET(LLC::cCYAN);
        cout << "\n   6. Ir a menú de costos fijos\n";
        cout << "   7. Regresar a menú de finanzas\n";
        cout << "   8. Regresar a menú principal\n";
        LLC::_colSET(LLC::cTEAL);
        cout << "\n   => Ingrese su opción: ";
        cin >> option;
        LLC::_colRESET();

        switch (option) {
            case 1:
                LLC::_colSET(LLC::cLIGHT_YELLOW);
                cout << "     ¿Cuántos costos variables desea registrar? ";
                cin >> num;
                LLC::_colRESET();
                check = registrar_costos_Variables(num);

                if (!check) {
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo abrir, leer y/o escribir al archivo 'registro_costos_Variables.txt'...";
                } else {
                    LLC::_colSET(LLC::cGREEN);
                    cout << "\n   ***********************************************************************";
                    cout << "\n                           Costo(s) registrado(s)...";
                }

                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(2250));
                break;
            case 2:
                check = mostrar_costos_Variables();
                if (!check) {
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_costos_Variables.txt'...";
                    LLC::_colRESET();
                    this_thread::sleep_for(chrono::milliseconds(2250));
                }
                
                break;
            case 3:
                system("cls || clear");
                cout << endl;
                pedir_Cstring("ID del costo variable a buscar", input_id, ID);
                indice = buscar_costo_Variable(input_id);

                LLC::_colSET(LLC::cTEAL);
                cout << "\n   Buscando costo variable...";
                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(800));

                if (indice == -1) {
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR: el ID '" << input_id << "' no se encontró en el registro...";
                    this_thread::sleep_for(chrono::milliseconds(2250));
                } else if (indice == -2) {
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_costos_Variables.txt'...";
                    this_thread::sleep_for(chrono::milliseconds(2250));
                } else if (indice >= 0) {
                    LLC::_colSET(LLC::cGREEN);
                    cout << "\n   Costo variable encontrado!";
                    this_thread::sleep_for(chrono::milliseconds(800));

                    LLC::_colSET(LLC::cCYAN);
                    cout << endl << "\n                               Costo Variable #" << indice+1 << ":" << endl;
                    cout << "   ***********************************************************************\n";
                    LLC::_colSET(LLC::cLIGHT_YELLOW);
                    cout << "   ID: " << registro_costos_Variables[indice].id << "\n";
                    cout << "   Monto: C$" << registro_costos_Variables[indice].monto << "\n";
                    cout << "   Descripción: " << registro_costos_Variables[indice].descripcion << "\n";
                    cout << "   Mes: " << registro_costos_Variables[indice].mes << endl;
                    LLC::_colSET(LLC::cCYAN);
                    cout << endl << "   ***********************************************************************\n";
                    cout << "   Presione cualquier tecla para continuar...";
                    cin.get();
                }

                LLC::_colRESET();
                break;
            case 4:
                check = editar_costo_Variable();
                if (!check) {
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_costos_Variables.txt'...";
                    LLC::_colRESET();
                    this_thread::sleep_for(chrono::milliseconds(2250));
                }
                
                break;
            case 5:
                system("cls || clear");
                cout << endl;
                pedir_Cstring("ID del costo variable a eliminar", input_id, ID);
                indice = eliminar_costo_Variable(input_id);

                LLC::_colSET(LLC::cTEAL);
                cout << "\n   Buscando costo variable...";
                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(800));

                if (indice == -1) {
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR: el ID '" << input_id << "' no se encontró en el registro...";
                } else if (indice == -2) {
                    LLC::_colSET(LLC::cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_costos_Variables.txt'...";
                } else if (indice == 0) {
                    LLC::_colSET(LLC::cGREEN);
                    cout << "\n   Costo variable eliminado!";
                }

                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(2250));
                break;

            case 6: break; //el mensaje y el sleep se llaman en finanzas()
            case 7: break; //^^
            case 8: break; //^^

            default:
                LLC::_colSET(LLC::cRED);
                cout << "      Opción inválida...";
                LLC::_colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));
                break;
        }
    } while ((option < 6) || (option > 8));

    LLC::_colRESET();
    return option;
}

//***************************************************************************************************