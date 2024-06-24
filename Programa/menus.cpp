#include <iostream>
#include <windows.h>
#include "funciones.cpp"
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
//---------------------------------
int facturacion();
int reportes();

//***************************************************************************************************

int start_screen() {
    int option = 0;
    title_splash();

    cambiar_color(14);
    cout << endl;
    cout << "   1. Acceder a menú principal\n";
    cambiar_color(12);
    cout << "   2. Cerrar programa\n";
    cambiar_color(9);
    cout << "\n   => Ingrese su opción: ";
    cin >> option;
    resetear_color();

    return option;
}

int principal() {
    int option = 0, submenu = 0;
    
    do {
        system("cls || clear");
        menu_principal();

        cambiar_color(14);
        cout << endl;
        cout << "   1. Acceder a Gestión de Producción\n";
        cout << "   2. Acceder a Gestión de Clientes\n";
        cout << "   3. Acceder a Gestión de Finanzas\n";
        cout << "   4. Acceder a Gestión de Facturación\n";
        cout << "   5. Acceder a Gestión de Reportes\n";
        cambiar_color(11);
        cout << "\n   6. Regresar a pantalla principal\n";
        cambiar_color(9);
        cout << "\n   => Ingrese su opción: ";
        cin >> option;
        resetear_color();

        switch (option) {
            case 1:
                cambiar_color(14);
                cout << "      Accediendo a Gestión de Producción...";
                resetear_color();
                Sleep(1000);

                submenu = produccion(); //llamar al submenu
                if (submenu == 6) continue; //si el submenu retorna la opcion de regresar al menu principal, ir a la proxima iteracion
                break;
            case 2:
                cambiar_color(14);
                cout << "      Accediendo a Gestión de Clientes...";
                resetear_color();
                Sleep(1000);

                submenu = clientes(); //^^
                if (submenu == 6) continue;
                break;
            case 3:
                cambiar_color(14);
                cout << "      Accediendo a Gestión de Finanzas...";
                resetear_color();
                Sleep(1000);

                submenu = finanzas(); //^^
                if (submenu == 9) continue;
                break;
            case 4:
                cambiar_color(14);
                cout << "      Accediendo a Gestión de Facturación...";
                resetear_color();
                Sleep(1000);

                submenu = facturacion(); //^^
                if (submenu == 6) continue;
                break;
            case 5:
                cambiar_color(14);
                cout << "      Accediendo a Gestión de Reportes...";
                resetear_color();
                Sleep(1000);

                submenu = reportes(); //^^
                if (submenu == 4) continue;
                break;
            case 6:
                cambiar_color(11);
                cout << "      Regresando a pantalla principal...";
                resetear_color();
                Sleep(1000);
                break;
            default:
                cambiar_color(12);
                cout << "      Opción inválida...";
                resetear_color();
                Sleep(1000);
                break;
        }
    } while (option != 6);

    resetear_color();
    return option;
}

//***************************************************************************************************

int produccion() {
    int option = 0, num = 0;
    bool check = false;

    do {
        system("cls || clear");
        titulo_prod();

        cambiar_color(14);
        cout << endl;
        cout << "   1. Registrar vacas\n";
        cout << "   2. Mostrar vacas\n";
        cout << "   3. Buscar vaca\n";
        cout << "   4. Editar registro\n";
        cout << "   5. Eliminar vaca\n";
        cambiar_color(11);
        cout << "\n   6. Regresar a menú principal\n";
        cambiar_color(9);
        cout << "\n   => Ingrese su opción: ";
        cin >> option;
        resetear_color();

        switch (option) {
            case 1:
                cambiar_color(14);
                cout << "     ¿Cuántas vacas desea registrar? ";
                cin >> num;
                resetear_color();
                check = registrar_Vacas(num);

                if (!check) {
                    cambiar_color(12);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo abrir, leer y/o escribir al archivo 'registro_Vacas.txt'...";
                } else {
                    cambiar_color(10);
                    cout << "\n   ***********************************************************************";
                    cout << "\n                           Vaca(s) registrada(s)...";
                }

                resetear_color();
                Sleep(2250);
                break;
            case 2:
                check = mostrar_Vacas();
                if (!check) {
                    cambiar_color(12);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_Vacas.txt'...";
                }

                break;
            case 3:
                //coso de buscar
                break;
            case 4:
                //coso de modificar
                break;
            case 5:
                //coso de eliminar (se palmo la vaca :< )
                break;
            case 6:
                cambiar_color(11);
                cout << "      Regresando a menú principal...";
                resetear_color();
                Sleep(1000);
                break;
            default:
                cambiar_color(12);
                cout << "      Opción inválida...";
                resetear_color();
                Sleep(1000);
                break;
        }
    } while (option != 6);

    resetear_color();
    return option;
}

