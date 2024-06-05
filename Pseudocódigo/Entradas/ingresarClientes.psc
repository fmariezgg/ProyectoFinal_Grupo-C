Proceso ingresarClientes
	Definir i, x Como Entero;
	Definir nombre, direccion, contacto Como Cadena;
	Definir compras Como Entero;
	Definir pagos_pendientes Como Cadena;
	Dimensionar nombre(100);
	Dimensionar direccion(100);
	Dimensionar contacto(100);
	Dimensionar compras(100);
	Dimensionar pagos_pendientes(100,100);
	Escribir 'cuantos clientes quiere ingresar al sistema?';
	Leer x;
	Para i<-0 Hasta x-1 Con Paso +1 Hacer
		Escribir 'ingresar nombre de cliente #', i+1, ': ';
		Leer nombre[i];
		Escribir 'ingresar direccion de cliente #', i+1, ': ';
		Leer direccion[i];
		Escribir 'ingresar contacto de cliente #', i+1, ': ';
		Leer contacto[i];
		Escribir 'ingresar compras de cliente #', i+1, ': ';
		Leer compras[i];
		Escribir 'ingresar pagos pendientes de cliente #', i+1, ': ';
		Leer pagos_pendientes[i,1];
		Escribir 'ingresar descripcion de pagos pendientes: ';
		Leer pagos_pendientes[i,2];
	FinPara
FinProceso
