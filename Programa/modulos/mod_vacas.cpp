#include "../headers/funciones_externas.h"
using namespace std;
using namespace LLC;

//implementaciones de todas las funciones del modulo de gestion de vacas:
//***************************************************************************************************

//las funciones de buscar no leen los archivos ellas mismas, pq si no, a la hora de validar los id's,
//los datos del arreglo con el que se estaba trabajando se reemplazan con lo que esta en el archivo (que en ese punto esta atrasado pq no se han escrito los cambios)
//entonces cuando estas se llaman en los menus, se tienen que leer los archivos antes

int buscar_Vaca(const char id[ID]) {  
    for (int i = 0; i < num_vacas; i++) {
        if (strcmp(registro_Vacas[i].id, id) == 0) return i;
    }
    
    return -1; //si no se ha retornado, significa que no se encontro el id
}

//***************************************************************************************************

bool registrar_Vacas() {
    system("cls || clear");
    bool leer = false, escribir = false;
    char tempID[ID] = "", input[3] = "";

    leer = leer_Archivos("registro_Vacas.txt");
    if (!leer) return false;
        
    do {
        _colSET(cCYAN);
        cout << endl << "                                  Vaca #" << num_vacas+1 << ":" << endl;
        cout << "   ***********************************************************************\n";
        _colRESET();
        
        while (true) { //checkear que el ID no este registrado
            pedir_Cstring("ID", tempID, ID);

            if (buscar_Vaca(tempID) >= 0) {
                _colSET(cRED);
                cout << "   ERROR: ID ya registrado...";
                _colRESET();
                this_thread::sleep_for(chrono::milliseconds(1500));
                cout << endl;
                continue; //si se encontro, volver a pedirlo
            } else if (buscar_Vaca(tempID) == -1) {
                strcpy(registro_Vacas[num_vacas].id, tempID); //si no, registrarlo
                break;
            } else if (buscar_Vaca(tempID) == -2) return false;
        }

        registro_Vacas[num_vacas].edad = pedir_int("edad (en años)");
        registro_Vacas[num_vacas].prod_diaria = pedir_int("producción diaria (en galones)");
        pedir_Cstring("estado de salud", registro_Vacas[num_vacas].estado_salud);
        
        num_vacas++;
        continuar("\n   ¿Desea registrar más vacas? (si/no) ", input);

    } while (((strcmp(input, "s") == 0) || (strcmp(input, "S") == 0) || (strcmp(input, "si") == 0) || (strcmp(input, "Si") == 0) || (strcmp(input, "sI") == 0) || (strcmp(input, "SI") == 0)));

    escribir = escribir_Archivos("registro_Vacas.txt");
    if (!escribir) return false;

    cout << "   ";
    this_thread::sleep_for(chrono::milliseconds(500));
    _colRESET();
    return true; //si no se ha retornado, significa que las operaciones de leer y escribir funcionaron bien y se guardaron los datos
}

//***************************************************************************************************

bool mostrar_Vacas() {
    system("cls || clear");
    bool leer = leer_Archivos("registro_Vacas.txt");
    if (!leer) return false;

    if (checkear_Vacio(num_vacas)) return true; //checkea si esta vacio el registro

    _colSET(cGREEN);
    cout << "\n   Mostrando vacas registradas...";
    this_thread::sleep_for(chrono::milliseconds(800));

    cout << endl;
    for (int i = 0; i < num_vacas; i++) {
        _colSET(cCYAN);
        cout << endl << "                                  Vaca #" << i+1 << ":" << endl;
        cout << "   ***********************************************************************\n";
        _colSET(cLIGHT_YELLOW);
        cout << "   ID: " << registro_Vacas[i].id << "\n";
        cout << "   Edad: " << registro_Vacas[i].edad << " año(s)\n";
        cout << "   Producción diaria: " << registro_Vacas[i].prod_diaria << " galón(es)\n";
        cout << "   Estado de salud: " << registro_Vacas[i].estado_salud << endl;
        cout << "   "; //todos los espacios y endl's asi raros son por estetica
        this_thread::sleep_for(chrono::milliseconds(800));
    }

    _colSET(cCYAN);
    cout << endl << "   ***********************************************************************\n";
    cout << "   Presione 'Enter' para continuar...";

    //para no usar system("pause"), primero se limpia el ultimo caracter en el buffer y se espera a que el usuario presione una tecla
    cin.ignore(); //este ignore es para el \n que quedo en el stream cuando el usuario ingreso su opcion en el menu
    cin.get();
    _colRESET();
    return true;
}

