Proceso mostrarClientes
	Definir i, x, compras, cantidad_clientes Como Entero;
	Definir nombre, direccion, contacto, pagos_pendientes Como Cadena;
	Dimensionar nombre(300);
	Dimensionar direccion(300);
	Dimensionar contacto(300);
	Dimensionar pagos_pendientes(300);
	Dimensionar compras(300);
	Para i<-0 Hasta cantidad_clientes Con Paso +1 Hacer
		Escribir 'Cliente #', i+1, ': ';
		Escribir 'Nombre: ', nombre[i];
		Escribir 'Direccion: ', direccion[i];
		Escribir 'Contacto: ', contacto[i];
		Escribir 'Pagos Pendientes: ', pagos_pendientes[i];
		Escribir 'Compras: ', compras[i];
	FinPara
FinProceso
