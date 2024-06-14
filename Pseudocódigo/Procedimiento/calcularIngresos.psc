Proceso calcularIngresos
	definir precio, clientes_compras, ingreso_semanal, ingreso_mensual como real;
	dimensionar clientes_compras[100];
	
	escribir "ingresar precio de leche: ";
	leer precio;

	ingreso_semanal <- 0;
	para i<-0 hasta 99 con paso +1 Hacer
		ingreso_semanal <- ingreso_semanal + (clientes_compras[i]*precio);
	FinPara

	ingreso_mensual <- ingreso_semanal*4;
FinProceso