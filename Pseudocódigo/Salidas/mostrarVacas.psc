Proceso mostrarVacas
	Definir i, x, id, edad, produccion, cantidad_vacas Como Entero;
	Definir estado_salud Como Cadena;
	Dimensionar id(300);
	Dimensionar edad(300);
	Dimensionar produccion(300);
	Dimensionar estado_salud(300);
	
	Para i<-0 Hasta cantidad_vacas Con Paso +1 Hacer
		Escribir 'Vaca #', i+1, ': ';
		Escribir 'ID: ', id[i];
		Escribir 'Edad: ', edad[i];
		Escribir 'Produccion: ', produccion[i];
		Escribir 'Estado de Salud: ', estado_salud[i];
	FinPara
FinProceso