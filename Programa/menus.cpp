#include "modulos/prototipos.h"
using namespace std;
using namespace LLC;

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

    do {
        system("cls || clear");
        title_splash();

        _colSET(cLIGHT_YELLOW);
        cout << endl;
        cout << "   1. Acceder a menú principal\n";
        _colSET(cRED);
        cout << "   2. Cerrar programa\n";
        _colSET(cTEAL);
        cout << "\n   => Ingrese su opción: ";
        cin >> option;
        _colRESET();

        if (cin.fail()) {
            error_opcion();
            continue;
        } else break;
        
    } while (true);

    return option;
}

int principal() {
    int option = 0, submenu = 0;
    
    do {
        system("cls || clear");
        menu_principal();

        _colSET(cLIGHT_YELLOW);
        cout << endl;
        cout << "   1. Acceder a Gestión de Producción\n";
        cout << "   2. Acceder a Gestión de Clientes\n";
        cout << "   3. Acceder a Gestión de Finanzas\n";
        _colSET(cCYAN);
        cout << "\n   4. Regresar a pantalla principal\n";
        _colSET(cTEAL);
        cout << "\n   => Ingrese su opción: ";
        cin >> option;
        _colRESET();

        if (cin.fail()) {
            error_opcion();
            continue;
        }

        switch (option) {
            case 1:
                _colSET(cLIGHT_YELLOW);
                cout << "      Accediendo a Gestión de Producción...";
                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));

                submenu = produccion(); //llamar al submenu
                if (submenu == 7) continue; //si el submenu retorna la opcion de regresar al menu principal, ir a la proxima iteracion
                break;
            case 2:
                _colSET(cLIGHT_YELLOW);
                cout << "      Accediendo a Gestión de Clientes...";
                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));

                submenu = clientes(); //^^
                if (submenu == 6) continue;
                break;
            case 3:
                _colSET(cLIGHT_YELLOW);
                cout << "      Accediendo a Gestión de Finanzas...";
                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));

                submenu = finanzas(); //^^
                if (submenu == 9) continue;
                break;
            case 4:
                _colSET(cCYAN);
                cout << "      Regresando a pantalla principal...";
                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));
                break;
            default:
                _colSET(cRED);
                cout << "      Opción inválida...";
                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));
                break;
        }
    } while (option != 4);

    _colRESET();
    return option;
}

//***************************************************************************************************

