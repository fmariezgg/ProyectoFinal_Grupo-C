#include <iostream>
#include <fstream>
#include <cstring>
#include "variables.h"
using namespace std;

/*esta es una funcion generica que se va a usar para pedir todos los strings que se van a ocupar en el sistema.
-- dato es el nombre de lo que se va a pedir (como nombre, id, etc.)
-- input es un puntero al arreglo adonde se va a guardar el string
-- largo es la longitud del string que se va a pedir. como la mayoria son de MAX_INPUT, ese es el valor por defecto*/
void pedir_Cstring(const char dato[MAX_INPUT], const char* input, int largo = MAX_INPUT);

//estas dos que siguen son lo mismo pero para los otros datos que se van a pedir
int pedir_int(const char dato[MAX_INPUT]);
float pedir_float(const char dato[MAX_INPUT]);

//y esta es para pedir si el cliente ha pagado (la tengo aqui pq no quiero tener la logica de validar lo que el usuario ingresa en registrar_Venta())
bool pedir_pagada();

//funciones para leer/escribir datos (archivo es el nombre del archivo que se va a abrir):
bool leer_archivo(const char archivo[MAX_INPUT]);
bool escribir_archivo(const char archivo[MAX_INPUT]);

//***************************************************************************************************

void pedir_Cstring(const char dato[MAX_INPUT], char* input, int largo = MAX_INPUT) {
    while (true) {
        cout << "Ingresar " << dato << ": ";
        cin.getline(input, largo);

        if (cin.fail()) {
            cin.clear();
            while (cin.get() != '\n' && !cin.eof());
            cout << "\nERROR: " << dato << " ingresado es demasiado largo...\n\n";
        } else break;
    }
}

int pedir_int(const char dato[MAX_INPUT]) {
    int num = 0;
    cout << "Ingresar " << dato << ": ";
    cin >> num;
    return num;
}

float pedir_float(const char dato[MAX_INPUT]) {
    float num = 0.00;
    cout << "Ingresar " << dato << ": ";
    cin >> num;
    return num;
}

bool pedir_pagada() {
    bool check = false;
    char input = '\0';

    while (true) {
        cout << "¿Ha pagado el cliente? (s/n) ";
        cin >> input;

        if ((input == 's') || (input == 'S')) {
            check = true;
            break;
        } else if ((input == 'n') || (input == 'N')) {
            check = false;
            break;
        } else {
            cout << "\nERROR: respuesta invalida...\n\n";
            continue;
        }
    }

    return check;
}

//***************************************************************************************************

bool leer_archivo(const char archivo[MAX_INPUT]) {
    int i = 0; //contador de elementos
    fstream file;
    file.open(archivo, ios::in);

    if (!file) {
        file.open(archivo, ios::out);  //si el archivo no existe, crearlo (ios::out crea el archivo si no existe, ios::in solo tira error)
        if (!file) return false; //si no se pudo crear/abrir, salir
        file.close();
        file.open(archivo, ios::in); //cerrar el archivo (pq esta en ios::out), y volver a abrirlo en modo de leer
        if (!file) return false; //si todavia da error, ni modo, salir y retornar false
    }

    else {
        //PRECIO
        if (strcmp(archivo, "precio_galon.txt") == 0) file >> precio_galon;
        
        //VACAS
        if (strcmp(archivo, "registro_Vacas.txt") == 0) {
            while (true) {
                file.getline(registro_Vacas[i].id, MAX_INPUT);
                file.getline(registro_Vacas[i].estado_salud, MAX_INPUT);
                file >> registro_Vacas[i].edad;
                file >> registro_Vacas[i].prod_diaria;

                if (file.fail()) break; //si no se pudo leer nada, salir
                file.ignore(); //quitar el \n del stream para que getline funcione bien
                i++;
            }
            
            num_vacas = i;
        }
        
        //CLIENTES
        else if (strcmp(archivo, "registro_Clientes.txt") == 0) {
            int j = 0; //contador de elementos de pagos_pendientes
            while (true) {
                file.getline(registro_Clientes[i].nombre, MAX_INPUT);
                file.getline(registro_Clientes[i].direccion, MAX_INPUT);
                file.getline(registro_Clientes[i].contacto, MAX_INPUT);

                if (file.fail()) break;
                file.ignore();
                i++;
            }
            
            num_pagos = j;
            num_clientes = i;
        }

        //VENTAS
        else if (strcmp(archivo, "registro_Ventas.txt") == 0) {
            while (true) {
                file.getline(registro_Ventas[i].id, ID);
                file.getline(registro_Ventas[i].nombre_cliente, MAX_INPUT);
                /*file.getline(registro_Ventas[i].fecha.mes, ID);
                file >> registro_Ventas[i].fecha.dia;
                file >> registro_Ventas[i].fecha.year;*/
                file >> registro_Ventas[i].cantidad_leche;
                file >> registro_Ventas[i].monto;
                file >> registro_Ventas[i].pagada;

                if (file.fail()) break;
                file.ignore();
                i++;
            }

            num_ventas = i;
        }
        
        //COSTOS FIJOS
        else if (strcmp(archivo, "registro_costos_Fijos.txt") == 0) {
            while (true) {
                file >> registro_costos_Fijos[i].monto;
                file.ignore();
                file.getline(registro_costos_Fijos[i].descripcion, MAX_INPUT);

                if (file.fail()) break;
                file.ignore();
                i++;
            }
            
            num_costos_Fijos = i;
        }
        
        //COSTOS VARIABLES
        else if (strcmp(archivo, "registro_costos_Variables.txt") == 0) {
            while (true) {
                file >> registro_costos_Variables[i].monto;
                file.ignore();
                file.getline(registro_costos_Variables[i].descripcion, MAX_INPUT);
                
                if (file.fail()) break;
                file.ignore();
                i++;
            }
            
            num_costos_Variables = i;
        }
    }

    file.close();
    return true;
}

