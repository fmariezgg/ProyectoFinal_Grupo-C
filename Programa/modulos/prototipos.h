#include "mod_vacas.cpp"

#ifndef MOD_CLIENTES_CPP //como mod_clientes.cpp se incluye en mod_ventas+pendientes.cpp, se pone el include guard para que no se incluya mas de una vez y explote C++
#define MOD_CLIENTES_CPP
#include "mod_clientes.cpp"
#endif

#include "mod_ventas+pendientes.cpp"
#include "mod_costos.cpp"
using namespace std;
using namespace LLC;

//aqui se definen los prototipos de todas las funciones del sistema
//tambien estan las implementaciones de las funciones de precio y de calcular totales

//***************************************************************************************************

//todas estas retornan bool para que se pueda checkear si se pudo abrir/leer/escribir al archivo
bool ingresar_Precio();
bool registrar_Vacas(); //num es la cantidad de cosas que se van a registrar (para que el usuario no tenga que estar ingresando 1 por 1)
bool registrar_Clientes(); 
bool registrar_Ventas(); //aqui se registran los pagos pendientes tambien, dependiendo de lo que ingresa el usuario
bool registrar_costos_Fijos();
bool registrar_costos_Variables();

//^^ estas igual:
bool mostrar_Precio();
bool mostrar_Vacas();
bool mostrar_Clientes();
bool mostrar_Ventas();
bool mostrar_Pendientes();
bool mostrar_costos_Fijos();
bool mostrar_costos_Variables();

//estas retornan la posicion del id en el arreglo:
//retornan -2 si hubo un error con el archivo y -1 si no se encontro el id (si es >=0, es la posicion del id en el arreglo)
int buscar_Vaca(const char id[ID]);
int buscar_Cliente(const char input[MAX_INPUT], bool buscar_nombre); //buscar por el id o nombre dependiendo del segundo parametro
int buscar_Venta(const char id[ID]);
int buscar_Pendiente(const char id[ID]);
int buscar_costo_Fijo(const char id[ID]);
int buscar_costo_Variable(const char id[ID]);

bool editar_Vaca();
bool editar_Cliente();
bool editar_Venta(); //si se cambia a que ya se pago, la quita del registro de pendientes (y si no, la agrega)
bool editar_Pendiente();
bool editar_costo_Fijo();
bool editar_costo_Variable();

//estas retornan 0 si se elimino bien, -1 si no se encontro el id y -2 si hubo un error con el archivo
//si el registro estaba vacio retorna 1 y manda un mensaje (por eso es que no hay un caso de indice == 1 cuando se llaman en los menus)
int eliminar_Vaca(const char id[ID]);
int eliminar_Cliente(const char id[ID]);
int eliminar_Venta(const char id[ID]);
int eliminar_Pendiente(const char id[ID]); //tambien actualiza el registro de la venta para que no este pendiente
int eliminar_costo_Fijo(const char id[ID]);
int eliminar_costo_Variable(const char id[ID]);

bool calcular_Produccion(); 
bool calcular_Ingresos();
bool calcular_Costos();
bool calcular_Utilidad();

//***************************************************************************************************

bool ingresar_Precio() {
    system("cls || clear");
    _colSET(cLIGHT_YELLOW);
    cout << "\n   Ingrese el precio por galón (en C$): ";
    cin >> precio_galon;

    bool escribir = escribir_Archivos("precio_galon.txt");
    if (!escribir) return false;

    cout << "   ";
    Sleep(500);
    _colSET(cGREEN);
    cout << "Precio actualizado a: C$" << precio_galon << "...";
    Sleep(1500);
    _colRESET();
    return true;
}

bool mostrar_Precio() {
    system("cls || clear");
    bool leer = leer_Archivos("precio_galon.txt");
    if (!leer) return false;

    if (checkear_Vacio(precio_galon)) return true; //ver si esta vacio el archivo

    _colSET(cGREEN);
    cout << "\n   Precio por galón: C$" << precio_galon;
    Sleep(2250);
    _colRESET();
    return true;
}

//***************************************************************************************************

