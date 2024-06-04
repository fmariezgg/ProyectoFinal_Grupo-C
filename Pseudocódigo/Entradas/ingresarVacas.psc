Proceso vacas
	Definir i, x, id, edad, produccion Como Entero;
	Definir estado_salud Como Cadena;
	Dimensionar id(300);
	Dimensionar edad(300);
	Dimensionar produccion(300);
	Dimensionar estado_salud(300);
	Escribir 'cuantas vacas quiere ingresar al sistema?';
	Leer x;
	Para i<-0 Hasta x-1 Con Paso +1 Hacer
		Escribir 'ingresar identificacion de vaca #', i+1, ': ';
		Leer id[i];
		Escribir 'ingresar edad de vaca #', i+1, ': ';
		Leer edad[i];
		Escribir 'ingresar produccion de leche diaria de vaca #', i+1, ': ';
		Leer produccion[i];
		Escribir 'ingresar estado de salud de vaca #', i+1, ': ';
		Leer estado_salud[i];
	FinPara
FinProceso