bool escribir_archivo(const char archivo[MAX_INPUT]) {
    int x = 0;
    fstream file;
    file.open(archivo, ios::trunc | ios::out);

    if (!file) return false;

    else {
        //PRECIO
        if (strcmp(archivo, "precio_galon.txt") == 0) file << precio_galon;

        //VACAS
        if (strcmp(archivo, "registro_Vacas.txt") == 0) {
            for (int i = 0; i < num_vacas; i++) {
                file << registro_Vacas[i].id << "\n";
                file << registro_Vacas[i].estado_salud << "\n";
                file << registro_Vacas[i].edad << "\n";
                file << registro_Vacas[i].prod_diaria << "\n";
                x++;
            }

            num_vacas = x;
        }
        
        //CLIENTES
        else if (strcmp(archivo, "registro_Clientes.txt") == 0) {
            for (int i = 0; i < num_clientes; i++) {
                file << registro_Clientes[i].nombre << "\n";
                file << registro_Clientes[i].direccion << "\n";
                file << registro_Clientes[i].contacto << "\n";
                x++;
            }

            num_clientes = x;
        }

        //VENTAS
        else if (strcmp(archivo, "registro_Ventas.txt") == 0) {
            for (int i = 0; i < num_ventas; i++) {
                file << registro_Ventas[i].id << "\n";
                file << registro_Ventas[i].nombre_cliente << "\n";
                /*file << registro_Ventas[i].fecha.mes << "\n";
                file << registro_Ventas[i].fecha.dia << "\n";
                file << registro_Ventas[i].fecha.year << "\n";*/
                file << registro_Ventas[i].cantidad_leche << "\n";
                file << registro_Ventas[i].monto << "\n";
                file << registro_Ventas[i].pagada << "\n";
                x++;
            }

            num_ventas = x;
        }
        
        //COSTOS FIJOS
        else if (strcmp(archivo, "registro_costos_Fijos.txt") == 0) {
            for (int i = 0; i < num_costos_Fijos; i++) {
                file << registro_costos_Fijos[i].monto << "\n";
                file << registro_costos_Fijos[i].descripcion << "\n";
                x++;
            }

            num_costos_Fijos = x;
        }
        
        //COSTOS VARIABLES
        else if (strcmp(archivo, "registro_costos_Variables.txt") == 0) {
            for (int i = 0; i < num_costos_Variables; i++) {
                file << registro_costos_Variables[i].monto << "\n";
                file << registro_costos_Variables[i].descripcion << "\n";
                x++;
            }
            num_costos_Variables = x;
        }
    }


    file.close();
    return true;
}