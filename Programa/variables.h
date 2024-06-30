#define ID 10 //tambien se ocupa como la longitud del C-string 'mes'
#define MAX_INPUT 100
#define MAX_REGISTER 1000

typedef struct FECHA {
    int dia = 0;
    char mes[ID] = "";
    int year = 0;
} FECHA;

typedef struct VACA {
    char id[ID] = "";
    int edad = 0;
    int prod_diaria = 0;
    char estado_salud[MAX_INPUT] = "";
} VACA;

typedef struct CLIENTE {
    char id[ID] = "";
    char nombre[MAX_INPUT] = "";
    char direccion[MAX_INPUT] = "";
    char contacto[MAX_INPUT] = "";
} CLIENTE;

typedef struct VENTA {
    char id[ID] = "";
    FECHA fecha;
    char nombre_cliente[MAX_INPUT] = "";
    float cantidad_leche = 0;
    float monto = 0.00;
    bool pagada = false;
} VENTA;

typedef struct PENDIENTE {
    char id_venta[ID] = "";
    FECHA fecha;
    char nombre_cliente[MAX_INPUT] = "";
    float monto = 0.00;
} PENDIENTE;

typedef struct COSTO {
    char id[ID] = "";
    float monto = 0.00;
    char descripcion[MAX_INPUT] = "";
    char mes[ID] = "";
} COSTO;

VACA registro_Vacas[MAX_REGISTER];
CLIENTE registro_Clientes[MAX_REGISTER];
VENTA registro_Ventas[MAX_REGISTER];
PENDIENTE registro_Pendientes[MAX_REGISTER];
COSTO registro_costos_Fijos[MAX_REGISTER];
COSTO registro_costos_Variables[MAX_REGISTER];

//para convertir lo que retorna time->tm_mon a un string
const char* meses[] = { "enero", "febrero", "marzo", "abril", "mayo", "junio", "julio", "agosto", "septiembre", "octubre", "noviembre", "diciembre" };

float precio_galon = 0.00;

//contadores de elementos de registros:
int num_vacas = 0;
int num_clientes = 0;
int num_ventas = 0;
int num_pendientes = 0;
int num_costos_Fijos = 0;
int num_costos_Variables = 0;