int clientes() {
    int option = 0, num = 0;
    bool check = false;

    do {
        system("cls || clear");
        titulo_clientes();

        cambiar_color(14);
        cout << endl;
        cout << "   1. Registrar clientes\n";
        cout << "   2. Mostrar clientes\n";
        cout << "   3. Buscar cliente\n";
        cout << "   4. Modificar clientes\n";
        cout << "   5. Eliminar clientes\n";
        cambiar_color(11);
        cout << "\n   6. Regresar a menú principal\n";
        cambiar_color(9);
        cout << "\n   => Ingrese su opción: ";
        cin >> option;
        resetear_color();

        switch (option) {
            case 1:
                cambiar_color(14);
                cout << "     ¿Cuántos clientes desea registrar? ";
                cin >> num;
                resetear_color();
                check = registrar_Clientes(num);

                if (!check) {
                    cambiar_color(12);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo abrir, leer y/o escribir al archivo 'registro_Clientes.txt'...";
                } else {
                    cambiar_color(10);
                    cout << "\n   ***********************************************************************";
                    cout << "\n                          Cliente(s) registrado(s)...";
                }

                resetear_color();
                Sleep(2250);
                break;
            case 2:
                check = mostrar_Clientes();
                if (!check) {
                    cambiar_color(12);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_Clientes.txt'...";
                }
                
                break;
            case 3:
                //coso de buscar
                break;
            case 4:
                //coso de modificar
                break;
            case 5:
                //coso de eliminar
                break;
            case 6:
                cambiar_color(11);
                cout << "      Regresando a menú principal...";
                resetear_color();
                Sleep(1000);
                break;
            default:
                cambiar_color(12);
                cout << "      Opción inválida...";
                resetear_color();
                Sleep(1000);
                break;
        }
    } while (option != 6);

    resetear_color();
    return option;
}

//***************************************************************************************************