//***************************************************************************************************

bool editar_Vaca() {
    system("cls || clear");
    bool leer = false, escribir = false;
    int indice = 0, info = 0;
    char id[ID] = "";

    leer = leer_Archivos("registro_Vacas.txt");
    if (!leer) return false;
    if (checkear_Vacio(num_vacas)) return true;

    cout << endl;
    pedir_Cstring("ID de la vaca a editar", id, ID);
    indice = buscar_Vaca(id);

    _colSET(cTEAL);
    cout << "\n   Buscando vaca...";
    this_thread::sleep_for(chrono::milliseconds(800));
    _colRESET();

    if (indice == -1) { //por si no se encontro el id
        _colSET(cRED);
        cout << "\n   ERROR: ID ingresado no esta registrado...";
        this_thread::sleep_for(chrono::milliseconds(2250));
        _colRESET();
        return true;
    } else if (indice == -2) return false;

    else if (indice >= 0) {
        _colSET(cGREEN);
        cout << "\n   Vaca encontrada!";
        this_thread::sleep_for(chrono::milliseconds(500));
        _colSET(cCYAN);
        cout << endl << "\n                                  Vaca #" << indice+1 << ":" << endl;
        cout << "   ***********************************************************************";
        do {
            _colSET(cLIGHT_YELLOW);
            cout << "\n\n   ¿Qué información quiere editar?" << endl;
            cout << "   1. Edad\n   2. Producción diaria\n   3. Estado de salud\n";
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
                    registro_Vacas[indice].edad = pedir_int("edad (en años)");
                    break;
                case 2:
                    registro_Vacas[indice].prod_diaria = pedir_int("producción diaria (en galones)");
                    break;
                case 3:
                    pedir_Cstring("estado de salud", registro_Vacas[indice].estado_salud);
                    break;
                default:
                    _colSET(cRED);
                    cout << "   Opción inválida...";
                    this_thread::sleep_for(chrono::milliseconds(1000));
                    _colRESET();
                    break;
            }
        } while (info < 1 || info > 3); //repetir mientras que la opcion que se haya ingresado no sea valida

        cout << "   ";
        this_thread::sleep_for(chrono::milliseconds(500));
        _colSET(cGREEN);
        escribir = escribir_Archivos("registro_Vacas.txt");
        if (escribir) {
            _colSET(cGREEN);
            cout << "\n   ***********************************************************************";
            cout << "\n                              Vaca editada...";
        } else return false;
        
        this_thread::sleep_for(chrono::milliseconds(2250));
        _colRESET();
    }

    return true;
}

//***************************************************************************************************

int eliminar_Vaca(const char id[ID]) {
    int indice = 0;
    bool leer = false, escribir = false;

    leer = leer_Archivos("registro_Vacas.txt");
    if (!leer) return -2;
    if (checkear_Vacio(num_vacas)) return 1;

    indice = buscar_Vaca(id);
    if (indice < 0) return indice; //si no se encontro/ocurrio un error, retornar el error para mostrar el mensaje correspondiente en el menu

    //como estas funciones de eliminar se ocupan adentro de otras funciones, sale mejor retornar los errores y lidiar con ellos en el menu,
    //para que no salgan mensajes raros mientras otra funcion se esta ejecutando

    for (int i = indice; i < num_vacas-1; i++) {
        registro_Vacas[i] = registro_Vacas[i+1];
    } num_vacas--;

    escribir = escribir_Archivos("registro_Vacas.txt");
    if (escribir) return 0;
    else return -2;
}

//***************************************************************************************************