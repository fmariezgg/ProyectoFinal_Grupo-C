#include <iostream>
#include <fstream>
#include <cstring>
#include "variables.h"
using namespace std;

//procesos de pedir datos:
void ingresar_Cstring(char* input, char dato[MAX_INPUT]);
int ingresar_int(char dato[MAX_INPUT]);
double ingresar_double(char dato[MAX_INPUT]);
bool ingresar_bool(char dato[MAX_INPUT]);

//funciones para abrir/leer/escribir archivos:
bool leer_archivo(char archivo[MAX_INPUT]);
bool escribir_archivo(char archivo[MAX_INPUT]);

//***************************************************************************************************

void ingresar_Cstring(char* input, char dato[MAX_INPUT]) {
    while (true) {
        cout << "\nIngresar " << dato << ": ";
        scanf(" %[^\n]", input);

        if (strlen(input) > MAX_INPUT) {
            cout << "\nERROR: " << dato << " ingresado es demasiado largo...\n";
            continue;
        } else break;
    }
}

int ingresar_int(char dato[MAX_INPUT]) {
    int num = 0;
    cout << "\nIngresar " << dato << ": ";
    cin >> num;
    return num;
}

double ingresar_double(char dato[MAX_INPUT]) {
    double num = 0.00;
    cout << "\nIngresar " << dato << ": ";
    cin >> num;
    return num;
}

bool ingresar_bool(char dato[MAX_INPUT]) {
    bool check = false;
    char input = '\0';

    while (true) {
        cout << "\nIngresar " << dato << ": (s/n)";
        cin >> input;

        if ((input == 's') || (input == 'S')) {
            check = true;
            break;
        } else if ((input == 'n') || (input == 'N')) {
            check = false;
            break;
        } else {
            cout << "\nERROR: entrada invalida...\n\n";
            continue;
        }
    }

    return check;
}

//***************************************************************************************************

bool leer_archivo(char archivo[MAX_INPUT]) {
    int i = 0;
    ifstream file;
    file.open(archivo);

    if (!file.is_open()) {
        cout << "\nERROR: No se pudo abrir el archivo: " << archivo << "...\n";
        return false;
    }

    else {
        //VACAS
        if (archivo == "registro_vacas.txt") {
            while (file >> registro_Vacas[i].id && file >> registro_Vacas[i].edad &&
                   file >> registro_Vacas[i].prod_diaria &&
                   file >> registro_Vacas[i].estado_salud) { i++; }
            
            num_vacas = i;
        }
        
        //CLIENTES
        else if (archivo == "registro_clientes.txt") {
            while (file >> registro_Clientes[i].nombre && file >> registro_Clientes[i].direccion &&
                   file >> registro_Clientes[i].contacto && file >> registro_Clientes[i].pagos_pendientes->monto
                   && file >> registro_Clientes[i].pagos_pendientes->descripcion) { i++; }
            
            num_clientes = i;
        }

        //VENTAS
        else if (archivo == "registro_ventas.txt") {
            while (file >> registro_Ventas[i].id && file >> registro_Ventas[i].nombre_cliente
                   && file >> registro_Ventas[i].fecha && file >> registro_Ventas[i].cantidad_leche
                   && file >> registro_Ventas[i].monto && file >> registro_Ventas[i].pagada) { i++; }

            num_ventas = i;
        }
        
        //COSTOS FIJOS
        else if (archivo == "registro_costosFijos.txt") {
            while (file >> registro_costosFijos[i].monto &&
                   file >> registro_costosFijos[i].descripcion) { i++; }
            
            num_costosF = i;
        }
        
        //COSTOS VARIABLES
        else if (archivo == "registro_costosVariables.txt") {
            while (file >> registro_costosVariables[i].monto &&
                   file >> registro_costosVariables[i].descripcion) { i++; }
            
            num_costosV = i;
        }
    }

    file.close();
    return true;
}

bool escribir_archivo(char archivo[MAX_INPUT]) {
    int x = 0;
    ofstream file;
    file.open(archivo, ios::trunc | ios::out);

    if (!file.is_open()) {
        cout << "\nERROR: No se pudo abrir el archivo: " << archivo << "...\n";
        return false;
    }

    else {
        //VACAS
        if (archivo == "registro_vacas.txt") {
            for (int i = 0; i < num_vacas; i++) {
                file << registro_Vacas[i].id << "\n";
                file << registro_Vacas[i].edad << "\n";
                file << registro_Vacas[i].prod_diaria << "\n";
                file << registro_Vacas[i].estado_salud << "\n";
                x++;
            }

            num_vacas = x;
        }
        
        //CLIENTES
        else if (archivo == "registro_clientes.txt") {
            for (int i = 0; i < num_clientes; i++) {
                file << registro_Clientes[i].nombre << "\n";
                file << registro_Clientes[i].direccion << "\n";
                file << registro_Clientes[i].contacto << "\n";
                file << registro_Clientes[i].pagos_pendientes << "\n";
                x++;
            }

            num_clientes = x;
        }

        //VENTAS
        else if (archivo == "registro_ventas.txt") {
            for (int i = 0; i < num_ventas; i++) {
                file << registro_Ventas[i].id << "\n";
                file << registro_Ventas[i].nombre_cliente << "\n";
                file << registro_Ventas[i].fecha << "\n";
                file << registro_Ventas[i].cantidad_leche << "\n";
                file << registro_Ventas[i].monto << "\n";
                file << registro_Ventas[i].pagada << "\n";
                x++;
            }

            num_ventas = x;
        }
        
        //COSTOS FIJOS
        else if (archivo == "registro_costosFijos.txt") {
            for (int i = 0; i < num_costosF; i++) {
                file << registro_costosFijos[i].monto << "\n";
                file << registro_costosFijos[i].descripcion << "\n";
                x++;
            }

            num_costosF = x;
        }
        
        //COSTOS VARIABLES
        else if (archivo == "registro_costosVariables.txt") {
            for (int i = 0; i < num_costosV; i++) {
                file << registro_costosVariables[i].monto << "\n";
                file << registro_costosVariables[i].descripcion << "\n";
                x++;
            }
            num_costosV = x;
        }
    }


    file.close();
    return true;
}