bool calcular_Produccion() {
    system("cls || clear");
    bool leer = leer_Archivos("registro_Vacas.txt");
    if (!leer) return false;

    if (checkear_Vacio(num_vacas)) return true;
    produccion_total = 0.00;

    _colSET(cTEAL);
    cout << "\n   Calculando...";
    Sleep(1000);

    for (int i = 0; i < num_vacas; i++) {
        produccion_total += registro_Vacas[i].prod_diaria;
    }

    _colSET(cLIGHT_YELLOW);
    cout << "\n   Producción total diaria: ";
    _colSET(cGREEN);
    cout << produccion_total << " galón(es)";
    _colSET(cLIGHT_YELLOW);
    cout << "\n   Producción total semanal: ";
    _colSET(cGREEN);
    cout << produccion_total*7 << " galón(es)";
    _colSET(cLIGHT_YELLOW);
    cout << "\n   Producción total mensual: ";
    _colSET(cGREEN);
    cout << produccion_total*30 << " galón(es)";


    _colSET(cGRAY);
    cout << "\n\n   Presione 'Enter' para continuar...";
    cin.ignore();
    cin.get();
    _colRESET();
    return true;
}

bool calcular_Ingresos() {
    system("cls || clear");
    bool leer = leer_Archivos("registro_Ventas.txt");
    if (!leer) return false;

    if (checkear_Vacio(num_ventas)) return true;
    ingresos_totales = 0.00;

    tm* time = obtener_fecha(); //para poder sumar las ventas del mes actual

    for (int i = 0; i < num_ventas; i++) { //sumar los montos de las ventas pagadas del mes actual
        if ((registro_Ventas[i].pagada) && (strcmp(registro_Ventas[i].fecha.mes, meses[time->tm_mon]) == 0))
            ingresos_totales += registro_Ventas[i].monto;
    }

    return true;
}

bool calcular_Costos() {
    system("cls || clear");
    bool leer_Fijos = false, leer_Variables = false;

    leer_Fijos = leer_Archivos("registro_costos_Fijos.txt");
    leer_Variables = leer_Archivos("registro_costos_Variables.txt");

    if (!leer_Fijos || !leer_Variables) return false;

    if ((num_costos_Fijos == 0) && (num_costos_Variables == 0)) { //si los DOS registros estan vacios, hay que decirle al usuario que no hay nada que sumar
        _colSET(cRED);
        cout << "   \nLos registros de costos estan vacíos...";
        _colRESET();
        return true;
    }

    costos_totales = 0.00;

    tm* time = obtener_fecha(); //para sumar los costos variables del mes actual

    for (int i = 0; i < num_costos_Fijos; i++) { //sumarle todos los costos fijos
        costos_totales += registro_costos_Fijos[i].monto;
    }

    for (int i = 0; i < num_costos_Variables; i++) { //si el costo variable es del mes actual, agregarlo al total
        if (strcmp(registro_costos_Variables[i].mes, meses[time->tm_mon]) == 0)
            costos_totales += registro_costos_Variables[i].monto;
    }

    return true;
}

bool calcular_Utilidad() {
    system("cls || clear");
    bool leer = leer_Archivos("registro_Ventas.txt"), leer2 = leer_Archivos("registro_costos_Fijos.txt"), leer3 = leer_Archivos("registro_costos_Variables.txt");
    if (!leer || !leer2 || !leer3) return false;

    if (checkear_Vacio(num_ventas)) return true;
    if ((num_costos_Fijos == 0) && (num_costos_Variables == 0)) {
        _colSET(cRED);
        cout << "   \nLos registros de costos estan vacíos...";
        _colRESET();
        return true;
    }

    utilidad = 0.00;

    _colSET(cTEAL);
    cout << "\n   Calculando...";
    Sleep(1000);

    if (calcular_Ingresos() && calcular_Costos()) utilidad = ingresos_totales - costos_totales;
    else return false;

    _colSET(cLIGHT_YELLOW);
    cout << "\n   Utilidad total mensual: ";

    if (utilidad < 0) _colSET(cRED);
    else if (utilidad > 0) _colSET(cGREEN);
    else _colRESET();

    cout << "C$" << utilidad;
    _colSET(cGRAY);
    cout << "\n\n   Presione 'Enter' para continuar...";
    cin.ignore();
    cin.get();
    _colRESET();
    return true;
}

//***************************************************************************************************