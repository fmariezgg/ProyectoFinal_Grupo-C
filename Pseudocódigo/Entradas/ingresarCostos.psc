Proceso costos
	Definir costosFijos, costosVariables Como Cadena;
	Definir x, opcion Como Cadena;
	Definir num, j, i Como Entero;
	Dimensionar costosFijos(50,50);
	Dimensionar costosVariables(50,50);
	Escribir 'quiere ingresar costos fijos o variables? (f/v) ';
	Leer opcion;
	Si opcion='f' O opcion='F' Entonces
		j <- 0;
		Repetir
			Escribir 'ingresar costo fijo: ';
			Leer costosFijos[j,1];
			Escribir 'ingresar descripcion de costo: ';
			Leer costosFijos[j,2];
			j <- j+1;
			Escribir 'quiere ingresar otro costo? (s/n) ';
			Leer x;
			Si x<>'s' O x<>'S' O x<>'n' O x<>'N' Entonces
				Escribir 'entrada invalida, reingresar dato: ';
				Escribir 'quiere ingresar otro costo? (s/n) ';
				Leer x;
			FinSi
		Hasta Que x='n' O x='N'
		Si opcion='v' O opcion='f' Entonces
			Escribir 'cuantos costos variables ingresara? ';
			Leer num;
			Para i<-0 Hasta num-1 Con Paso +1 Hacer
				Escribir 'ingresar costo variable #', i+1, ': ';
				Leer costosVariables[i,1];
				Escribir 'ingresar descripcion de costo: ';
				Leer costosVariables[i,2];
			FinPara
		FinSi
	SiNo
		Escribir 'entrada invalida';
	FinSi
FinProceso
