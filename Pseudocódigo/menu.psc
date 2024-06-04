Proceso menu
	Definir opcion Como Entero;
	Repetir
		Escribir '1. Ingresar Entradas';
		Escribir '2. Gestión de Producción';
		Escribir '3. Gestión de Ingresos';
		Escribir '4. Gestión de Costos';
		Escribir '5. Gestión de Utilidad';
		Escribir '6. Gestión de Reportes';
		Escribir '7. Cerrar sistema';
		Escribir 'escoja: ';
		Leer opcion;
		Segun opcion Hacer
			1:
				Escribir 'llamando subproceso de ingresar entradas...';
				// pedir al usuario que datos quiere ingresar
				// llamar al subproceso correspondiente
			2:
				Escribir 'llamando subproceso de gestión de producción...';
				// pedir al usuario si quiere calcular produccion o mostrarla
				// llamar subproceso correspondiente
			3:
				Escribir 'llamando subproceso de gestión de ingresos...';
				// pedir al usuario si quiere calcular ingresos o mostrarlos
				// llamar subproceso correspondiente
			4:
				Escribir 'llamando subproceso de gestión de costos...';
				// pedir al usuario si quiere ingresar costos o mostrarlos
				// si quiere ingresar costos, pedir si costos fijos o variables
				// llamar subproceso correspondiente
			5:
				Escribir 'llamando subproceso de gestión de utilidad...';
				// pedir al usuario si quiere calcular utilidad o mostrarla
				// llamar subproceso correspondiente
			6:
				Escribir 'llamando subproceso de gestión de reportes...';
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
