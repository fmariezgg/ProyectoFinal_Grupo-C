#ifndef FUNCIONES_EXTERNAS_H  //como estoy incluyendo este .h en varios archivos, a la hora de incluir esos otros archivos en prototipos.h
#define FUNCIONES_EXTERNAS_H //van a haber redefiniciones de las funciones de este archivo, y esto de ifndef evita que pase eso y solo se incluye una vez

#include <iostream>
#include <fstream>
#include <cstring> //funciones de C-strings
#include <ctime> //para obtener la fecha y hora actuales
#include <chrono> //esto y <thread> se ocupan para hacer lo mismo que Sleep() sin tener que usar windows.h
#include <thread>
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

//esta es para pedir si el cliente ha pagado su compra o no
//la tengo aqui pq no quiero tener la logica de validar el input en registrar_Ventas()
bool pedir_pagada();

//en varias funciones se checkea si el registro esta vacio antes de hacer algo,
//entonces para no estar repitiendo el mismo codigo, lo puse en su propia funcion
bool checkear_Vacio(int num_registro);

//funciones para abrir/leer/escribir a archivos
bool leer_Archivos(const char nombre_archivo[MAX_INPUT]);
bool escribir_Archivos(const char nombre_archivo[MAX_INPUT]);

//***************************************************************************************************

tm* obtener_fecha() {
    time_t now = time(0); //retorna la cantidad de segundos desde 1970
    tm* time = localtime(&now); //convierte la cantidad de segundos a una fecha y hora legible
    return time;
}

//***************************************************************************************************

void pedir_Cstring(const char dato[MAX_INPUT], char* input, int longitud = MAX_INPUT) {
    while (true) {
        LLC::_colSET(LLC::cLIGHT_YELLOW);
        cout << "   Ingresar " << dato << ": ";
        if (cin.peek() == '\n') cin.ignore();
        cin.getline(input, longitud);

        if (cin.fail()) {
            cin.clear();
            while ((cin.get() != '\n') && (!cin.eof())); //limpia el resto de los caracteres que quedaron en el stream
            LLC::_colSET(LLC::cRED);
            cout << "\n   ERROR: " << dato << " ingresado es demasiado largo...\n\n";
        } else break;
    }

    LLC::_colRESET();
}

int pedir_int(const char dato[MAX_INPUT]) {
    int num = 0;
    LLC::_colSET(LLC::cLIGHT_YELLOW);
    cout << "   Ingresar " << dato << ": ";
    cin >> num;
    LLC::_colRESET();
    return num;
}

float pedir_float(const char dato[MAX_INPUT]) {
    float num = 0.00;
    LLC::_colSET(LLC::cLIGHT_YELLOW);
    cout << "   Ingresar " << dato << ": ";
    cin >> num;
    LLC::_colRESET();
    return num;
}

//***************************************************************************************************

bool pedir_pagada() {
    char input[3] = "";

    while (true) {
        LLC::_colSET(LLC::cLIGHT_YELLOW);
        cout << "   ¿Ha pagado el cliente? (si/no) ";
        cin >> input;

        if ((strcmp(input, "s") == 0) || (strcmp(input, "S") == 0) || (strcmp(input, "si") == 0) || (strcmp(input, "Si") == 0) || (strcmp(input, "sI") == 0) || (strcmp(input, "SI") == 0)) {
            return true;
        } else if ((strcmp(input, "n") == 0) || (strcmp(input, "N") == 0) || (strcmp(input, "no") == 0) || (strcmp(input, "No") == 0) || (strcmp(input, "nO") == 0) || (strcmp(input, "NO") == 0)) {
            return false;
        } else {
            LLC::_colSET(LLC::cRED);
            cout << "\n   ERROR: respuesta inválida...\n\n";
            continue;
        }
    }

    LLC::_colRESET();
}

bool checkear_Vacio(int nun_registro) {
    if (nun_registro == 0) {
        LLC::_colSET(LLC::cRED);
        cout << "\n   El registro esta vacío...";
        this_thread::sleep_for(chrono::milliseconds(2250));
        LLC::_colRESET();
        return true;
    }

    return false;
}

