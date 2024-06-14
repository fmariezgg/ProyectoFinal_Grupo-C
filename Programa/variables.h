#define MAX_INPUT 100
#define MAX_REGISTER 1000

typedef struct VACA {
    char id[10] = "";
    int edad = 0;
    int prod_diaria = 0;
    char estado_salud[MAX_INPUT];
} VACA;

typedef struct CLIENTE {
    char nombre[MAX_INPUT] = "";
    char direccion[MAX_INPUT] = "";
    char contacto[MAX_INPUT] = "";
    TRANSACCION pagos_pendientes[MAX_INPUT] = {{0, ""}};
} CLIENTE;

typedef struct VENTA {
    char id[10] = "";
    char nombre_cliente[MAX_INPUT] = "";
    char fecha[MAX_INPUT] = "";
    int cantidad_leche = 0;
    double monto = 0.00;
    bool pagada = false;
} VENTA;

typedef struct TRANSACCION {
    double monto = 0.00;
    char descripcion[MAX_INPUT] = "";
} TRANSACCION;

double precio_galon = 5.99;

VACA registro_Vacas[MAX_REGISTER];
CLIENTE registro_Clientes[MAX_REGISTER];
VENTA registro_Ventas[MAX_REGISTER];

TRANSACCION registro_costosFijos[MAX_REGISTER];
TRANSACCION registro_costosVariables[MAX_REGISTER];

int num_vacas = 0;
int num_clientes = 0;
int num_ventas = 0;

int num_costosF = 0;
int num_costosV = 0;