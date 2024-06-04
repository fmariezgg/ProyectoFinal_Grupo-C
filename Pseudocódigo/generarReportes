Estructura Reporte
    Entero produccion
    Real ingresos, costos, utilidad
FinEstructura

Definir reporte Como Nuevo Reporte
Definir nombreArchivo Como Cadena "reportes.txt"
Definir opcion Como Entero
Definir archivo Como Texto

Repetir
    Escribir "1. Guardar Reporte"
    Escribir "2. Mostrar Reportes"
    Escribir "3. Salir"
    Escribir "Seleccione una opción: "
    Leer opcion

    Segun opcion Hacer
        1:
            Escribir "Ingrese la producción: "
            Leer reporte.produccion
            Escribir "Ingrese los ingresos: "
            Leer reporte.ingresos
            Escribir "Ingrese los costos: "
            Leer reporte.costos
            reporte.utilidad <- reporte.ingresos - reporte.costos
            AbrirArchivo(archivo, nombreArchivo, append)
            Escribir archivo, reporte.produccion, " ", reporte.ingresos, " ", reporte.costos, " ", reporte.utilidad, "\n"
            CerrarArchivo(archivo)
            Escribir "Reporte guardado correctamente."
        2:
            AbrirArchivo(archivo, nombreArchivo)
            Si archivo Abierto Entonces
                Repetir
                    Leer linea De archivo
                    Si NoEof(archivo) Entonces
                        Imprimir linea
                    FinSi
                Hasta Eof(archivo)
                CerrarArchivo(archivo)
            SiNo
                Escribir "No se pudo abrir el archivo para mostrar los reportes."
            FinSi
        3:
            Escribir "Saliendo..."
        Otro:
            Escribir "Opción no válida."
    FinSegun
Hasta Que opcion = 3
