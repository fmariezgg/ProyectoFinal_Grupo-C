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
int costos();
int costos_Fijos();
int costos_Variables();
int ventas();
int utilidad();
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
    bool check = false;
    
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
        cout << "   6. Cambiar precio por galón de leche\n";
        cambiar_color(11);
        cout << "\n   7. Regresar a pantalla principal\n";
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
                if (submenu == 5) continue; //si el submenu retorna la opcion de regresar al menu principal, ir a la proxima iteracion
                break;
            case 2:
                cambiar_color(14);
                cout << "      Accediendo a Gestión de Clientes...";
                resetear_color();
                Sleep(1000);

                submenu = clientes();
                if (submenu == 6) continue; //^^
                break;
            case 3:
                cambiar_color(14);
                cout << "      Accediendo a Gestión de Finanzas...";
                resetear_color();
                Sleep(1000);

                submenu = finanzas();
                if (submenu == 4) continue; //^^
                break;
            case 4:
                cambiar_color(14);
                cout << "      Accediendo a Gestión de Facturación...";
                resetear_color();
                Sleep(1000);

                submenu = facturacion();
                if (submenu == 6) continue; //^^
                break;
            case 5:
                cambiar_color(14);
                cout << "      Accediendo a Gestión de Reportes...";
                resetear_color();
                Sleep(1000);

                submenu = reportes();
                if (submenu == 4) continue; //^^
                break;
            case 6:
                check = cambiar_Precio();
                if (check) {
                    cambiar_color(10);
                    cout << "Precio actualizado a: " << precio_galon << "...";
                } else {
                    cambiar_color(12);
                    cout << "ERROR DE ARCHIVO: no se pudo escribir el precio ingresado al archivo 'precio_galon.txt'...";
                }
                
                resetear_color();
                Sleep(2250);
                break;
            case 7:
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
    } while (option != 7);

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
        cout << "   2. Mostrar vacas registradas\n";
        cout << "   3. Modificar vacas\n";
        cout << "   4. Eliminar vacas\n";
        cambiar_color(11);
        cout << "\n   5. Regresar a menú principal\n";
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
                //coso de mostrar todo
                break;
            case 3:
                //coso de modificar
                break;
            case 4:
                //coso de eliminar (se palmo la vaca :< )
                break;
            case 5:
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
    } while (option != 5);

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
        cout << "   3. Buscar cliente específico\n";
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

//***************************************************************************************************