//***************************************************************************************************

bool leer_Archivos(const char nombre_archivo[MAX_INPUT]) {
    int i = 0; //contador de elementos
    fstream file;
    file.open(nombre_archivo, ios::in);

    if (!file) {
        file.open(nombre_archivo, ios::out);  //si el archivo no existe, crearlo (ios::out crea el archivo si no existe, ios::in solo tira error)
        if (!file) return false; //si no se pudo crear/abrir, salir
        file.close();
        file.open(nombre_archivo, ios::in); //cerrar el archivo (pq esta en ios::out), y volver a abrirlo en modo de leer
        if (!file) return false; //si todavia da error, ni modo, salir y retornar false

        LLC::_colSET(LLC::cRED);
        cout << "\n   " << nombre_archivo << " no encontrado...";
        this_thread::sleep_for(chrono::milliseconds(500)); LLC::_colSET(LLC::cGREEN);
        cout << "\n   Creando " << nombre_archivo << "...";
        this_thread::sleep_for(chrono::milliseconds(1000)); LLC::_colRESET();
        cout << endl;
    }

    else {
        //leer precio
        if (strcmp(nombre_archivo, "precio_galon.txt") == 0) file >> precio_galon;
        
        //leer vacas
        else if (strcmp(nombre_archivo, "registro_Vacas.txt") == 0) {
            while (true) {
                file.getline(registro_Vacas[i].id, ID);
                file >> registro_Vacas[i].edad;
                file >> registro_Vacas[i].prod_diaria;
                if (file.peek() == '\n') file.ignore(); //si el proximo caracter es un \n, quitarlo del stream para que getline funcione bien
                file.getline(registro_Vacas[i].estado_salud, MAX_INPUT);

                if (file.fail()) break; //si no se pudo leer nada, salir
                if (file.peek() == '\n') file.ignore(); //quitar el \n otra vez
                i++;
            }
            
            num_vacas = i;
        }
        
        //leer clientes
        else if (strcmp(nombre_archivo, "registro_Clientes.txt") == 0) {
            while (true) {
                file.getline(registro_Clientes[i].id, ID);
                if (file.peek() == '\n') file.ignore();
                file.getline(registro_Clientes[i].nombre, MAX_INPUT);
                if (file.peek() == '\n') file.ignore();
                file.getline(registro_Clientes[i].direccion, MAX_INPUT);
                if (file.peek() == '\n') file.ignore();
                file.getline(registro_Clientes[i].contacto, MAX_INPUT);

                if (file.fail()) break;                
                if (file.peek() == '\n') file.ignore();
                i++;
            }
            
            num_clientes = i;
        }

        //leer ventas
        else if (strcmp(nombre_archivo, "registro_Ventas.txt") == 0) {
            while (true) {
                file.getline(registro_Ventas[i].id, ID);
                if (file.peek() == '\n') file.ignore();
                file.getline(registro_Ventas[i].nombre_cliente, MAX_INPUT);
                file >> registro_Ventas[i].fecha.dia;
                if (file.peek() == '\n') file.ignore();
                file.getline(registro_Ventas[i].fecha.mes, ID);
                file >> registro_Ventas[i].fecha.year;
                file >> registro_Ventas[i].cantidad_leche;
                file >> registro_Ventas[i].monto;
                file >> registro_Ventas[i].pagada;

                if (file.fail()) break;
                if (file.peek() == '\n') file.ignore();
                i++;
            }

            num_ventas = i;
        }

        //leer pagos pendientes
        else if (strcmp(nombre_archivo, "registro_Pendientes.txt") == 0) {
            while (true) {
                file.getline(registro_Pendientes[i].id_venta, ID);
                file >> registro_Pendientes[i].fecha.dia;
                if (file.peek() == '\n') file.ignore();
                file.getline(registro_Pendientes[i].fecha.mes, ID);
                file >> registro_Pendientes[i].fecha.year;
                if (file.peek() == '\n') file.ignore();
                file.getline(registro_Pendientes[i].nombre_cliente, MAX_INPUT);
                file >> registro_Pendientes[i].monto;

                if (file.fail()) break;
                if (file.peek() == '\n') file.ignore();
                i++;
            }

            num_pendientes = i;
        }

        //leer costos fijos
        else if (strcmp(nombre_archivo, "registro_costos_Fijos.txt") == 0) {
            while (true) {
                file.getline(registro_costos_Fijos[i].id, ID);
                file >> registro_costos_Fijos[i].monto;
                if (file.peek() == '\n') file.ignore();
                file.getline(registro_costos_Fijos[i].descripcion, MAX_INPUT);

                if (file.fail()) break;
                if (file.peek() == '\n') file.ignore();
                i++;
            }
            
            num_costos_Fijos = i;
        }
        
        //leer costos variables
        else if (strcmp(nombre_archivo, "registro_costos_Variables.txt") == 0) {
            while (true) {
                file.getline(registro_costos_Variables[i].id, ID);
                file >> registro_costos_Variables[i].monto;
                if (file.peek() == '\n') file.ignore();
                file.getline(registro_costos_Variables[i].descripcion, MAX_INPUT);
                if (file.peek() == '\n') file.ignore();
                file.getline(registro_costos_Variables[i].mes, ID);
                
                if (file.fail()) break;
                if (file.peek() == '\n') file.ignore();
                i++;
            }
            
            num_costos_Variables = i;
        }
    }

    file.close();
    return true;
}