int finanzas() {
    int option = 0, submenu = 0;
    bool check = false;

    do {
        system("cls || clear");
        titulo_finanzas();

        cambiar_color(14);
        cout << endl;
        cout << "   1. Acceder a menú de ventas\n";
        cout << "   2. Acceder a menú de pagos pendientes\n";
        cout << "   3. Acceder a menú de costos fijos\n";
        cout << "   4. Acceder a menú de costos variables\n";
        cambiar_color(10);
        cout << "\n   5. Calcular ingresos totales\n";
        cambiar_color(12);
        cout << "   6. Calcular costos totales\n";
        resetear_color();
        cout << "   7. Calcular utilidad\n";
        cambiar_color(14);
        cout << "\n   8. Mostrar precio por galón\n";
        cout << "   9. Cambiar precio por galón\n";
        cambiar_color(11);
        cout << "\n   10. Regresar a menú principal\n";
        cambiar_color(9);
        cout << "\n   => Ingrese su opción: ";
        cin >> option;
        resetear_color();

        /*si se escogio entrar a los menus de costos fijos/variables y se quiere mover
        directamente entre los dos sin tener que regresar al menu de finanzas*/
        while (option == 3 || option == 4) { 
            if (option == 3) {
                cambiar_color(14);
                cout << "      Accediendo a submenú de costos fijos...";
                resetear_color();
                Sleep(1000);

                submenu = costos_Fijos();
                if (submenu == 6) option = 4; //ir al menu de costos variables
            } else if (option == 4) {
                cambiar_color(14);
                cout << "      Accediendo a submenú de costos variables...";
                resetear_color();
                Sleep(1000);

                submenu = costos_Variables();
                if (submenu == 6) option = 3; //ir al menu de costos fijos
            }

            //si se escogio regresar al menu de finanzas, salir del while
            if (submenu == 7) {
                cambiar_color(11);
                cout << "      Regresando a menú de finanzas...";
                resetear_color();
                Sleep(1000);
                break;
            }

            /*si se escogio regresar al menu de principal directamente desde
            los menus de costos fijos/variables, asignar option al valor de este menu
            que nos regresa a al menu principal y nos saca de este while*/
            else if (submenu == 8) option = 9;
        }

        switch (option) {
            case 1:
                cambiar_color(14);
                cout << "      Accediendo a menú de ventas...";
                resetear_color();
                Sleep(1000);

                submenu = ventas();
                if (submenu == 6) continue; //si el submenu retorna la opcion de regresar al menu de finanzas, ir a la proxima iteracion
                else if (submenu == 7) return 9; //retorna la opcion que hace que se regrese al menu principal
                break;
            case 2:
                cambiar_color(14);
                cout << "      Accediendo a menú de pagos pendientes...";
                resetear_color();
                Sleep(1000);

                submenu = pendientes();
                if (submenu == 5) continue; //^^
                else if (submenu == 6) return 9; //^^
                break;

            case 3: break; //para que el switch no se vaya al caso default si option es 2 o 3
            case 4: break; //^^

            case 5:
                //coso de ingresos
                break;
            case 6:
                //coso de costos totales
                break;
            case 7:
                //coso de utilidad
                break;
            case 8:
                check = mostrar_Precio();
                if (!check) {
                    Sleep(500);
                    cambiar_color(12);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'precio_galon.txt'...";
                }

                resetear_color();
                Sleep(2250);
                break;
            case 9:
                check = ingresar_Precio();
                if (!check) {
                    cambiar_color(12);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo escribir el precio ingresado al archivo 'precio_galon.txt'...";
                }
                
                resetear_color();
                Sleep(2250);
                break;
            case 10:
                cambiar_color(11);
                cout << "      Regresando a menú principal...";
                resetear_color();
                Sleep(1000);
                break;
            default:
                cambiar_color(12);
                cout << "      Opción inválida...";
                resetear_color();
                Sleep(1000);
                break;
        }
    } while (option != 10);

    resetear_color();
    return option;
}

int ventas() {
    int option = 0, num = 0;
    bool check = false;

    do {
        system("cls || clear");
        titulo_ventas();

        cambiar_color(14);
        cout << endl;
        cout << "   1. Registrar venta\n";
        cout << "   2. Mostrar ventas\n";
        cout << "   3. Buscar venta\n";
        cout << "   4. Modificar ventas\n";
        cout << "   5. Eliminar ventas\n";
        cambiar_color(11);
        cout << "\n   6. Regresar a menú de finanzas\n";
        cout << "   7. Regresar a menú principal\n";
        cambiar_color(9);
        cout << "\n   => Ingrese su opción: ";
        cin >> option;
        resetear_color();
        
        switch (option) {
            case 1:
                cambiar_color(14);
                cout << "     ¿Cuántas ventas desea registrar? ";
                cin >> num;
                resetear_color();
                check = registrar_Ventas(num);

                if (!check) {
                    cambiar_color(12);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo abrir, leer y/o escribir al archivo 'registro_Ventas.txt'...";
                } else {
                    cambiar_color(10);
                    cout << "\n   ***********************************************************************";
                    cout << "\n                           Venta(s) registrada(s)...";
                }

                resetear_color();
                Sleep(2250);
                break;
            case 2:
                check = mostrar_Ventas();
                if (!check) {
                    cambiar_color(12);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_Ventas.txt'...";
                }
                
                break;
            case 3:
                //coso de buscar
                break;
            case 4:
                //coso de modificar
                break;
            case 5:
                //coso de eliminar
                break;
            case 6:
                cambiar_color(11);
                cout << "      Regresando a menú de finanzas...";
                resetear_color();
                Sleep(1000);
                break;
            case 7:
                cambiar_color(11);
                cout << "      Regresando a menú principal...";
                resetear_color();
                Sleep(1000);
                break;
            default:
                cambiar_color(12);
                cout << "      Opción inválida...";
                resetear_color();
                Sleep(1000);
                break;
        }
    } while ((option != 6) && (option != 7)); //mientras no se quiera regresar a otro menu, permanecer en el bucle

    resetear_color();
    return option; //retornar la opcion del menu al que se quiere regresar
}