int produccion() {
    int option = 0, indice = 0; //indice: la posicion de un id en el registro
    char input_id[ID] = ""; //esta es para guardar el id que se va a buscar
    bool check = false; //para checkear si se pudo abrir/leer/escribir a un archivo

    do {
        system("cls || clear");
        titulo_prod();
        
        cout << endl << "   1. Calcular producción total\n";
        _colSET(cLIGHT_YELLOW);
        cout << "\n   2. Registrar vacas\n";
        cout << "   3. Mostrar vacas\n";
        cout << "   4. Buscar vaca\n";
        cout << "   5. Modificar datos de vaca\n";
        cout << "   6. Eliminar vaca\n";
        _colSET(cCYAN);
        cout << "\n   7. Regresar a menú principal\n";
        _colSET(cTEAL);
        cout << "\n   => Ingrese su opción: ";
        cin >> option;
        _colRESET();

        if (cin.fail()) {
            error_opcion();
            continue;
        }

        switch (option) {
            case 1:
                check = calcular_Produccion(); //la misma funcion checkea si el registro estaba vacio
                if (!check) {
                    _colSET(cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_Vacas.txt'...";
                    _colRESET();
                   this_thread::sleep_for(chrono::milliseconds(2250));
                }
                
                break;
            case 2:
                check = registrar_Vacas();

                if (!check) {
                    _colSET(cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo abrir, leer y/o escribir al archivo 'registro_Vacas.txt'...";
                } else {
                    _colSET(cGREEN);
                    cout << "\n   ***********************************************************************";
                    cout << "\n                           Vaca(s) registrada(s)...";
                }

                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(2250));
                break;
            case 3:
                check = mostrar_Vacas();
                if (!check) {
                    _colSET(cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_Vacas.txt'...";
                    _colRESET();
                    this_thread::sleep_for(chrono::milliseconds(2250));
                }

                break;
            case 4:
                system("cls || clear");
                cout << endl;
                pedir_Cstring("ID de la vaca a buscar", input_id, ID);
                check = leer_Archivos("registro_Vacas.txt");
                if (check) indice = buscar_Vaca(input_id); //si se pudo leer el archivo, buscar el id
                else indice = -2; //si no, ponerle -2 a id para que se ejecute el else if correcto

                _colSET(cTEAL);
                cout << "\n   Buscando vaca...";
                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(800));

                if (indice == -1) {
                    _colSET(cRED);
                    cout << "\n   ERROR: el ID '" << input_id << "' no se encontró en el registro...";
                    this_thread::sleep_for(chrono::milliseconds(2250));
                } else if (indice == -2) {
                    _colSET(cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_Vacas.txt'...";
                    this_thread::sleep_for(chrono::milliseconds(2250));
                } else if (indice >= 0) {
                    _colSET(cGREEN);
                    cout << "\n   Vaca encontrada!";
                    this_thread::sleep_for(chrono::milliseconds(800));

                    _colSET(cCYAN);
                    cout << endl << "\n                                  Vaca #" << indice+1 << ":" << endl;
                    cout << "   ***********************************************************************\n";
                    _colSET(cLIGHT_YELLOW);
                    cout << "   ID: " << registro_Vacas[indice].id << "\n";
                    cout << "   Edad: " << registro_Vacas[indice].edad << "\n";
                    cout << "   Producción diaria: " << registro_Vacas[indice].prod_diaria << "\n";
                    cout << "   Estado de salud: " << registro_Vacas[indice].estado_salud << endl;
                    _colSET(cCYAN);
                    cout << endl << "   ***********************************************************************\n";
                    cout << "   Presione 'Enter' para continuar...";
                    cin.get();
                }
                
                _colRESET();
                break;
            case 5:
                check = editar_Vaca();
                if (!check) {
                    _colSET(cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_Vacas.txt'...";
                    this_thread::sleep_for(chrono::milliseconds(2250));
                }

                break;
            case 6: //se palmo la vaca :(
                system("cls || clear");
                cout << endl;
                pedir_Cstring("ID de la vaca a eliminar", input_id, ID);
                indice = eliminar_Vaca(input_id);

                _colSET(cTEAL);
                cout << "\n   Buscando vaca...";
                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(800));

                if (indice == -1) {
                    _colSET(cRED);
                    cout << "\n   ERROR: el ID '" << input_id << "' no se encontró en el registro...";
                } else if (indice == -2) {
                    _colSET(cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_Vacas.txt'...";
                } else if (indice == 0) {
                    _colSET(cGREEN);
                    cout << "\n   Vaca eliminada!";     
                }
                
                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(1500));
                break;
            case 7:
                _colSET(cCYAN);
                cout << "      Regresando a menú principal...";
                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));
                break;
            default:
                _colSET(cRED);
                cout << "      Opción inválida...";
                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));
                break;
        }
    } while (option != 7);

    _colRESET();
    return option;
}

