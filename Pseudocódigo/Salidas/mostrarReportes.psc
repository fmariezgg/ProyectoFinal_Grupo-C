Proceso mostrarReportes
	Definir reportes Como Real;
	Definir x Como Entero;
	Dimensionar reportes(100,5);
	
	Escribir 'Que reporte quiere ver? ';
	Leer x;
	
	Escribir 'Mostrando reporte #', x, ': ';
	Escribir 'Reporte Mes Antepasado:';
	Escribir 'Produccion Semanal: ', reportes[x,0];
	Escribir 'Produccion Mensual: ', reportes[x,1];
	Escribir 'Ingresos Semanales: ', reportes[x,2];
	Escribir 'Ingresos Mensuales: ', reportes[x,3];
	Escribir 'Utilidad del Mes: ', reportes[x,4];
FinProceso
