Proceso compararReportes
	Definir i Como Entero;
	Definir reporteAnterior, reporteActual, prod1, prod2, ing1, ing2, utilidad Como Real;
	Dimensionar reporteActual(5);
	Dimensionar reporteAnterior(5);
	prod1 <- reporteActual[0]-reporteAnterior[0];
	prod2 <- reporteActual[1]-reporteAnterior[1];
	ing1 <- reporteActual[2]-reporteAnterior[2];
	ing2 <- reporteActual[3]-reporteAnterior[3];
	utilidad <- reporteActual[4]-reporteAnterior[4];
	Escribir 'Reporte Mes Antepasado:';
	Escribir 'Produccion Semanal: ', reporteAnterior[0];
	Escribir 'Produccion Mensual: ', reporteAnterior[1];
	Escribir 'Ingresos Semanales: ', reporteAnterior[2];
	Escribir 'Ingresos Mensuales: ', reporteAnterior[3];
	Escribir 'Utilidad del Mes: ', reporteAnterior[4];
	Escribir 'Reporte Mes Pasado:';
	Escribir 'Produccion Semanal: ', reporteActual[0];
	Escribir 'Produccion Mensual: ', reporteActual[1];
	Escribir 'Ingresos Semanales: ', reporteActual[2];
	Escribir 'Ingresos Mensuales: ', reporteActual[3];
	Escribir 'Utilidad del Mes: ', reporteActual[4];
	Escribir 'Incrementos/Decrementos:';
	Escribir 'Produccion Semanal: ', prod1;
	Escribir 'Produccion Mensual: ', prod2;
	Escribir 'Ingresos Semanales: ', ing1;
	Escribir 'Ingresos Mensuales: ', ing2;
	Escribir 'Utilidad del Mes: ', utilidad;
FinProceso
