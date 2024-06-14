Proceso calcularProduccion
	definir vaca_produccion, produccion_semanal, produccion_mensual como real;
	dimensionar vaca_produccion[100];
	
	produccion_semanal <- 0;
	para i<-0 hasta 99 con paso +1 Hacer
		produccion_semanal <- produccion_semanal + (vaca_produccion[i]*7);
	FinPara
	
	produccion_mensual <- produccion_semanal*4;
FinProceso