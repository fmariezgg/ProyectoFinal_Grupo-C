Proceso menu
	Definir opcion Como Entero;
	Repetir
		Escribir '1. Ingresar Entradas';
		Escribir '2. Gesti�n de Producci�n';
		Escribir '3. Gesti�n de Ingresos';
		Escribir '4. Gesti�n de Costos';
		Escribir '5. Gesti�n de Utilidad';
		Escribir '6. Gesti�n de Reportes';
		Escribir '7. Cerrar sistema';
		Escribir 'escoja: ';
		Leer opcion;
		Segun opcion Hacer
			1:
				Escribir 'llamando subproceso de ingresar entradas...';
				// pedir al usuario que datos quiere ingresar
				// llamar al subproceso correspondiente
			2:
				Escribir 'llamando subproceso de gesti�n de producci�n...';
				// pedir al usuario si quiere calcular produccion o mostrarla
				// llamar subproceso correspondiente
			3:
				Escribir 'llamando subproceso de gesti�n de ingresos...';
				// pedir al usuario si quiere calcular ingresos o mostrarlos
				// llamar subproceso correspondiente
			4:
				Escribir 'llamando subproceso de gesti�n de costos...';
				// pedir al usuario si quiere ingresar costos o mostrarlos
				// si quiere ingresar costos, pedir si costos fijos o variables
				// llamar subproceso correspondiente
			5:
				Escribir 'llamando subproceso de gesti�n de utilidad...';
				// pedir al usuario si quiere calcular utilidad o mostrarla
				// llamar subproceso correspondiente
			6:
				Escribir 'llamando subproceso de gesti�n de reportes...';
				// pedir al usuario si quiere mostrar reportes o compararlos
				// si quiere mostrar reportes, pedir de cual mes
				// si quiere comparar reportes, pedir hasta cuantos meses atras quiere comparar
				// llamar subproceso correspondiente
			7:
				Escribir 'cerrando programa...';
			De Otro Modo:
				Escribir 'opcion invalida :/';
		FinSegun
	Hasta Que opcion=7
FinProceso