int clientes() {
    int option = 0, indice = 0; //igual que el menu de produccion
    char input_id[ID] = "";
    bool check = false;

    do {
        system("cls || clear");
        titulo_clientes();

        _colSET(cLIGHT_YELLOW);
        cout << endl;
        cout << "   1. Registrar clientes\n";
        cout << "   2. Mostrar clientes\n";
        cout << "   3. Buscar cliente\n";
        cout << "   4. Modificar datos de cliente\n";
        cout << "   5. Eliminar cliente\n";
        _colSET(cCYAN);
        cout << "\n   6. Regresar a menú principal\n";
        _colSET(cTEAL);
        cout << "\n   => Ingrese su opción: ";
        cin >> option;
        _colRESET();

        if (cin.fail()) {
            error_opcion();
            continue;
        }

        switch (option) {
            case 1:
                check = registrar_Clientes();

                if (!check) {
                    _colSET(cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo abrir, leer y/o escribir al archivo 'registro_Clientes.txt'...";
                } else {
                    _colSET(cGREEN);
                    cout << "\n   ***********************************************************************";
                    cout << "\n                          Cliente(s) registrado(s)...";
                }

                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(2250));
                break;
            case 2:
                check = mostrar_Clientes();
                if (!check) {
                    _colSET(cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_Clientes.txt'...";
                    _colRESET();
                    this_thread::sleep_for(chrono::milliseconds(2250));
                }
                
                break;
            case 3:
                system("cls || clear");
                cout << endl;
                pedir_Cstring("ID del cliente a buscar", input_id, ID);
                check = leer_Archivos("registro_Clientes.txt");
                if (check) indice = buscar_Cliente(input_id, false); //lo mismo de solo buscar el id si se pudo leer el archivo
                else indice = -2;

                _colSET(cTEAL);
                cout << "\n   Buscando cliente...";
                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(800));

                if (indice == -1) {
                    _colSET(cRED);
                    cout << "\n   ERROR: el ID '" << input_id << "' no se encontró en el registro...";
                    this_thread::sleep_for(chrono::milliseconds(2250));
                } else if (indice == -2) {
                    _colSET(cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_Clientes.txt'...";
                    this_thread::sleep_for(chrono::milliseconds(2250));
                } else if (indice >= 0) {
                    _colSET(cGREEN);
                    cout << "\n   Cliente encontrado!";
                    this_thread::sleep_for(chrono::milliseconds(800));

                    _colSET(cCYAN);
                    cout << endl << "\n                                  Cliente #" << indice+1 << ":" << endl;
                    cout << "   ***********************************************************************\n";
                    _colSET(cLIGHT_YELLOW);
                    cout << "   ID: " << registro_Clientes[indice].id << "\n";
                    cout << "   Nombre: " << registro_Clientes[indice].nombre << "\n";
                    cout << "   Dirección: " << registro_Clientes[indice].direccion << "\n";
                    cout << "   Contacto: " << registro_Clientes[indice].contacto << endl;
                    _colSET(cCYAN);
                    cout << endl << "   ***********************************************************************\n";
                    cout << "   Presione 'Enter' para continuar...";
                    cin.get();
                }

                _colRESET();
                break;
            case 4:
                check = editar_Cliente();
                if (!check) {
                    _colSET(cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_Clientes.txt'...";
                    _colRESET();
                    this_thread::sleep_for(chrono::milliseconds(2250));
                }

                break;
            case 5:
                system("cls || clear");
                cout << endl;
                pedir_Cstring("ID del cliente a eliminar", input_id, ID);
                indice = eliminar_Cliente(input_id);

                _colSET(cTEAL);
                cout << "\n   Buscando cliente...";
                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(800));

                if (indice == -1) {
                    _colSET(cRED);
                    cout << "\n   ERROR: el ID '" << input_id << "' no se encontró en el registro...";
                } else if (indice == -2) {
                    _colSET(cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_Clientes.txt'...";
                } else if (indice == 0) {
                    _colSET(cGREEN);
                    cout << "\n   Cliente eliminado!";     
                }
                
                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(1500));
                break;
            case 6:
                _colSET(cCYAN);
                cout << "      Regresando a menú principal...";
                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));
                break;
            default:
                _colSET(cRED);
                cout << "      Opción inválida...";
                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));
                break;
        }
    } while (option != 6);

    _colRESET();
    return option;
}

//***************************************************************************************************

