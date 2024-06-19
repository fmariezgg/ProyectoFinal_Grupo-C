#include <iostream>
#include <windows.h>
#include "funciones.cpp"
using namespace std;

//menus y submenus:
int start_screen();
int principal();
int produccion();
int clientes();
int finanzas();
int costos();
int costos_Fijos();
int costos_Variables();
int ventas();
int utilidad();
int facturas();
int reportes();

//***************************************************************************************************

int start_screen() {
    int option = 0;

    cout << " /$$    /$$                      /$$                                     /$$                 /$$                           /$$\n";
    cout << "| $$   | $$                     | $$                                    | $$                | $$                          | $$\n";
    cout << "| $$   | $$ /$$$$$$  /$$$$$$$  /$$$$$$    /$$$$$$   /$$$$$$$        /$$$$$$$  /$$$$$$       | $$        /$$$$$$   /$$$$$$$| $$$$$$$   /$$$$$$\n";
    cout << "|  $$ / $$//$$__  $$| $$__  $$|_  $$_/   |____  $$ /$$_____/       /$$__  $$ /$$__  $$      | $$       /$$__  $$ /$$_____/| $$__  $$ /$$__  $$\n";
    cout << " \\  $$ $$/| $$$$$$$$| $$  \\ $$  | $$      /$$$$$$$|  $$$$$$       | $$  | $$| $$$$$$$$      | $$      | $$$$$$$$| $$      | $$  \\ $$| $$$$$$$\n";
    cout << "  \\  $$$/ | $$_____/| $$  | $$  | $$ /$$ /$$__  $$ \\____  $$      | $$  | $$| $$_____/      | $$      | $$_____/| $$      | $$  | $$| $$_____/\n";
    cout << "   \\  $/  |  $$$$$$$| $$  | $$  |  $$$$/|  $$$$$$$ /$$$$$$$/      |  $$$$$$$|  $$$$$$$      | $$$$$$$$|  $$$$$$$|  $$$$$$$| $$  | $$|  $$$$$$$\n";
    cout << "    \\_/    \\_______/|__/  |__/   \\___/   \\_______/|_______/        \\_______/ \\_______/      |________/ \\_______/ \\_______/|__/  |__/ \\_______/\n" << endl;
    cout << "v1.0.0: por Fátima Zogaib y Joaquín Pérez\n";
    cout << "----------------------------------------------------------------------------------------------------------------------------------------------\n";

    cout << "\n1. Acceder a menú principal\n";
    cout << "2. Cerrar programa\n";
    cout << "\nIngrese su opción: ";
    cin >> option;
    return option;
}

int principal() {
    int option = 0, submenu = 0;
    bool check = false;
    
    do {
        system("cls || clear");
        cout << "\n\t\t\tMenú Principal:\n";
        cout << "---------------------------------------------------------------\n";
        cout << "\n1. Acceder a Gestión de Producción\n";
        cout << "2. Acceder a Gestión de Clientes\n";
        cout << "3. Acceder a Gestión de Finanzas\n";
        cout << "4. Acceder a Gestión de Facturación\n";
        cout << "5. Acceder a Gestión de Reportes\n";
        cout << "\n6. Cambiar precio por galón de leche\n";
        cout << "7. Regresar a pantalla principal\n";
        cout << "\nIngrese su opción: ";
        cin >> option;

        switch (option) {
            case 1:
                cout << "Accediendo a Gestión de Producción...";
                Sleep(1000);
                submenu = produccion(); //llamar al submenu
                if (submenu == 5) continue; //si el submenu retorna la opcion de regresar al menu principal, ir a la proxima iteracion
                break;
            case 2:
                cout << "Accediendo a Gestión de Clientes...";
                Sleep(1000);
                submenu = clientes();
                if (submenu == 6) continue; //^^
                break;
            case 3:
                cout << "Accediendo a Gestión de Finanzas...";
                Sleep(1000);
                submenu = finanzas();
                if (submenu == 4) continue; //^^
                break;
            case 4:
                cout << "Accediendo a Gestión de Facturación...";
                Sleep(1000);
                submenu = facturas();
                if (submenu == 6) continue; //^^
                break;
            case 5:
                cout << "Accediendo a Gestión de Reportes...";
                Sleep(1000);
                submenu = reportes();
                if (submenu == 4) continue; //^^
                break;
            case 6:
                check = cambiar_Precio();
                if (check) cout << "Precio actualizado a: " << precio_galon << "...\n\n";
                else cout << "\nERROR DE ARCHIVO: no se pudo escribir el precio ingresado al archivo 'precio_galon.txt'...\n\n";

                system("pause");
                break;
            case 7:
                cout << "Regresando a pantalla principal...";
                Sleep(1000);
                break;
            default:
                cout << "\nOpción inválida...";
                Sleep(1000);
                break;
        }
    } while (option != 7);

    return option;
}

