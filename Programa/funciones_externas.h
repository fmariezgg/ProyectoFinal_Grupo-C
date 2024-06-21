#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <windows.h>
#include "titulos.h"
#include "variables.h"
using namespace std;

//hace exactamente lo que dice (se usa en registro_Ventas() para guardar la fecha automaticamente)
tm* obtener_fecha();

/*esta es una funcion generica que se va a usar para pedir todos los strings que se van a ocupar en el sistema.
-- dato es el nombre de lo que se va a pedir (como nombre, id, etc.)
-- input es un puntero al arreglo adonde se va a guardar el string (como los nombres de los arreglos
   funcionan como punteros para su primer elemento, solo se llama con el nombre del arreglo)
-- longitud es la longitud del string que se va a pedir. como la mayoria son de MAX_INPUT, ese es el valor por defecto*/
void pedir_Cstring(const char dato[MAX_INPUT], const char* input, int longitud = MAX_INPUT);

//estas dos que siguen son lo mismo pero para los otros datos que se van a pedir
int pedir_int(const char dato[MAX_INPUT]);
float pedir_float(const char dato[MAX_INPUT]);

//y esta es para pedir si el cliente ha pagado su compra o no
//(la tengo aqui pq no quiero tener la logica de validar el input en registrar_Ventas())
bool pedir_pagada();

//funciones para abrir/leer/escribir a archivos
bool leer_archivo(const char nombre_archivo[MAX_INPUT]);
bool escribir_archivo(const char nombre_archivo[MAX_INPUT]);

//***************************************************************************************************

tm* obtener_fecha() {
    time_t now = time(0);
    tm* time = localtime(&now);
    return time;
}

//***************************************************************************************************

void pedir_Cstring(const char dato[MAX_INPUT], char* input, int longitud = MAX_INPUT) {
    while (true) {
        cambiar_color(14);
        cout << "   Ingresar " << dato << ": ";
        if (cin.peek() == '\n') cin.ignore();
        cin.getline(input, longitud);

        if (cin.fail()) {
            cin.clear();
            while (cin.get() != '\n' && !cin.eof());
            cambiar_color(12);
            cout << "\n   ERROR: " << dato << " ingresado es demasiado largo...\n\n";
        } else break;
    }

    resetear_color();
}

int pedir_int(const char dato[MAX_INPUT]) {
    int num = 0;
    cambiar_color(14);
    cout << "   Ingresar " << dato << ": ";
    cin >> num;
    resetear_color();
    return num;
}

float pedir_float(const char dato[MAX_INPUT]) {
    float num = 0.00;
    cambiar_color(14);
    cout << "   Ingresar " << dato << ": ";
    cin >> num;
    resetear_color();
    return num;
}

bool pedir_pagada() {
    char input = '\0';

    while (true) {
        cambiar_color(14);
        cout << "   ¿Ha pagado el cliente? (s/n) ";
        cin >> input;

        if ((input == 's') || (input == 'S')) return true;
        else if ((input == 'n') || (input == 'N')) return false;
        else {
            cambiar_color(12);
            cout << "\n   ERROR: respuesta invalida...\n\n";
            continue;
        }
    }

    resetear_color();
}

//***************************************************************************************************