bool escribir_Archivos(const char nombre_archivo[MAX_INPUT]) {
    int x = 0; //contador de elementos
    ofstream file;
    file.open(nombre_archivo, ios::trunc | ios::out);

    if (!file) return false;

    else {
        //escribir precio
        if (strcmp(nombre_archivo, "precio_galon.txt") == 0) file << precio_galon;

        //escribir vacas
        if (strcmp(nombre_archivo, "registro_Vacas.txt") == 0) {
            for (int i = 0; i < num_vacas; i++) {
                file << registro_Vacas[i].id << "\n";
                file << registro_Vacas[i].edad << "\n";
                file << registro_Vacas[i].prod_diaria << "\n";
                file << registro_Vacas[i].estado_salud << "\n";
                x++;
            }

            num_vacas = x;
        }
        
        //escribir clientes
        else if (strcmp(nombre_archivo, "registro_Clientes.txt") == 0) {
            for (int i = 0; i < num_clientes; i++) {
                file << registro_Clientes[i].id << "\n";
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
                file << registro_Ventas[i].fecha.dia << "\n";
                file << registro_Ventas[i].fecha.mes << "\n";
                file << registro_Ventas[i].fecha.year << "\n";
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
                file << registro_Pendientes[i].fecha.dia << "\n";
                file << registro_Pendientes[i].fecha.mes << "\n";
                file << registro_Pendientes[i].fecha.year << "\n";
                file << registro_Pendientes[i].nombre_cliente << "\n";
                file << registro_Pendientes[i].monto << "\n";
                x++;
            }

            num_pendientes = x;
        }

        //escribir costos fijos
        else if (strcmp(nombre_archivo, "registro_costos_Fijos.txt") == 0) {
            for (int i = 0; i < num_costos_Fijos; i++) {
                file << registro_costos_Fijos[i].id << "\n";
                file << registro_costos_Fijos[i].monto << "\n";
                file << registro_costos_Fijos[i].descripcion << "\n";
                x++;
            }

            num_costos_Fijos = x;
        }
        
        //escribir costos variables
        else if (strcmp(nombre_archivo, "registro_costos_Variables.txt") == 0) {
            for (int i = 0; i < num_costos_Variables; i++) {
                file << registro_costos_Fijos[i].id << "\n";
                file << registro_costos_Variables[i].monto << "\n";
                file << registro_costos_Variables[i].descripcion << "\n";
                file << registro_costos_Variables[i].mes << "\n";
                x++;
            }
            num_costos_Variables = x;
        }
    }


    file.close();
    return true;
}

//***************************************************************************************************

#endif