//***************************************************************************************************

int produccion() {
    int option = 0, num = 0;
    bool check = false;

    do {
        system("cls || clear");
        cout << "\n\t\t\tGestión de Producción:\n";
        cout << "---------------------------------------------------------------\n";
        cout << "\n1. Registrar vacas\n";
        cout << "2. Mostrar vacas registradas\n";
        cout << "3. Modificar vacas\n";
        cout << "4. Eliminar vacas\n";
        cout << "5. Regresar a menú principal\n";
        cout << "\nIngrese su opción: ";
        cin >> option;

        switch (option) {
            case 1:
                cout << "\n¿Cuántas vacas desea registrar? ";
                cin >> num;
                check = registrar_Vacas(num);

                if (!check) cout << "\nERROR DE ARCHIVO: no se pudo abrir, leer y/o escribir al archivo 'registro_Vacas.txt'...\n\n";
                else cout << "\nVacas registradas...\n\n";

                system("pause");
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
                cout << "Regresando a menú principal...";
                Sleep(1000);
                break;
            default:
                cout << "\nOpción inválida...";
                Sleep(1000);
                break;
        }
    } while (option != 5);

    return option;
}

int clientes() {
    int option = 0, num = 0;
    bool check = false;

    do {
        system("cls || clear");
        cout << "\n\t\t\tGestión de Clientes:\n";
        cout << "---------------------------------------------------------------\n";
        cout << "\n1. Registrar clientes\n";
        cout << "2. Mostrar clientes\n";
        cout << "3. Buscar cliente específico\n";
        cout << "4. Modificar clientes\n";
        cout << "5. Eliminar clientes\n";
        cout << "6. Regresar a menú principal\n";
        cout << "\nIngrese su opción: ";
        cin >> option;

        switch (option) {
            case 1:
                cout << "\n¿Cuántos clientes desea registrar? ";
                cin >> num;
                check = registrar_Clientes(num);

                if (!check) cout << "\nERROR DE ARCHIVO: no se pudo abrir, leer y/o escribir al archivo 'registro_Clientes.txt'...\n\n";
                else cout << "\nClientes registrados...\n\n";

                system("pause");
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
                cout << "Regresando a menú principal...";
                Sleep(1000);
                break;
            default:
                cout << "\nOpción inválida...";
                Sleep(1000);
                break;
        }
    } while (option != 6);

    return option;
}

//***************************************************************************************************

int finanzas() {
    int option = 0;
    int submenu = 0;

    do {
        system("cls || clear");
        cout << "\n\t\t\tGestión de Finanzas:\n";
        cout << "---------------------------------------------------------------\n";
        cout << "\n1. Acceder a menú de ventas\n";
        cout << "2. Acceder a menú de costos\n";
        cout << "3. Calcular utilidad\n";
        cout << "4. Regresar a menú principal\n";
        cout << "\nIngrese su opción: ";
        cin >> option;

        switch (option) {
            case 1:
                cout << "Accediendo a menú de ventas...";
                Sleep(1000);
                submenu = ventas();
                if (submenu == 7) continue; //si el submenu retorna la opcion de regresar al menu de finanzas, ir a la proxima iteracion
                else if (submenu == 8) return 4; //retorna la opcion que hace que se regrese al menu principal
                else break;
            case 2:
                cout << "Accediendo a menú de costos...";
                Sleep(1000);
                submenu = costos();
                if (submenu == 4) continue; //^^ lo mismo pero con los valores que retorna esta funcion
                else if (submenu == 5) return 4;
                else break;
            case 3:
                cout << "Accediendo a menú de utilidad...";
                Sleep(1000);
                submenu = utilidad();
                if (submenu == 3) continue; //^^ lo mismo otra vez
                if (submenu == 4) return 4;
                else break;
            case 4:
                cout << "Regresando a menú principal...";
                Sleep(1000);
                break;
            default:
                cout << "\nOpción inválida...";
                Sleep(1000);
                break;
        }
    } while (option != 4);

    return option;
}