bool leer_archivo(const char nombre_archivo[MAX_INPUT]) {
    int i = 0; //contador de elementos
    fstream file;
    file.open(nombre_archivo, ios::in);

    if (!file) {
        file.open(nombre_archivo, ios::out);  //si el archivo no existe, crearlo (ios::out crea el archivo si no existe, ios::in solo tira error)
        if (!file) return false; //si no se pudo crear/abrir, salir
        file.close();
        file.open(nombre_archivo, ios::in); //cerrar el archivo (pq esta en ios::out), y volver a abrirlo en modo de leer
        if (!file) return false; //si todavia da error, ni modo, salir y retornar false

        cambiar_color(12);
        cout << "\n   " << nombre_archivo << " no encontrado...\n";
        cambiar_color(10);
        cout << "   Creando " << nombre_archivo << "..." << endl;
        resetear_color();
    }

    else {
        //leer precio
        if (strcmp(nombre_archivo, "precio_galon.txt") == 0) file >> precio_galon;
        
        //leer vacas
        else if (strcmp(nombre_archivo, "registro_Vacas.txt") == 0) {
            while (true) {
                file.getline(registro_Vacas[i].id, MAX_INPUT);
                file.getline(registro_Vacas[i].estado_salud, MAX_INPUT);
                file >> registro_Vacas[i].edad;
                file >> registro_Vacas[i].prod_diaria;

                if (file.fail()) break; //si no se pudo leer nada, salir
                if (file.peek() == '\n') file.ignore();; //quitar el \n del stream para que getline funcione bien
                i++;
            }
            
            num_vacas = i;
        }
        
        //leer clientes
        else if (strcmp(nombre_archivo, "registro_Clientes.txt") == 0) {
            while (true) {
                file.getline(registro_Clientes[i].nombre, MAX_INPUT);
                file.getline(registro_Clientes[i].direccion, MAX_INPUT);
                file.getline(registro_Clientes[i].contacto, MAX_INPUT);

                if (file.fail()) break;
                file.ignore();
                i++;
            }
            
            num_clientes = i;
        }

        //leer ventas
        else if (strcmp(nombre_archivo, "registro_Ventas.txt") == 0) {
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
                if (file.peek() == '\n') file.ignore();;
                i++;
            }

            num_ventas = i;
        }

        //leer pagos pendientes
        else if (strcmp(nombre_archivo, "registro_Pendientes.txt") == 0) {
            while (true) {
                file.getline(registro_Pendientes[i].id_venta, ID);
                file.getline(registro_Pendientes[i].nombre_cliente, MAX_INPUT);
                file >> registro_Pendientes[i].monto;

                if (file.fail()) break;
                if (file.peek() == '\n') file.ignore();;
                i++;
            }

            num_pendientes = i;
        }

        //leer costos fijos
        else if (strcmp(nombre_archivo, "registro_costos_Fijos.txt") == 0) {
            while (true) {
                file >> registro_costos_Fijos[i].monto;
                if (file.peek() == '\n') file.ignore();;
                file.getline(registro_costos_Fijos[i].descripcion, MAX_INPUT);

                if (file.fail()) break;
                if (file.peek() == '\n') file.ignore();;
                i++;
            }
            
            num_costos_Fijos = i;
        }
        
        //leer costos variables
        else if (strcmp(nombre_archivo, "registro_costos_Variables.txt") == 0) {
            while (true) {
                file >> registro_costos_Variables[i].monto;
                if (file.peek() == '\n') file.ignore();;
                file.getline(registro_costos_Variables[i].descripcion, MAX_INPUT);
                
                if (file.fail()) break;
                if (file.peek() == '\n') file.ignore();;
                i++;
            }
            
            num_costos_Variables = i;
        }
    }

    file.close();
    return true;
}

bool escribir_archivo(const char nombre_archivo[MAX_INPUT]) {
    int x = 0; //contador de elementos
    fstream file;
    file.open(nombre_archivo, ios::trunc | ios::out);

    if (!file) return false;

    else {
        //escribir precio
        if (strcmp(nombre_archivo, "precio_galon.txt") == 0) file << precio_galon;

        //escribir vacas
        if (strcmp(nombre_archivo, "registro_Vacas.txt") == 0) {
            for (int i = 0; i < num_vacas; i++) {
                file << registro_Vacas[i].id << "\n";
                file << registro_Vacas[i].estado_salud << "\n";
                file << registro_Vacas[i].edad << "\n";
                file << registro_Vacas[i].prod_diaria << "\n";
                x++;
            }

            num_vacas = x;
        }
        
        //escribir clientes
        else if (strcmp(nombre_archivo, "registro_Clientes.txt") == 0) {
            for (int i = 0; i < num_clientes; i++) {
                file << registro_Clientes[i].nombre << "\n";
                file << registro_Clientes[i].direccion << "\n";
                file << registro_Clientes[i].contacto << "\n";
                x++;
            }

            num_clientes = x;
        }

        //escribir ventas
        else if (strcmp(nombre_archivo, "registro_Ventas.txt") == 0) {
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

        //escribir pagos pendientes
        else if (strcmp(nombre_archivo, "registro_Pendientes.txt") == 0) {
            for (int i = 0; i < num_pendientes; i++) {
                file << registro_Pendientes[i].id_venta << "\n";
                file << registro_Pendientes[i].nombre_cliente << "\n";
                file << registro_Pendientes[i].monto << "\n";
                x++;
            }

            num_pendientes = x;
        }

        //escribir costos fijos
        else if (strcmp(nombre_archivo, "registro_costos_Fijos.txt") == 0) {
            for (int i = 0; i < num_costos_Fijos; i++) {
                file << registro_costos_Fijos[i].monto << "\n";
                file << registro_costos_Fijos[i].descripcion << "\n";
                x++;
            }

            num_costos_Fijos = x;
        }
        
        //escribir costos variables
        else if (strcmp(nombre_archivo, "registro_costos_Variables.txt") == 0) {
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