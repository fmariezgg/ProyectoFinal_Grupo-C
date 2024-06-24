Proceso generarReportes
	Definir reportes, produccion_semana, produccion_mes, ingresos_semana, ingresos_mes, utilidad_mes Como Real;
	Definir num_reporte Como Entero;
	Dimensionar reportes(100,5);
	reportes[num_reporte,0]<-produccion_semana;
	reportes[num_reporte,1]<-produccion_mes;
	reportes[num_reporte,2]<-ingresos_semana;
	reportes[num_reporte,3]<-ingresos_mes;
	reportes[num_reporte,4]<-utilidad_mes;
FinProceso