int ventas() {
    int option = 0, num = 0;
    bool check = false;

    do {
        system("cls || clear");
        cout << "\n\t\t\tGestión de Ventas:\n";
        cout << "---------------------------------------------------------------\n";
        cout << "1. Mostrar ingresos\n";
        cout << "\n2. Registrar venta\n";
        cout << "3. Mostrar ventas\n";
        cout << "4. Buscar venta específica\n";
        cout << "5. Modificar ventas\n";
        cout << "6. Eliminar ventas\n";
        cout << "\n7. Regresar a menú de finanzas\n";
        cout << "8. Regresar a menú principal\n";
        cout << "\nIngrese su opción: ";
        cin >> option;
        
        switch (option) {
            case 1:
                //coso de mostrar ingresos
            case 2:
                cout << "\n¿Cuántas ventas desea registrar? ";
                cin >> num;
                check = registrar_Ventas(num);

                if (!check) cout << "\nERROR DE ARCHIVO: no se pudo abrir, leer y/o escribir a los archivos: 'registro_Ventas.txt', 'registro_Pendientes', 'precio_galon.txt'...\n\n";
                else cout << "\nVentas registradas...\n\n";

                system("pause");
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
                cout << "Regresando a menú de finanzas...";
                Sleep(1000);
                break;
            case 8:
                cout << "Regresando a menú principal...";
                Sleep(1000);
                break;
            default:
                cout << "\nOpción inválida...";
                Sleep(1000);
                break;
        }
    } while ((option != 7) && (option != 8)); //mientras no se quiera regresar a otro menu, permanecer en el bucle

    return option; //retornar la opcion del menu al que se quiere regresar
}

