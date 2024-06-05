Proceso calcularUtilidad
	definir ingreso_mensual, utilidad_mensual, TOTALcostos_mensuales, costos_fijos_mensuales, costos_variables_mensuales como real;
	dimensionar costos_fijos_mensuales[100];
	dimensionar costos_variables_mensuales[100];
	
	para i<-0 hasta 99 con paso +1 Hacer
		TOTALcostos_mensuales <- TOTALcostos_mensuales + costos_fijos_mensuales[i] + costos_variables_mensuales[i];
	FinPara
	
	utilidad_mensual <- ingreso_mensual - TOTALcostos_mensuales;
	utilidad_mensual <- utilidad_mensual - (utilidad_mensual*0.3); //con impuestos
FinProceso