int finanzas() {
    int option = 0, submenu = 0;
    bool check = false;

    do {
        system("cls || clear");
        titulo_finanzas();

        _colSET(cLIGHT_YELLOW);
        cout << endl;
        cout << "   1. Acceder a menú de ventas\n";
        cout << "   2. Acceder a menú de pagos pendientes\n";
        cout << "   3. Acceder a menú de costos fijos\n";
        cout << "   4. Acceder a menú de costos variables\n";
        _colSET(cGREEN);
        cout << "\n   5. Calcular ingresos totales\n";
        _colSET(cRED);
        cout << "   6. Calcular costos totales\n";
        _colRESET();
        cout << "   7. Calcular utilidad\n";
        _colSET(cLIGHT_YELLOW);
        cout << "\n   8. Mostrar precio por galón\n";
        cout << "   9. Cambiar precio por galón\n";
        _colSET(cCYAN);
        cout << "\n   10. Regresar a menú principal\n";
        _colSET(cTEAL);
        cout << "\n   => Ingrese su opción: ";
        cin >> option;
        _colRESET();

        if (cin.fail()) {
            error_opcion();
            continue;
        }

        /*esto es por si se escogio entrar a los menus de costos fijos/variables y se quiere mover
        directamente entre los dos sin tener que regresar al menu de finanzas*/
        while (option == 3 || option == 4) { 
            if (option == 3) {
                _colSET(cLIGHT_YELLOW);
                cout << "      Accediendo a submenú de costos fijos...";
                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));

                submenu = costos_Fijos();
                if (submenu == 6) option = 4; //ir al menu de costos variables
            } else if (option == 4) {
                _colSET(cLIGHT_YELLOW);
                cout << "      Accediendo a submenú de costos variables...";
                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));

                submenu = costos_Variables();
                if (submenu == 6) option = 3; //ir al menu de costos fijos
            }

            //si se escogio regresar al menu de finanzas, salir del while, y entrar al caso correspondiente del switch
            if (submenu == 7) {
                _colSET(cCYAN);
                cout << "      Regresando a menú de finanzas...";
                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));
                break;
            }

            /*si se escogio regresar al menu principal directamente desde
            los menus de costos fijos/variables, option toma el valor de este menu
            que nos regresa a al menu principal y nos saca de este while y el do while*/
            else if (submenu == 8) option = 10;
        }

        //resolver el resto de los casos del menu con el switch
        switch (option) {
            case 1:
                _colSET(cLIGHT_YELLOW);
                cout << "      Accediendo a menú de ventas...";
                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));

                submenu = ventas();
                if (submenu == 6) continue; //si el submenu retorna la opcion de regresar al menu de finanzas, ir a la proxima iteracion
                else if (submenu == 7) return 10; //retorna la opcion que hace que termine el do while y se regrese al menu principal
                break;
            case 2:
                _colSET(cLIGHT_YELLOW);
                cout << "      Accediendo a menú de pagos pendientes...";
                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));

                submenu = pendientes();
                if (submenu == 5) continue; //^^
                else if (submenu == 6) return 10; //^^
                break;

            case 3: break; //para que el switch no se vaya al caso default si option es 3 o 4
            case 4: break; //^^

            case 5:
                check = calcular_Ingresos();

                if (!check) {
                    _colSET(cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer uno o más de los siguientes archivos: 'registro_Ventas.txt', 'registro_Pendientes.txt'...";
                    _colRESET();
                }
                
                //si no se pudo calcular, checkear_Vacio va a imprimir el mensaje correcto a la consola, y no hay que hacer nada mas
                //pero si ingresos_totales si tiene un valor, mostrarlo
                if (ingresos_totales != 0.00) {
                    _colSET(cTEAL);
                    cout << "\n   Calculando...";
                    this_thread::sleep_for(chrono::milliseconds(1000));
                    _colSET(cLIGHT_YELLOW);
                    cout << "\n   Ingresos totales mensuales: ";
                    _colSET(cGREEN);
                    cout << "C$" << ingresos_totales;
                    _colSET(cGRAY);
                    cout << "\n\n   Presione 'Enter' para continuar...";
                    cin.get();
                    _colRESET();
                }

                break;
            case 6:
                check = calcular_Costos();

                if (!check) {
                    _colSET(cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer uno o más de los siguientes archivos: 'costos_Fijos.txt', 'costos_Variables.txt'...";
                    _colRESET();
                }

                if (costos_totales != 0.00) { //lo mismo que con los ingresos
                    _colSET(cTEAL);
                    cout << "\n   Calculando...";
                    this_thread::sleep_for(chrono::milliseconds(1000));
                    _colSET(cLIGHT_YELLOW);
                    cout << "\n   Costos totales mensuales: ";
                    _colSET(cRED);
                    cout << "C$" << costos_totales;
                    _colSET(cGRAY);
                    cout << "\n\n   Presione 'Enter' para continuar...";
                    cin.get();
                    _colRESET();
                }

                break;
            case 7:
                check = calcular_Utilidad(); //la misma funcion checkea si no se pudo calcular/estaba vacio el registro
                if (!check) {
                    _colSET(cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer uno o más de los siguientes archivos: 'registro_Ventas.txt', 'registro_Pendientes.txt', 'costos_Fijos.txt', 'costos_Variables.txt'...";
                    _colRESET();
                }

                break;
            case 8:
                check = mostrar_Precio();
                if (!check) {
                   this_thread::sleep_for(chrono::milliseconds(500));
                    _colSET(cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'precio_galon.txt'...";
                    _colRESET();
                }

                this_thread::sleep_for(chrono::milliseconds(2250));
                break;
            case 9:
                check = ingresar_Precio();
                if (!check) {
                    _colSET(cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo escribir el precio ingresado al archivo 'precio_galon.txt'...";
                    _colRESET();
                }
                
                this_thread::sleep_for(chrono::milliseconds(2250));
                break;
            case 10:
                _colSET(cCYAN);
                cout << "      Regresando a menú principal...";
                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));
                break;
            default:
                _colSET(cRED);
                cout << "      Opción inválida...";
                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));
                break;
        }
    } while (option != 10);

    _colRESET();
    return option;
}