int pendientes() {
    int option = 0;
    bool check = false;

    do {
        system("cls || clear");
        titulo_pendientes();

        cambiar_color(14);
        cout << endl;
        cout << "   1. Mostrar pagos pendientes\n";
        cout << "   2. Buscar pago pendiente\n";
        cout << "   3. Modificar pago pendiente\n";
        cout << "   4. Eliminar pago pendiente\n";
        cambiar_color(11);
        cout << "\n   5. Regresar a menú de finanzas\n";
        cout << "   6. Regresar a menú principal\n";
        cambiar_color(9);
        cout << "\n   => Ingrese su opción: ";
        cin >> option;

        switch (option) {
            case 1:
                check = mostrar_Pendientes();
                if (!check) {
                    cambiar_color(12);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_Pendientes.txt'...";
                }
                
                break;
            case 2:
                //coso de buscar
                break;
            case 3:
                //coso de modificar
                break;
            case 4:
                //coso de eliminar
                break;
            case 5:
                cambiar_color(11);
                cout << "      Regresando a menú de finanzas...";
                resetear_color();
                Sleep(1000);
                break;
            case 6:
                cambiar_color(11);
                cout << "      Regresando a menú principal...";
                resetear_color();
                Sleep(1000);
                break;
            default:
                cambiar_color(12);
                cout << "      Opción inválida...";
                resetear_color();
                Sleep(1000);
                break;
        }
    } while ((option != 5) && (option != 6));

    resetear_color();
    return option;
}

int costos_Fijos() {
    int option = 0, num = 0;
    bool check = false;

    do {
        system("cls || clear");
        titulo_costos_Fijos();

        cambiar_color(14);
        cout << endl;
        cout << "   1. Registrar costo\n";
        cout << "   2. Mostrar costos\n";
        cout << "   3. Buscar costo\n";
        cout << "   4. Modificar costo\n";
        cout << "   5. Eliminar costo\n";
        cambiar_color(11);
        cout << "\n   6. Ir a menú de costos variables\n";
        cout << "   7. Regresar a menú de finanzas\n";
        cout << "   8. Regresar a menú principal\n";
        cambiar_color(9);
        cout << "\n   => Ingrese su opción: ";
        cin >> option;
        resetear_color();

        switch (option) {
            case 1:
                cambiar_color(14);
                cout << "     ¿Cuántos costos fijos desea registrar? ";
                cin >> num;
                resetear_color();
                check = registrar_costos_Fijos(num);

                if (!check) {
                    cambiar_color(12);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo abrir, leer y/o escribir al archivo 'registro_costos_Fijos.txt'...";
                } else {
                    cambiar_color(10);
                    cout << "\n   ***********************************************************************";
                    cout << "\n                          Costo(s) registrado(s)...";
                }

                resetear_color();
                Sleep(2250);
                break;
            case 2:
                check = mostrar_costos_Fijos();
                if (!check) {
                    cambiar_color(12);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_costos_Fijos.txt'...";
                }

                break;
            case 3:
                //coso de buscar
                break;
            case 4:
                //coso de modificar
                break;
            case 5:
                //coso de eliminar
                break;

            case 6: break; //el mensaje y el sleep se llaman en finanzas()
            case 7: break; //^^
            case 8: break; //^^

            default:
                cambiar_color(12);
                cout << "      Opción inválida...";
                resetear_color();
                Sleep(1000);
                break;
        }
    } while ((option < 6) || (option > 8)); //mientras no se quiera salir del submenu, quedarse en el do while

    resetear_color();
    return option;
}

