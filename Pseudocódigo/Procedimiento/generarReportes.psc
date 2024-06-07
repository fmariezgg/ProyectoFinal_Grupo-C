Proceso compararReportes
    Definir i Como Entero;
    Definir reporteAnterior, reporteActual Como Real;
	
    // Asignar valores a reporteAnterior
    Escribir 'Ingrese datos del reporte del mes antepasado:';
    Para i <- 0 Hasta 4 Hacer
        Segun i Hacer
            0: Escribir 'Produccion Semanal: ';
            1: Escribir 'Produccion Mensual: ';
            2: Escribir 'Ingresos Semanales: ';
            3: Escribir 'Ingresos Mensuales: ';
            4: Escribir 'Utilidad del Mes: ';
        FinSegun
        Leer reporteAnterior;
    FinPara
	
    // Asignar valores a reporteActual
    Escribir 'Ingrese datos del reporte del mes pasado:';
    Para i <- 0 Hasta 4 Hacer
        Segun i Hacer
            0: Escribir 'Produccion Semanal: ';
            1: Escribir 'Produccion Mensual: ';
            2: Escribir 'Ingresos Semanales: ';
            3: Escribir 'Ingresos Mensuales: ';
            4: Escribir 'Utilidad del Mes: ';
        FinSegun
        Leer reporteActual;
    FinPara
FinProceso