int costos() {
    int option = 0;
    int submenu = 0;

    do {
        system("cls || clear");
        cout << "\n\t\t\tGestión de Costos:\n";
        cout << "---------------------------------------------------------------\n";
        cout << "\n1. Menú de costos fijos\n";
        cout << "2. Menú de costos variables\n";
        cout << "3. Calcular costos totales\n";
        cout << "\n4. Regresar a menú de finanzas\n";
        cout << "5. Regresar a menú principal\n";
        cout << "\nIngrese su opción: ";
        cin >> option;

        /*si se escogio entrar a los costos fijos/variables y se quiere mover
        directamente entre los dos sin tener que regresar al menu de gestion de costos*/
        while (option == 1 || option == 2) { 
            if (option == 1) {
                cout << "Accediendo a submenú de costos fijos...";
                Sleep(1000);
                submenu = costos_Fijos();
                if (submenu == 5) option = 2; //ir al menu de costos variables
            } else if (option == 2) {
                cout << "Accediendo a submenú de costos variables...";
                Sleep(1000);
                submenu = costos_Variables();
                if (submenu == 5) option = 1; //ir al menu de costos fijos
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
            case 3:
                //coso de costos totales
            case 4:
                //el mensaje se llama en costos_Fijos() y costos_Variables()
                Sleep(1000);
                break;
            case 5:
                //^^
                Sleep(1000);
                break;
            default:
                cout << "\nOpción inválida...";
                Sleep(1000);
                break;
        }
    } while ((option != 4) && (option != 5));

    return option;
}

int costos_Fijos() {
    int option = 0, num = 0;
    bool check = false;

    do {
        system("cls || clear");
        cout << "\n\t\t\tSubmenú de Costos Fijos:\n";
        cout << "---------------------------------------------------------------\n";
        cout << "\n1. Registrar costo\n";
        cout << "2. Mostrar costos\n";
        cout << "3. Modificar costo\n";
        cout << "4. Eliminar costo\n";
        cout << "\n5. Ir a menú de costos variables\n";
        cout << "6. Regresar a menú finanzas\n";
        cout << "7. Regresar a menú principal\n";
        cout << "\nIngrese su opción: ";
        cin >> option;

        switch (option) {
            case 1:
                cout << "\n¿Cuántos costos fijos desea registrar? ";
                cin >> num;
                check = registrar_costos_Fijos(num);

                if (!check) cout << "\nERROR DE ARCHIVO: no se pudo abrir, leer y/o escribir al archivo 'registro_costos_Fijos.txt'...\n\n";
                else cout << "\nCostos registrados...\n\n";

                system("pause");
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
            case 5:
                //el mensaje y el sleep se llaman en costos()
                break;
            case 6:
                cout << "Regresando a menú finanzas..."; //el sleep se llama en el switch de costos()
                break;
            case 7:
                cout << "Regresando a menú principal..."; //^^
                break;
            default:
                cout << "\nOpción inválida...";
                Sleep(1000);
                break;
        }
    } while ((option < 5) || (option > 7)); //mientras no se quiera salir del submenu, quedarse en el do while

    return option; //cuando se quiera salir, terminar el bucle y retornar option
}

int costos_Variables() {
    int option = 0, num = 0;
    bool check = false;

    do {
        system("cls || clear");
        cout << "\n\t\t\tSubmenú de Costos Variables:\n";
        cout << "---------------------------------------------------------------\n"; 
        cout << "\n1. Registrar costo\n";
        cout << "2. Mostrar costos\n";
        cout << "3. Modificar costo\n";
        cout << "4. Eliminar costo\n";
        cout << "\n5. Ir a menú de costos fijos\n";
        cout << "6. Regresar a menú finanzas\n";
        cout << "7. Regresar a menú principal\n";
        cout << "\nIngrese su opción: ";
        cin >> option;

        switch (option) {
            case 1:
                cout << "\n¿Cuántos costos variables desea registrar? ";
                cin >> num;
                check = registrar_costos_Variables(num);

                if (!check) cout << "\nERROR DE ARCHIVO: no se pudo abrir, leer y/o escribir al archivo 'registro_costos_Variables.txt'...\n\n";
                else cout << "\nCostos registrados...\n\n";

                system("pause");
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
            case 5:
                //el mensaje y el sleep se llaman en costos()
                break;
            case 6:
                cout << "Regresando a menú finanzas..."; //el sleep se llama en el switch de costos()
                break;
            case 7:
                cout << "Regresando a menú principal..."; //^^
                break;
            default:
                cout << "\nOpción inválida...";
                Sleep(1000);
                break;
        }
    } while ((option < 5) || (option > 7)); //mientras no se quiera salir del submenu, quedarse en el do while

    return option; //cuando se quiera salir, terminar el bucle y retornar option
}

int utilidad() {
    int option = 0;

    do {
        system("cls || clear");
        cout << "\n\t\t\tGestión de Utilidad:\n";
        cout << "---------------------------------------------------------------\n";
        cout << "1. Calcular utilidad bruta\n";
        cout << "2. Calcular utilidad operativa\n";
        cout << "3. Regresar a menú de finanzas\n";
        cout << "4. Regresar a menú principal\n";
        cout << "\nIngrese su opción: ";
        cin >> option;
    
        switch (option) {
            case 1:
                //coso de calcular utilidad bruta
                break;
            case 2:
                //coso de calcular utilidad operativa
                break;
            case 3:
                cout << "Regresando a menú de finanzas...";
                Sleep(1000);
                break;
            case 4:
                cout << "Regresando a menú principal...";
                Sleep(1000);
                break;
            default:
                cout << "\nOpción inválida...";
                Sleep(1000);
                break;
        }
    } while ((option != 3) && (option != 4)); //mientras no se quiera regresar a otro menu, permanecer en el bucle

    return option; //retornar la opcion del menu al que se quiere regresar
}

//***************************************************************************************************

int facturas() {
    int option = 0;

    do {
        system("cls || clear");
        cout << "\n\t\t\tGestión de Facturación:\n";
        cout << "---------------------------------------------------------------\n";
        cout << "\n1. Generar nueva factura\n";
        cout << "2. Mostrar facturas\n";
        cout << "3. Buscar factura específica\n";
        cout << "4. Modificar factura\n";
        cout << "5. Eliminar factura\n";
        cout << "6. Regresar a menú principal\n";
        cout << "\nIngrese su opción: ";
        cin >> option;

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
                cout << "Regresando a menú principal...";
                Sleep(1000);
                break;
            default:
                cout << "\nOpción inválida...";
                Sleep(1000);
                break;
        }
    } while (option != 6);

    return option;
}

int reportes() {
    int option = 0;

    do {
        system("cls || clear");
        cout << "\n\t\t\tGestión de Reportes:\n";
        cout << "---------------------------------------------------------------\n";
        cout << "\n1. Reporte de producción\n";
        cout << "2. Reporte de clientes\n";
        cout << "3. Reporte de finanzas\n";
        cout << "4. Regresar a menú principal\n";
        cout << "\nIngrese su opción: ";
        cin >> option;

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
                cout << "Regresando a menú principal...";
                Sleep(1000);
                break;
            default:
                cout << "\nOpción inválida...";
                Sleep(1000);
                break;
        }
    } while (option != 4);

    return option;
}