int ventas() {
    int option = 0, indice = 0; //igual que los menus anteriores
    char input_id[ID] = "", pagada[3] = "";
    bool check = false;

    do {
        system("cls || clear");
        titulo_ventas();

        _colSET(cLIGHT_YELLOW);
        cout << endl;
        cout << "   1. Registrar ventas\n";
        cout << "   2. Mostrar ventas\n";
        cout << "   3. Buscar venta\n";
        cout << "   4. Modificar venta\n";
        cout << "   5. Eliminar venta\n";
        _colSET(cCYAN);
        cout << "\n   6. Regresar a menú de finanzas\n";
        cout << "   7. Regresar a menú principal\n";
        _colSET(cTEAL);
        cout << "\n   => Ingrese su opción: ";
        cin >> option;
        _colRESET();

        if (cin.fail()) {
            error_opcion();
            continue;
        }
        
        switch (option) {
            case 1:
                check = registrar_Ventas();

                if (!check) {
                    _colSET(cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo abrir, leer y/o escribir a uno o más los siguientes archivos: 'registro_Ventas.txt', 'registro_Pendientes.txt', 'registro_Clientes.txt', 'precio_galon.txt'...";
                } else {
                    _colSET(cGREEN);
                    cout << "\n   ***********************************************************************";
                    cout << "\n                           Venta(s) registrada(s)...";
                }

                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(2250));
                break;
            case 2:
                check = mostrar_Ventas();
                if (!check) {
                    _colSET(cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_Ventas.txt'...";
                    _colRESET();
                    this_thread::sleep_for(chrono::milliseconds(2250));
                }
                
                break;
            case 3:
                system("cls || clear");
                cout << endl;
                pedir_Cstring("ID de la venta a buscar", input_id, ID);
                check = leer_Archivos("registro_Ventas.txt");
                if (check) indice = buscar_Venta(input_id);
                else indice = -2;

                _colSET(cTEAL);
                cout << "\n   Buscando venta...";
                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(800));

                if (indice == -1) {
                    _colSET(cRED);
                    cout << "\n   ERROR: el ID '" << input_id << "' no se encontró en el registro...";
                    this_thread::sleep_for(chrono::milliseconds(2250));
                } else if (indice == -2) {
                    _colSET(cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_Ventas.txt'...";
                    this_thread::sleep_for(chrono::milliseconds(2250));
                } else if (indice >= 0) {
                    strcpy(pagada, (registro_Ventas[indice].pagada ? "Sí" : "No")); //convertir el bool a un string usando una operacion ternaria para que se imprima bien
                    _colSET(cGREEN);
                    cout << "\n   Venta encontrada!";
                    this_thread::sleep_for(chrono::milliseconds(800));

                    _colSET(cCYAN);
                    cout << endl << "\n                                  Venta #" << indice+1 << ":" << endl;
                    cout << "   ***********************************************************************\n";
                    _colSET(cLIGHT_YELLOW);
                    cout << "   ID: " << registro_Ventas[indice].id << "\n";
                    cout << "   Fecha: " << registro_Ventas[indice].fecha.dia << " de " << registro_Ventas[indice].fecha.mes << ", " << registro_Ventas[indice].fecha.year << "\n";
                    cout << "   Nombre del cliente: " << registro_Ventas[indice].nombre_cliente << "\n";
                    cout << "   Cantidad de leche: " << registro_Ventas[indice].cantidad_leche << " galones\n";
                    cout << "   Monto: C$" << registro_Ventas[indice].monto << "\n";
                    cout << "   ¿Está pagada? "; _colSET(cTEAL); cout << pagada << endl;
                    _colSET(cCYAN);
                    cout << endl << "   ***********************************************************************\n";
                    cout << "   Presione 'Enter' para continuar...";
                    cin.get();
                }

                _colRESET();
                break;
            case 4:
                check = editar_Venta();
                if (!check) {
                    _colSET(cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo abrir, leer y/o escribir a uno o más de los siguientes archivos: 'registro_Ventas.txt', 'registro_Pendientes.txt'...";
                    _colRESET();
                    this_thread::sleep_for(chrono::milliseconds(2250));
                }
                
                break;
            case 5:
                system("cls || clear");
                cout << endl;
                pedir_Cstring("ID de la venta a eliminar", input_id, ID);
                indice = eliminar_Venta(input_id);

                _colSET(cTEAL);
                cout << "\n   Buscando venta...";
                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(800));

                if (indice == -1) {
                    _colSET(cRED);
                    cout << "\n   ERROR: el ID '" << input_id << "' no se encontró en el registro...";
                } else if (indice == -2) {
                    _colSET(cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo abrir, leer y/o escribir a uno o más los siguientes archivos: 'registro_Ventas.txt', 'registro_Pendientes.txt', 'precio_galon.txt...";
                } else if (indice >= 0) {
                    _colSET(cGREEN);
                    cout << "\n   Venta eliminada!";
                }

                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(1500));
                break;
            case 6:
                _colSET(cCYAN);
                cout << "      Regresando a menú de finanzas...";
                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));
                break;
            case 7:
                _colSET(cCYAN);
                cout << "      Regresando a menú principal...";
                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));
                break;
            default:
                _colSET(cRED);
                cout << "      Opción inválida...";
                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));
                break;
        }
    } while ((option != 6) && (option != 7)); //mientras no se quiera regresar a otro menu, permanecer en el do while

    _colRESET();
    return option; //retornar la opcion del menu al que se quiere regresar
}