int finanzas() {
    int option = 0;
    int submenu = 0;

    do {
        system("cls || clear");
        titulo_finanzas();

        cambiar_color(14);
        cout << endl;
        cout << "   1. Acceder a menú de ventas\n";
        cout << "   2. Acceder a menú de costos\n";
        cout << "   3. Acceder a menú de utilidad\n";
        cambiar_color(11);
        cout << "\n   4. Regresar a menú principal\n";
        cambiar_color(9);
        cout << "\n   => Ingrese su opción: ";
        cin >> option;
        resetear_color();

        switch (option) {
            case 1:
                cambiar_color(14);
                cout << "      Accediendo a menú de ventas...";
                resetear_color();
                Sleep(1000);

                submenu = ventas();
                if (submenu == 7) continue; //si el submenu retorna la opcion de regresar al menu de finanzas, ir a la proxima iteracion
                else if (submenu == 8) return 4; //retorna la opcion que hace que se regrese al menu principal
                else break;
            case 2:
                cambiar_color(14);
                cout << "      Accediendo a menú de costos...";
                resetear_color();
                Sleep(1000);

                submenu = costos();
                if (submenu == 4) continue; //^^ lo mismo pero con los valores que retorna esta funcion
                else if (submenu == 5) return 4;
                else break;
            case 3:
                cambiar_color(14);
                cout << "      Accediendo a menú de utilidad...";
                resetear_color();
                Sleep(1000);

                submenu = utilidad();
                if (submenu == 3) continue; //^^ lo mismo otra vez
                if (submenu == 4) return 4;
                else break;
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

int ventas() {
    int option = 0, num = 0;
    bool check = false;

    do {
        system("cls || clear");
        titulo_ventas();

        cambiar_color(10);
        cout << endl;
        cout << "   1. Mostrar ingresos\n";
        cambiar_color(14);
        cout << "\n   2. Registrar venta\n";
        cout << "   3. Mostrar ventas\n";
        cout << "   4. Buscar venta específica\n";
        cout << "   5. Modificar ventas\n";
        cout << "   6. Eliminar ventas\n";
        cambiar_color(11);
        cout << "\n   7. Regresar a menú de finanzas\n";
        cout << "   8. Regresar a menú principal\n";
        cambiar_color(9);
        cout << "\n   => Ingrese su opción: ";
        cin >> option;
        resetear_color();
        
        switch (option) {
            case 1:
                //coso de mostrar ingresos
                break;
            case 2:
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
            case 3:
                //coso de mostrar todo
                break;
            case 4:
                //coso de buscar
                break;
            case 5:
                //coso de modificar
                break;
            case 6:
                //coso de eliminar
                break;\
            case 7:
                cambiar_color(11);
                cout << "      Regresando a menú de finanzas...";
                resetear_color();
                Sleep(1000);
                break;
            case 8:
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
    } while ((option != 7) && (option != 8)); //mientras no se quiera regresar a otro menu, permanecer en el bucle

    resetear_color();
    return option; //retornar la opcion del menu al que se quiere regresar
}

int costos() {
    int option = 0;
    int submenu = 0;

    do {
        system("cls || clear");
        titulo_costos();

        cambiar_color(12);
        cout << endl;
        cout << "   1. Calcular costos totales\n";
        cambiar_color(14);
        cout << "   2. Menú de costos fijos\n";
        cout << "   3. Menú de costos variables\n";
        cambiar_color(11);
        cout << "\n   4. Regresar a menú de finanzas\n";
        cout << "   5. Regresar a menú principal\n";
        cambiar_color(9);
        cout << "\n   => Ingrese su opción: ";
        cin >> option;
        resetear_color();

        /*si se escogio entrar a los costos fijos/variables y se quiere mover
        directamente entre los dos sin tener que regresar al menu de gestion de costos*/
        while (option == 2 || option == 3) { 
            if (option == 2) {
                cambiar_color(14);
                cout << "      Accediendo a submenú de costos fijos...";
                resetear_color();
                Sleep(1000);

                submenu = costos_Fijos();
                if (submenu == 5) option = 3; //ir al menu de costos variables
            } else if (option == 3) {
                cambiar_color(14);
                cout << "      Accediendo a submenú de costos variables...";
                resetear_color();
                Sleep(1000);

                submenu = costos_Variables();
                if (submenu == 5) option = 2; //ir al menu de costos fijos
            }

            /*si se escogio regresar al menu de finanzas directamente desde
            los menus de costos fijos/variables, asignar option al valor de este menu
            que nos regresa a al menu de finanzas y nos saca de este while*/
            if (submenu == 6) option = 4;

            //^^ lo mismo pero con el menu principal
            else if (submenu == 7) option = 5;
        }

        //si no se entro a los de costos, resolver los otros casos de option
        switch (option) {
            case 1:
                //coso de costos totales
                break;
            case 4:
                cambiar_color(11);
                cout << "      Regresando a menú finanzas...";
                resetear_color();
                Sleep(1000);
                break;
            case 5:
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
    } while ((option != 4) && (option != 5));

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
        cout << "   3. Modificar costo\n";
        cout << "   4. Eliminar costo\n";
        cambiar_color(11);
        cout << "\n   5. Ir a menú de costos variables\n";
        cout << "   6. Regresar a menú finanzas\n";
        cout << "   7. Regresar a menú principal\n";
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
                //coso de mostrar todo
                break;
            case 3:
                //coso de modificar
                break;
            case 4:
                //coso de eliminar
                break;

            case 5: break; //el mensaje y el sleep se llaman en costos()
            case 6: break; //^^
            case 7: break; //^^

            default:
                cambiar_color(12);
                cout << "      Opción inválida...";
                resetear_color();
                Sleep(1000);
                break;
        }
    } while ((option < 5) || (option > 7)); //mientras no se quiera salir del submenu, quedarse en el do while

    resetear_color();
    return option; //cuando se quiera salir, terminar el bucle y retornar option
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
        cout << "   3. Modificar costo\n";
        cout << "   4. Eliminar costo\n";
        cambiar_color(11);
        cout << "\n   5. Ir a menú de costos fijos\n";
        cout << "   6. Regresar a menú finanzas\n";
        cout << "   7. Regresar a menú principal\n";
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
                //coso de mostrar todo
                break;
            case 3:
                //coso de modificar
                break;
            case 4:
                //coso de eliminar
                break;

            case 5: break; //el mensaje y el sleep se llaman en costos()
            case 6: break; //^^
            case 7: break; //^^

            default:
                cambiar_color(12);
                cout << "      Opción inválida...";
                resetear_color();
                Sleep(1000);
                break;
        }
    } while ((option < 5) || (option > 7)); //mientras no se quiera salir del submenu, quedarse en el do while

    resetear_color();
    return option; //cuando se quiera salir, terminar el bucle y retornar option
}

int utilidad() {
    int option = 0;

    do {
        system("cls || clear");
        titulo_utilidad();

        cambiar_color(14);
        cout << endl;
        cout << "   1. Calcular utilidad bruta\n";
        cout << "   2. Calcular utilidad operativa\n";
        cambiar_color(11);
        cout << "\n   3. Regresar a menú de finanzas\n";
        cout << "   4. Regresar a menú principal\n";
        cambiar_color(9);
        cout << "\n   => Ingrese su opción: ";
        cin >> option;
        resetear_color();
    
        switch (option) {
            case 1:
                //coso de calcular utilidad bruta
                break;
            case 2:
                //coso de calcular utilidad operativa
                break;
            case 3:
                cambiar_color(11);
                cout << "      Regresando a menú de finanzas...";
                resetear_color();
                Sleep(1000);
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
    } while ((option != 3) && (option != 4)); //mientras no se quiera regresar a otro menu, permanecer en el bucle

    resetear_color();
    return option; //retornar la opcion del menu al que se quiere regresar
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
        cout << "   3. Buscar factura específica\n";
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