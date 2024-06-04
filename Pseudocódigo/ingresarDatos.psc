SubProceso datosVacas
	definir i, x, id, edad, produccion como entero;
	definir estado_salud como cadena;
	dimensionar id[300];
	dimensionar edad[300];
	dimensionar produccion[300];
	dimensionar estado_salud[300];
	
	escribir "cuantas vacas quiere ingresar al sistema?";
	leer x;
	
	Para i<-0 Hasta x-1 Con Paso +1 Hacer
		escribir "ingresar identificacion de vaca #", i+1, ": ";
		leer id[i];
		escribir "ingresar edad de vaca #", i+1, ": ";
		leer edad[i];
		escribir "ingresar produccion de leche diaria de vaca #", i+1, ": ";
		leer produccion[i];
		escribir "ingresar estado de salud de vaca #", i+1, ": ";
		leer estado_salud[i];
	FinPara
FinSubProceso

SubProceso datosClientes
	definir i, x como entero;
	definir nombre, direccion, contacto como cadena;
	definir compras como entero;
	definir pagos_pendientes como cadena;
	dimensionar nombre[100];
	dimensionar direccion[100];
	dimensionar contacto[100];
	dimensionar compras[100];
	dimensionar pagos_pendientes[100, 100];
	
	escribir "cuantos clientes quiere ingresar al sistema?";
	leer x;
	
	Para i<-0 Hasta x-1 Con Paso +1 Hacer
		escribir "ingresar nombre de cliente #", i+1, ": ";
		leer nombre[i];
		escribir "ingresar direccion de cliente #", i+1, ": ";
		leer direccion[i];
		escribir "ingresar contacto de cliente #", i+1, ": ";
		leer contacto[i];
		escribir "ingresar compras de cliente #", i+1, ": ";
		leer compras[i];
		escribir "ingresar pagos pendientes de cliente #", i+1, ": ";
		leer pagos_pendientes[i, 1];
		escribir "ingresar descripcion de pagos pendientes: ";
		leer pagos_pendientes[i, 2];
	FinPara
	
FinSubProceso

SubProceso costos
	definir costosFijos, costosVariables como cadena;
	definir x, opcion como caracter;
	definir num, j, i como entero;
	dimensionar costosFijos[50,50];
	dimensionar costosVariables[50,50];
	
	escribir "quiere ingresar costos fijos o variables? (f/v) ";
	leer opcion;
	
	si opcion = "f" o opcion = "F" Entonces
		j <- 0;
		Repetir
			escribir "ingresar costo fijo: ";
			leer costosFijos[j,1];
			escribir "ingresar descripcion de costo: ";
			leer costosFijos[j,2];
			j <- j+1;
			escribir "quiere ingresar otro costo? (s/n) ";
			leer x;
			si x <> 's' o x <> 'S' o x <> 'n' o x <> 'N' Entonces
				escribir "entrada invalida, reingresar dato: ";
				escribir "quiere ingresar otro costo? (s/n) ";
				leer x;
			FinSi
		Hasta Que x = 'n' o x = 'N'
		
		si opcion = "v" o opcion = "f" Entonces
			escribir "cuantos costos variables ingresara? ";
			leer num;
			
			Para i<-0 Hasta num-1 Con Paso +1 Hacer
				escribir "ingresar costo variable #", i+1, ": ";
				leer costosVariables[i,1];
				escribir "ingresar descripcion de costo: ";
				leer costosVariables[i,2];
			FinPara
		FinSi
		
	SiNo
		escribir "entrada invalida";
	FinSi

FinSubProceso

Proceso ingresarDatos
	definir x Como Entero;
	definir precio como real;
	
	Repetir
		escribir "1. Ingresar datos de vacas";
		escribir "2. Ingresar datos de clientes";
		escribir "3. Ingresar costos";
		escribir "4. Definir precio de leche";
		escribir "5. Salir";
		escribir "Escoja: ";
		leer x;
		
		Segun x Hacer
			1:
				datosVacas;
			2:
				datosClientes;
			3:
				costos;
			4:
				escribir "a cuanto vendera la leche producida? ";
				leer precio;
			De Otro Modo:
				escribir "opcion invalida";
		FinSegun
		
	Hasta Que x = 5

FinProceso