int pendientes() {
    int option = 0, indice = 0; //estas se usan igual que en los otros menus
    char input_id[ID] = "";
    bool check = false;

    do {
        system("cls || clear");
        titulo_pendientes();

        _colSET(cLIGHT_YELLOW);
        cout << endl;
        cout << "   1. Mostrar pagos pendientes\n";
        cout << "   2. Buscar pago pendiente\n";
        cout << "   3. Modificar pago pendiente\n";
        cout << "   4. Eliminar pago pendiente\n";
        _colSET(cCYAN);
        cout << "\n   5. Regresar a menú de finanzas\n";
        cout << "   6. Regresar a menú principal\n";
        _colSET(cTEAL);
        cout << "\n   => Ingrese su opción: ";
        cin >> option;
        _colRESET();

        if (cin.fail()) {
            error_opcion();
            continue;
        }

        switch (option) {
            case 1:
                check = mostrar_Pendientes();
                if (!check) {
                    _colSET(cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_Pendientes.txt'...";
                    _colRESET();
                    this_thread::sleep_for(chrono::milliseconds(2250));
                }
                
                break;
            case 2:
                system("cls || clear");
                cout << endl;
                pedir_Cstring("ID del pago pendiente a buscar", input_id, ID);
                check = leer_Archivos("registro_Pendientes.txt");
                if (check) indice = buscar_Pendiente(input_id);
                else indice = -2;

                _colSET(cTEAL);
                cout << "\n   Buscando pago pendiente...";
                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(800));

                if (indice == -1) {
                    _colSET(cRED);
                    cout << "\n   ERROR: el ID '" << input_id << "' no se encontró en el registro...";
                    this_thread::sleep_for(chrono::milliseconds(2250));
                } else if (indice == -2) {
                    _colSET(cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_Pendientes.txt'...";
                    this_thread::sleep_for(chrono::milliseconds(2250));
                } else if (indice >= 0) {
                    _colSET(cGREEN);
                    cout << "\n   Pago pendiente encontrado!";
                    this_thread::sleep_for(chrono::milliseconds(800));

                    _colSET(cCYAN);
                    cout << endl << "\n                                  Pago pendiente #" << indice+1 << ":" << endl;
                    cout << "   ***********************************************************************\n";
                    _colSET(cLIGHT_YELLOW);
                    cout << "   ID de la venta: " << registro_Pendientes[indice].id_venta << "\n";
                    cout << "   Fecha: " << registro_Pendientes[indice].fecha.dia << " de " << registro_Pendientes[indice].fecha.mes << ", " << registro_Pendientes[indice].fecha.year << "\n";
                    cout << "   Nombre del cliente: " << registro_Pendientes[indice].nombre_cliente << endl;
                    cout << "   Monto: C$" << registro_Pendientes[indice].monto << "\n";
                    _colSET(cCYAN);
                    cout << endl << "   ***********************************************************************\n";
                    cout << "   Presione 'Enter' para continuar...";
                    cin.get();
                }

                _colRESET();
                break;
            case 3:
                check = editar_Pendiente();
                if (!check) {
                    _colSET(cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer uno o más de los siguientes archivos: 'registro_Pendientes.txt', 'registro_Ventas.txt...";
                    _colRESET();
                    this_thread::sleep_for(chrono::milliseconds(2250));
                }
                
                break;
            case 4:
                system("cls || clear");
                cout << endl;
                pedir_Cstring("ID del pago pendiente a eliminar", input_id, ID);
                indice = eliminar_Pendiente(input_id);

                _colSET(cTEAL);
                cout << "\n   Buscando pago pendiente...";
                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(800));

                if (indice == -1) {
                    _colSET(cRED);
                    cout << "\n   ERROR: el ID '" << input_id << "' no se encontró en el registro...";
                } else if (indice == -2) {
                    _colSET(cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo abrir/leer uno o más de los siguientes archivos: 'registro_Pendientes.txt', 'registro_Ventas.txt', 'precio_galon.txt'...";
                } else if (indice >= 0) {
                    _colSET(cGREEN);
                    cout << "\n   Pago pendiente eliminado!";
                }

                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(1500));
                break;
            case 5:
                _colSET(cCYAN);
                cout << "      Regresando a menú de finanzas...";
                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));
                break;
            case 6:
                _colSET(cCYAN);
                cout << "      Regresando a menú principal...";
                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));
                break;
            default:
                _colSET(cRED);
                cout << "      Opción inválida...";
                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));
                break;
        }
    } while ((option != 5) && (option != 6));

    _colRESET();
    return option;
}

