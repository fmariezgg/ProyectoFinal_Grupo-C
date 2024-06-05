Proceso mostrarCostos
	definir costosFijos, costosVariables Como Cadena;
	Definir opcion Como caracter;
	Definir num, i, cantidad_CF, cantidad_CV Como Entero;
	Dimensionar costosFijos(50,50); //la primera dimension es el monto del costo, y la segunda su descripcion
	Dimensionar costosVariables(50,50);
	Escribir 'quiere mostrar costos fijos o variables? (f/v) ';
	Leer opcion;
	Si opcion='f' O opcion='F' Entonces
		para i<-0 hasta cantidad_CF con paso +1 Hacer
			escribir "Costo #", i+1, ": ",  ;
			escribir "Monto: ", costosFijos[i];
		FinPara
		Si opcion='v' O opcion='f' Entonces
			Escribir 'cuantos costos variables ingresara? ';
			Leer num;
			Para i<-0 Hasta num-1 Con Paso +1 Hacer
				Escribir 'ingresar costo variable #', i+1, ': ';
				Leer costosVariables[i,i];
				Escribir 'ingresar descripcion de costo: ';
				Leer costosVariables[i,i];
			FinPara
		FinSi
	SiNo
		Escribir 'entrada invalida';
	FinSi
FinProceso