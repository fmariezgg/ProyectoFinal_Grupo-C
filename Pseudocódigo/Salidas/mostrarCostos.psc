Proceso mostrarCostos
	Definir costosFijos, costosVariables Como Cadena;
	Definir opcion Como Cadena;
	Definir num, i, cantidad_CF, cantidad_CV Como Entero;
	Dimensionar costosFijos(50,2);
	Dimensionar costosVariables(50,2); // la primera dimension es el monto del costo, y la segunda su descripcion
	
	Escribir 'quiere mostrar costos fijos o variables? (f/v) ';
	Leer opcion;
	
	Si opcion='f' O opcion='F' Entonces
		Para i<-0 Hasta cantidad_CF Con Paso +1 Hacer
			Escribir 'Costo #', i+1, ': ', ;
			Escribir 'Monto: ', costosFijos[i,0];
			Escribir 'Monto: ', costosFijos[i,1];
		FinPara
		Si opcion='v' O opcion='f' Entonces
			Para i<-0 Hasta cantidad_CV Con Paso +1 Hacer
				Escribir 'Costo #', i+1, ': ', ;
				Escribir 'Monto: ', costosVariables[i,0];
				Escribir 'Monto: ', costosVariables[i,1];
			FinPara
		FinSi
		
	SiNo
		Escribir 'entrada invalida';
	FinSi
FinProceso