int costos_Fijos() {
    int option = 0, indice = 0; //lo mismo que el resto de los menus basicamente
    char input_id[ID] = "";
    bool check = false;

    do {
        system("cls || clear");
        titulo_costos_Fijos();

        _colSET(cLIGHT_YELLOW);
        cout << endl;
        cout << "   1. Registrar costos\n";
        cout << "   2. Mostrar costos\n";
        cout << "   3. Buscar costo\n";
        cout << "   4. Modificar costo\n";
        cout << "   5. Eliminar costo\n";
        _colSET(cCYAN);
        cout << "\n   6. Ir a menú de costos variables\n";
        cout << "   7. Regresar a menú de finanzas\n";
        cout << "   8. Regresar a menú principal\n";
        _colSET(cTEAL);
        cout << "\n   => Ingrese su opción: ";
        cin >> option;
        _colRESET();

        if (cin.fail()) {
            error_opcion();
            continue;
        }

        switch (option) {
            case 1:
                check = registrar_costos_Fijos();

                if (!check) {
                    _colSET(cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo abrir, leer y/o escribir al archivo 'registro_costos_Fijos.txt'...";
                } else {
                    _colSET(cGREEN);
                    cout << "\n   ***********************************************************************";
                    cout << "\n                          Costo(s) registrado(s)...";
                }

                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(2250));
                break;
            case 2:
                check = mostrar_costos_Fijos();
                if (!check) {
                    _colSET(cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_costos_Fijos.txt'...";
                    _colRESET();
                    this_thread::sleep_for(chrono::milliseconds(2250));
                }

                break;
            case 3:
                system("cls || clear");
                cout << endl;
                pedir_Cstring("ID del costo fijo a buscar", input_id, ID);
                check = leer_Archivos("registro_costos_Fijos.txt");
                if (check) indice = buscar_costo_Fijo(input_id);
                else indice = -2;

                _colSET(cTEAL);
                cout << "\n   Buscando costo fijo...";
                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(800));

                if (indice == -1) {
                    _colSET(cRED);
                    cout << "\n   ERROR: el ID '" << input_id << "' no se encontró en el registro...";
                    this_thread::sleep_for(chrono::milliseconds(2250));
                } else if (indice == -2) {
                    _colSET(cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_costos_Fijos.txt'...";
                    this_thread::sleep_for(chrono::milliseconds(2250));
                } else if (indice >= 0) {
                    _colSET(cGREEN);
                    cout << "\n   Costo fijo encontrado!";
                    this_thread::sleep_for(chrono::milliseconds(800));

                    _colSET(cCYAN);
                    cout << endl << "\n                                  Costo Fijo #" << indice+1 << ":" << endl;
                    cout << "   ***********************************************************************\n";
                    _colSET(cLIGHT_YELLOW);
                    cout << "   ID: " << registro_costos_Fijos[indice].id << "\n";
                    cout << "   Monto: C$" << registro_costos_Fijos[indice].monto << "\n";
                    cout << "   Descripción: " << registro_costos_Fijos[indice].descripcion << endl;
                    _colSET(cCYAN);
                    cout << endl << "   ***********************************************************************\n";
                    cout << "   Presione 'Enter' para continuar...";
                    cin.get();
                }

                _colRESET();
                break;
            case 4:
                check = editar_costo_Fijo();
                if (!check) {
                    _colSET(cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_costos_Fijos.txt'...";
                    _colRESET();
                    this_thread::sleep_for(chrono::milliseconds(2250));
                }

                break;
            case 5:
                system("cls || clear");
                cout << endl;
                pedir_Cstring("ID del costo fijo a eliminar", input_id, ID);
                indice = eliminar_costo_Fijo(input_id);

                _colSET(cTEAL);
                cout << "\n   Buscando costo fijo...";
                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(800));

                if (indice == -1) {
                    _colSET(cRED);
                    cout << "\n   ERROR: el ID '" << input_id << "' no se encontró en el registro...";
                } else if (indice == -2) {
                    _colSET(cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_costos_Fijos.txt'...";
                } else if (indice == 0) {
                    _colSET(cGREEN);
                    cout << "\n   Costo fijo eliminado!";
                }

                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(1500));
                break;

            case 6: break; //el mensaje y el sleep se llaman en finanzas()
            case 7: break; //^^
            case 8: break; //^^

            default:
                _colSET(cRED);
                cout << "      Opción inválida...";
                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));
                break;
        }
    } while ((option < 6) || (option > 8)); //mientras no se quiera salir del submenu, quedarse en el do while

    _colRESET();
    return option;
}

