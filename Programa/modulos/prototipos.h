#include "mod_vacas.cpp"
#include "mod_clientes.cpp"
#include "mod_ventas+pendientes.cpp"
#include "mod_costos.cpp"
using namespace std;

//aqui se definen los prototipos de todas las funciones del sistema
//tambien estan las implementaciones de las funciones de precio pero shhhhh, no valia la pena darles su propio archivo

//***************************************************************************************************

//todas estas retornan bool para que se pueda checkear si se pudo abrir/leer/escribir al archivo
bool ingresar_Precio();
bool registrar_Vacas(int num); //num es la cantidad de cosas que se van a registrar (para que el usuario no tenga que estar ingresando 1 por 1)
bool registrar_Clientes(int num); 
bool registrar_Ventas(int num); //aqui se registran los pagos pendientes tambien, dependiendo de lo que ingresa el usuario
bool registrar_costos_Fijos(int num);
bool registrar_costos_Variables(int num);

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
//si el registro estaba vacio retorna 1 y manda un mensaje (por eso es que no hay un caso de indice == 1 cuando las llamo en los menus)
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
    LLC::_colSET(LLC::cLIGHT_YELLOW);
    cout << "\n   Ingrese el precio por galón (en C$): ";
    cin >> precio_galon;

    bool escribir = escribir_Archivos("precio_galon.txt");
    if (!escribir) return false;

    cout << "   ";
    this_thread::sleep_for(chrono::milliseconds(500));
    LLC::_colSET(LLC::cGREEN);
    cout << "Precio actualizado a: C$" << precio_galon << "...";
    this_thread::sleep_for(chrono::milliseconds(1500));
    LLC::_colRESET();
    return true;
}

bool mostrar_Precio() {
    system("cls || clear");
    bool leer = leer_Archivos("precio_galon.txt");
    if (!leer) return false;

    if (precio_galon == 0.00) {
        LLC::_colSET(LLC::cRED);
        cout << "\n   No hay precio registrado...";
        this_thread::sleep_for(chrono::milliseconds(2250));
        LLC::_colRESET();
        return true;
    }

    LLC::_colSET(LLC::cGREEN);
    cout << "\n   Precio por galón: C$" << precio_galon;
    this_thread::sleep_for(chrono::milliseconds(2250));
    LLC::_colRESET();
    return true;
}

bool calcular_Produccion(){
    system("cls || clear");
    bool leer = leer_Archivos("registro_Vacas.txt");
    if (!leer) return false;

    if (checkear_Vacio(num_vacas)) return true;


    for (int i = 0; i < num_vacas; i++) {
        produccion_total += registro_Vacas[i].prod_diaria;
    }

    LLC::_colSET(LLC::cGREEN);
    cout << "\n   Producción total diaria: " << total << " galón(es)";
    this_thread::sleep_for(chrono::milliseconds(2250));
    LLC::_colRESET();
    return true;
}

bool calcular_Ingresos() {
    system("cls || clear");
    bool leer = leer_Archivos("registro_Ventas.txt");
    if (!leer) return false;

    if (checkear_Vacio(num_ventas)) return true;

    for (int i = 0; i < num_ventas; i++) {
        ingresos_totales += registro_Ventas[i].monto;
    }

    LLC::_colSET(LLC::cGREEN);
    cout << "\n   Ingresos totales: C$" << ingresos_totales;
    this_thread::sleep_for(chrono::milliseconds(2250));
    LLC::_colRESET();
    return true;
}

bool calcular_Costos() {
    system("cls || clear");
    bool leer = leer_Archivos("registro_costos_Fijos.txt");
    if (!leer) return false;

    if (checkear_Vacio(num_costos_Fijos)) return true;

    for (int i = 0; i < num_costos_Fijos; i++) {
        costos_totales += registro_costos_Fijos[i].monto;
    }

    leer = leer_Archivos("registro_costos_Variables.txt");
    if (!leer) return false;

    if (checkear_Vacio(num_costos_Variables)) return true;

    for (int i = 0; i < num_costos_Variables; i++) {
        costos_totales += registro_costos_Variables[i].monto;
    }

    LLC::_colSET(LLC::cGREEN);
    cout << "\n   Costos totales: C$" << costos_totales;
    this_thread::sleep_for(chrono::milliseconds(2250));
    LLC::_colRESET();
    return true;
}

bool calcular_Utilidad() {
    system("cls || clear");
    bool leer = leer_Archivos("registro_Ventas.txt");
    if (!leer) return false;

    if (checkear_Vacio(num_ventas)) return true;

    for (int i = 0; i < num_ventas; i++) {
        if (registro_Ventas[i].pagada) utilidad += registro_Ventas[i].monto;
    }

    utilidad -= costos_totales;

    LLC::_colSET(LLC::cGREEN);
    cout << "\n   Utilidad total: C$" << utilidad;
    this_thread::sleep_for(chrono::milliseconds(2250));
    LLC::_colRESET();
    return true;
}




