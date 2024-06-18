#define ID 10
#define MAX_INPUT 100
#define MAX_REGISTER 1000

/*typedef struct FECHA {
    char mes[ID] = "";
    int dia = 0;
    int year = 0;
} FECHA;*/

typedef struct VACA {
    char id[ID] = "";
    char estado_salud[MAX_INPUT] = "";
    int edad = 0;
    int prod_diaria = 0;
} VACA;

typedef struct CLIENTE {
    char nombre[MAX_INPUT] = "";
    char direccion[MAX_INPUT] = "";
    char contacto[MAX_INPUT] = "";
} CLIENTE;

typedef struct VENTA {
    char id[ID] = "";
    char nombre_cliente[MAX_INPUT] = "";
    //FECHA fecha = {"", 0, 0};
    int cantidad_leche = 0;
    float monto = 0.00;
    bool pagada = false;
} VENTA;

typedef struct PENDIENTE {
    char id_venta[ID] = "";
    char nombre_cliente[MAX_INPUT] = "";
} PENDIENTE;

typedef struct TRANSACCION {
    float monto = 0.00;
    char descripcion[MAX_INPUT] = "";
} TRANSACCION;

VACA registro_Vacas[MAX_REGISTER];
CLIENTE registro_Clientes[MAX_REGISTER];
VENTA registro_Ventas[MAX_REGISTER];
TRANSACCION registro_costos_Fijos[MAX_REGISTER];
TRANSACCION registro_costos_Variables[MAX_REGISTER];

float precio_galon = 0.00;
int num_vacas = 0;
int num_clientes = 0;
int num_pagos = 0;
int num_ventas = 0;
int num_costos_Fijos = 0;
int num_costos_Variables = 0;