int costos_Variables() {
    int option = 0, indice = 0;
    char input_id[ID] = "";
    bool check = false;

    do {
        system("cls || clear");
        titulo_costos_Variables();

        _colSET(cLIGHT_YELLOW);
        cout << endl;
        cout << "   1. Registrar costos\n";
        cout << "   2. Mostrar costos\n";
        cout << "   3. Buscar costo\n";
        cout << "   4. Modificar costo\n";
        cout << "   5. Eliminar costo\n";
        _colSET(cCYAN);
        cout << "\n   6. Ir a menú de costos fijos\n";
        cout << "   7. Regresar a menú de finanzas\n";
        cout << "   8. Regresar a menú principal\n";
        _colSET(cTEAL);
        cout << "\n   => Ingrese su opción: ";
        cin >> option;
        _colRESET();

        if (cin.fail()) {
            error_opcion();
            continue;
        }

        switch (option) {
            case 1:
                check = registrar_costos_Variables();

                if (!check) {
                    _colSET(cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo abrir, leer y/o escribir al archivo 'registro_costos_Variables.txt'...";
                } else {
                    _colSET(cGREEN);
                    cout << "\n   ***********************************************************************";
                    cout << "\n                           Costo(s) registrado(s)...";
                }

                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(2250));
                break;
            case 2:
                check = mostrar_costos_Variables();
                if (!check) {
                    _colSET(cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_costos_Variables.txt'...";
                    _colRESET();
                    this_thread::sleep_for(chrono::milliseconds(2250));
                }
                
                break;
            case 3:
                system("cls || clear");
                cout << endl;
                pedir_Cstring("ID del costo variable a buscar", input_id, ID);
                check = leer_Archivos("registro_costos_Variables.txt");
                if (check) indice = buscar_costo_Variable(input_id);
                else indice = -2;

                _colSET(cTEAL);
                cout << "\n   Buscando costo variable...";
                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(800));

                if (indice == -1) {
                    _colSET(cRED);
                    cout << "\n   ERROR: el ID '" << input_id << "' no se encontró en el registro...";
                    this_thread::sleep_for(chrono::milliseconds(2250));
                } else if (indice == -2) {
                    _colSET(cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_costos_Variables.txt'...";
                    this_thread::sleep_for(chrono::milliseconds(2250));
                } else if (indice >= 0) {
                    _colSET(cGREEN);
                    cout << "\n   Costo variable encontrado!";
                    this_thread::sleep_for(chrono::milliseconds(800));

                    _colSET(cCYAN);
                    cout << endl << "\n                               Costo Variable #" << indice+1 << ":" << endl;
                    cout << "   ***********************************************************************\n";
                    _colSET(cLIGHT_YELLOW);
                    cout << "   ID: " << registro_costos_Variables[indice].id << "\n";
                    cout << "   Monto: C$" << registro_costos_Variables[indice].monto << "\n";
                    cout << "   Descripción: " << registro_costos_Variables[indice].descripcion << "\n";
                    cout << "   Mes: " << registro_costos_Variables[indice].mes << endl;
                    _colSET(cCYAN);
                    cout << endl << "   ***********************************************************************\n";
                    cout << "   Presione 'Enter' para continuar...";
                    cin.get();
                }

                _colRESET();
                break;
            case 4:
                check = editar_costo_Variable();
                if (!check) {
                    _colSET(cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_costos_Variables.txt'...";
                    _colRESET();
                    this_thread::sleep_for(chrono::milliseconds(2250));
                }
                
                break;
            case 5:
                system("cls || clear");
                cout << endl;
                pedir_Cstring("ID del costo variable a eliminar", input_id, ID);
                indice = eliminar_costo_Variable(input_id);

                _colSET(cTEAL);
                cout << "\n   Buscando costo variable...";
                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(800));

                if (indice == -1) {
                    _colSET(cRED);
                    cout << "\n   ERROR: el ID '" << input_id << "' no se encontró en el registro...";
                } else if (indice == -2) {
                    _colSET(cRED);
                    cout << "\n   ERROR DE ARCHIVO: no se pudo leer el archivo 'registro_costos_Variables.txt'...";
                } else if (indice == 0) {
                    _colSET(cGREEN);
                    cout << "\n   Costo variable eliminado!";
                }

                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(1500));
                break;

            case 6: break; //el mensaje y el sleep se llaman en finanzas()
            case 7: break; //^^
            case 8: break; //^^

            default:
                _colSET(cRED);
                cout << "      Opción inválida...";
                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(1000));
                break;
        }
    } while ((option < 6) || (option > 8));

    _colRESET();
    return option;
}

//***************************************************************************************************