int costos_Variables() {
    int option = 0, num = 0;
    bool check = false;

    do {
        system("cls || clear");
        titulo_costos_Variables();

        cambiar_color(14);
        cout << endl;
        cout << "   1. Registrar costo\n";
        cout << "   2. Mostrar costos\n";
        cout << "   3. Buscar costo\n";
        cout << "   4. Modificar costo\n";
        cout << "   5. Eliminar costo\n";
        cambiar_color(11);
        cout << "\n   6. Ir a menú de costos fijos\n";
        cout << "   7. Regresar a menú de finanzas\n";
        cout << "   8. Regresar a menú principal\n";
        cambiar_color(9);
        cout << "\n   => Ingrese su opción: ";
        cin >> option;
        resetear_color();

        switch (option) {
            case 1:
                cambiar_color(14);
                cout << "     ¿Cuántos costos variables desea registrar? ";
                cin >> num;
                resetear_color();
                check = registrar_costos_Variables(num);

                if (!check) {
                    cambiar_color(12);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo abrir, leer y/o escribir al archivo 'registro_costos_Variables.txt'...";
                } else {
                    cambiar_color(10);
                    cout << "\n   ***********************************************************************";
                    cout << "\n                           Costo(s) registrado(s)...";
                }

                resetear_color();
                Sleep(2250);
                break;
            case 2:
                check = mostrar_costos_Variables();
                if (!check) {
                    cambiar_color(12);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_costos_Variables.txt'...";
                }
                
                break;
            case 3:
                //coso de buscar
                break;
            case 4:
                //coso de modificar
                break;
            case 5:
                //coso de eliminar
                break;

            case 6: break; //el mensaje y el sleep se llaman en finanzas()
            case 7: break; //^^
            case 8: break; //^^

            default:
                cambiar_color(12);
                cout << "      Opción inválida...";
                resetear_color();
                Sleep(1000);
                break;
        }
    } while ((option < 6) || (option > 8));

    resetear_color();
    return option;
}

//***************************************************************************************************

int facturacion() {
    int option = 0;

    do {
        system("cls || clear");
        titulo_facturacion();

        cambiar_color(14);
        cout << endl;
        cout << "   1. Generar nueva factura\n";
        cout << "   2. Mostrar facturas\n";
        cout << "   3. Buscar factura\n";
        cout << "   4. Modificar factura\n";
        cout << "   5. Eliminar factura\n";
        cambiar_color(11);
        cout << "\n   6. Regresar a menú principal\n";
        cambiar_color(9);
        cout << "\n   => Ingrese su opción: ";
        cin >> option;
        resetear_color();

        switch (option) {
            case 1:
                //coso de generar
                break;
            case 2:
                //coso de mostrar todo
                break;
            case 3:
                //coso de buscar
                break;
            case 4:
                //coso de modificar
                break;
            case 5:
                //coso de eliminar
                break;
            case 6:
                cambiar_color(11);
                cout << "      Regresando a menú principal...";
                resetear_color();
                Sleep(1000);
                break;
            default:
                cambiar_color(12);
                cout << "      Opción inválida...";
                resetear_color();
                Sleep(1000);
                break;
        }
    } while (option != 6);

    resetear_color();
    return option;
}

int reportes() {
    int option = 0;

    do {
        system("cls || clear");
        titulo_reportes();

        cambiar_color(14);
        cout << endl;
        cout << "   1. Reporte de producción\n";
        cout << "   2. Reporte de clientes\n";
        cout << "   3. Reporte de finanzas\n";
        cambiar_color(11);
        cout << "\n   4. Regresar a menú principal\n";
        cambiar_color(9);
        cout << "\n   => Ingrese su opción: ";
        cin >> option;
        resetear_color();

        switch (option) {
            case 1:
                //coso de reporte de produccion
                break;
            case 2:
                //coso de reporte de clientes
                break;
            case 3:
                //coso de reporte de finanzas
                break;
            case 4:
                cambiar_color(11);
                cout << "      Regresando a menú principal...";
                resetear_color();
                Sleep(1000);
                break;
            default:
                cambiar_color(12);
                cout << "      Opción inválida...";
                resetear_color();
                Sleep(1000);
                break;
        }
    } while (option != 4);

    resetear_color();
    return option;
}