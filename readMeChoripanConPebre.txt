
La tarea fue realizada de forma grupal.

Se utilizaron las herraminetas replit y github:

Link repositorio de github: https://github.com/vainillaLatte/Tarea-2
Link replit: https://replit.com/join/jeouspqipd-vaguzzely

Coevaluación:

Trabajo en equipo, el trabajo fue realizado de forma equitativa, todos los participantes trabajan de forma activa.

Puntaje asignado en la coevaluación en relación al trabajo en equipo:

95 César Anabalon
100 Michelle Madariaga
100 Alejandra Hidalgo
100 Valentina Guzmán

Archivo README:


----------------------------------
El menú se ve así:
Menú
================================================================
    1.- Crear jugador
    2.- Mostrar jugador
    3.- Agregar item a jugador
    4.- Eliminar item de jugador
    5.- Agregar puntos de habilidad al jugador
    6.- Mostrar jugadores con item específico
    7.- Deshacer última acción
    8.- Exportar datos de jugadores a archivo de texto
    9.- Cargar datos de jugadores desde un archivo de texto
================================================================
---------------------------------
El usuario debe ingresar la opción que quiera.

Casi todas las funciones realizan lo que se pide, excepto la 7, la de exportar datos.
creemos que es porque intenta acceder a una parte de la memoria que no tiene permiso para acceder, pero no tenemos la exactitud de qué parte de la función falla,
probablemente esté entre la definición de exportar o en el if de jugadores== NULL (líneas 258-260)

----------------------------------------------------------------

Si desea ver una descripión con más detalle de cada una de las funciones, puede leer lo siguiente:


Función 1:
Nombre: opcion1(HashMap * jugadores) //1.-Crear Jugador
Descripción: Permite al usuario crear un jugador y guardarlo en el HashMap.
Se utiliza la función crear jugador, implementada por nosotros.
Posibles causas de errores: El programa no da errores mientras se ingrese bien lo que se le pide.

Función 2:
Nombre: opcion2(char nombre[Max], HashMap *jugadores)//2.- Mostrar jugador
Descripción: Permite al usuario mostrar los datos de un jugador específico, el usuario debe ingresar el nombre del jugador que desea que sean mostrados los datos.
Posibles causas de errores: Esta función marcha bien siempre y cuando el jugador ingresado por el usuario exista en el HashMap.

Función 3:
Nombre: opcion3(char nombre[], char item[], HashMap *jugadores, int maxItems)// 3.- Agregar item a jugador
Descripción: Permite al usuario agregar un item a un jugador específico. Se agrega al char **items.
Posibles causas de errores: Esta función trabaja correctamente siempre y cuando el jugador ingresado por el usuario exista en el HashMap,  el usuario debe ingresar lo que se le pida.

Función 4:
Nombre: void opcion4(char nombre[], char item[], HashMap *jugadores)// 4.- Eliminar item de jugador.
Descripción: Permite al usuario eliminar un item de un jugador específico.
Esta función trabaja correctamente siempre y cuando el jugador ingresado por el usuario exista en el HashMap y tenga al menos un ítem. En caso contrario, se mostrará un aviso “El jugador (-) no existe o no tiene ningún ítem en su inventario”.

Función 5:
Nombre: void opcion5(char nombre[], int pHabilidad, HashMap *listJ)//5.- Agregar puntos de habilidad al jugador
Descripción: Permite al usuario agregar puntos de habilidad a un jugador específico.
Esta función trabaja correctamente siempre y cuando el jugador ingresado por el usuario exista en el HashMap.

Función 6:
Nombre: void opcion6(char item[],HashMap *jugadores)//6.- Mostrar jugadores con item específico
Descripción: Permite al usuario mostrar todos los jugadores que tengan un item específico.
Esta función marcha correctamente y mostrará todos los jugadores con el ítem especificado.

Función 7:
Nombre:  void opcion7(char nombre[], HashMap *jugadores)//7.- Deshacer última acción
Descripción: Permite al usuario deshacer la última acción realizada en el juego.
Esta función trabaja correctamente mientras el jugador exista. Si no hay una acción que deshacer en la pila de acciones del jugador, se muestra un mensaje que dice “No hay accion a eliminar”. 

Función 8:
Nombre: opcion8(HashMap *mapJuga)// 8.- Exportar datos de jugadores a archivo de texto
Descripción: Permite al usuario exportar los datos de todos los jugadores a un archivo de texto (output.csv).
Esta función no trabaja correctamente, debido a que arroja el error de "signal: segmentation fault (core dumped)".

Función 9:
Nombre: opcion9(HashMap *jugador, char *arch)//9.- Cargar datos de jugadores desde un archivo de texto
Descripción: Permite al usuario cargar los datos de los jugadores desde un archivo de texto, se le debe ingresar el nombre del archivo a leer. (puede ser el de 100 o el de 1000 jugadores)
Funciona correctamente.

---------------------------------------------------------------------------------



