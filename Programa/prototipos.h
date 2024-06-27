#include "mod_vacas.cpp"
#include "mod_clientes.cpp"
#include "mod_ventas+pendientes.cpp"
#include "mod_costos.cpp"
using namespace std;

/*
pendientes:
-- quitar la estructura de fecha y solo convertir  el tm* a un string para que sea mas facil de manejar
-- validar id's para que no se repitan
-- cuando se ingrese una venta de un cliente que no esta registrado, avisarle al usuario que lo registre primero
-- debug/refine de editar y eliminar
-- los procesos de salida: calcular produccion, ingresos, costos y utilidad
*/

/*aqui se definen los prototipos de todas las funciones del sistema
 (tambien estan las implementaciones de las funciones de precio pero shhhhh, no valia la pena darles su propio archivo)*/

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

bool editar_Vacas();
bool editar_Clientes();
bool editar_Ventas(); //si se cambia a que ya se pago, quitar la venta del registro de pendientes
bool editar_Pendientes();
bool editar_costos_Fijos();
bool editar_costos_Variables();

bool eliminar_Vacas();
bool eliminar_Clientes();
bool eliminar_Ventas();
bool eliminar_Pendientes(); //cuando se elimine, que actualice el registro de la venta para que no aparezca como pendiente
bool eliminar_costos_Fijos();
bool eliminar_costos_Variables();

//***************************************************************************************************

bool ingresar_Precio() {
    system("cls || clear");
    cambiar_color(14);
    cout << "\n   Ingrese el precio por galón (en C$): ";
    cin >> precio_galon;

    bool escribir = escribir_Archivos("precio_galon.txt");
    if (!escribir) return false;

    cout << "   ";
    Sleep(500);
    cambiar_color(10);
    cout << "Precio actualizado a: C$" << precio_galon << "...";
    Sleep(1500);
    resetear_color();
    return true;
}

bool mostrar_Precio() {
    system("cls || clear");
    bool leer = leer_Archivos("precio_galon.txt");
    if (!leer) return false;

    if (precio_galon == 0.00) {
        cambiar_color(12);
        cout << "\n   No hay precio registrado...";
        Sleep(3000);
        resetear_color();
        return true;
    }

    cambiar_color(10);
    cout << "\n   Precio por galón: C$" << precio_galon;
    Sleep(3000);
    resetear_color();
    return true;
}