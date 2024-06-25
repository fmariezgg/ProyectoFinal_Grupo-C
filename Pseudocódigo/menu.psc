Algoritmo menu
	Definir opcion Como Entero
	Repetir
		Escribir '1. Ingresar Entradas'
		Escribir '2. Gestion de Produccion'
		Escribir '3. Gestion de Ingresos'
		Escribir '4. Gestion de Costos'
		Escribir '5. Gestion de Utilidad'
		Escribir '6. Cerrar sistema'
		Escribir 'escoja: '
		Leer opcion
		Según opcion Hacer
			1:
				Escribir 'llamando subproceso de ingresar entradas...'
				// pedir al usuario que datos quiere ingresar
				// llamar al subproceso correspondiente
			2:
				Escribir 'llamando subproceso de gesti?n de producci?n...'
				// pedir al usuario si quiere calcular produccion o mostrarla
				// llamar subproceso correspondiente
			3:
				Escribir 'llamando subproceso de gesti?n de ingresos...'
				// pedir al usuario si quiere calcular ingresos o mostrarlos
				// llamar subproceso correspondiente
			4:
				Escribir 'llamando subproceso de gesti?n de costos...'
				// pedir al usuario si quiere ingresar costos o mostrarlos
				// si quiere ingresar costos, pedir si costos fijos o variables
				// llamar subproceso correspondiente
			5:
				Escribir 'llamando subproceso de gesti?n de utilidad...'
				// pedir al usuario si quiere calcular utilidad o mostrarla
				// llamar subproceso correspondiente
			6:
				Escribir 'cerrando programa...'
			De Otro Modo:
				Escribir 'opcion invalida :/'
		FinSegún
	Hasta Que opcion=6
FinAlgoritmo
