#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include <stdbool.h>
#include "hashmap.h"
#include "list.h"
#include "stack.h"
#define Max 31
#define TABLE_SIZE 100
#define MAX_ITEMS 8

typedef struct
{
  char nombre[Max];
  int pHabilidad;
  int item;
  char **items; //Es un puntero doble, utilizado para almacenar un arreglo de cadenas de texto.
  Stack* acciones; 
}Jugador;

typedef struct{
  char accion[Max];
  void* dato;
}Accion;

//función que crea jugador, se llama el la función opcion1
void crearJugador(char nombre[], HashMap * jugadores)
{
  Jugador  *p = (Jugador *)malloc(sizeof(Jugador));
  
  strcpy(p->nombre, nombre);
  p->pHabilidad = 0; //Se pide que los P.H de cada jugador comience en 0
  p->item = 0; //inventario vacío
  p->acciones = (Stack*)malloc(sizeof(Stack*));
  insertMap(jugadores, nombre, p);
}

//crea al jugador
void opcion1(HashMap * jugadores)
{
  char nombre[Max];
  
  getchar();
  printf("\nIngrese nombre de jugador: ");
  scanf("%[^\n]%*c", nombre);
  crearJugador(nombre, jugadores);
}
//muestra el jugador y su equipamiento
void opcion2(char nombre[Max], HashMap *jugadores)
{
  Pair *buscado = searchMap(jugadores, nombre);
  Jugador * aux;
  
  while(buscado != NULL)
  {
    aux = buscado->value;
    if(strcmp(aux->nombre, nombre) == 0)
    { 
      printf("\nDatos del jugador buscado\n");
      puts("======================================================");
      printf("\tNombre              : %s\n", aux->nombre);
      printf("\tPuntos de habilidad : %i\n", aux->pHabilidad);
      printf("\tCantidad de item    : %i\n", aux->item);
      
      for(int i = 0; i < aux->item; i++)
      {
        printf("\tItems               : %s\n", aux->items[i]);
      }
      puts("======================================================");
      return;
    }
    else
    {
      printf("\nNombre del jugador no existe.\n");
      return;
    }
  }
}
//agrega ítem a jugador
void opcion3(char nombre[], char item[], HashMap *jugadores, int maxItems)
{
  Jugador *player = searchMap(jugadores, nombre)->value;
  
  if (player != NULL)
  {
    // Si el jugador tiene espacio suficiente en su inventario
    if (player->item < maxItems)
    {
      if (player->items == NULL)
      {
        player->items = (char **)malloc(maxItems * sizeof(char *));
        for (int i = 0; i < maxItems; i++)
        {
          player->items[i] = (char *)malloc(Max * sizeof(char));
        }
      }
      // nuevo ítem en el inventario del jugador
      strcpy(player->items[player->item], item);
      player->item++;
       // Se crea una nueva acción y se agrega a la pila de acciones del jugador
      Accion * queHizo = (Accion*) malloc(sizeof(Accion));
      
      strcpy(queHizo->accion, "opcion3");
      queHizo->dato = item;
      stack_push(player->acciones, queHizo);
    }
    else
    {
      printf("\nEl inventario del jugador %s está lleno\n", nombre);
    }
  }
  else
  {
    printf("\nEl jugador %s no existe\n", nombre);
  }
}

//elimina ítem a jugador
void opcion4(char nombre[], char item[], HashMap *jugadores)
{
  Jugador *player = searchMap(jugadores, nombre)->value;
  Accion * queHizo = (Accion*) malloc(sizeof(Accion));
  
  if (player != NULL && player->item > 0)
  {
    int i;
    
    for (i = 0; i < player->item; i++)
    {
      if (strcmp(player->items[i], item) == 0)
      {
        strcpy(queHizo->accion, "opcion4");
        queHizo->dato = (void*) item;
        stack_push(player->acciones, queHizo);
        free(player->items[i]);       
        
        for (; i < player->item - 1; i++)
        {
          player->items[i] = player->items[i + 1];
        }
        player->item--;
        printf("\nEl item %s fue eliminado del inventario de %s\n", item, nombre);
        return;
      }
    }
    printf("\nEl jugador %s no tiene el item %s en su inventario\n", nombre, item);
  }
  else
  {
    printf("\nEl jugador %s no existe o no tiene ningún item en su inventario\n", nombre);
  }
}

//agrega puntos de habilidad al jugador
void opcion5(char nombre[], int pHabilidad, HashMap *listJ)
{
  Pair *aBuscar = searchMap(listJ, nombre);
  Jugador *aSumarPuntos = aBuscar->value;

  if(strcmp(aSumarPuntos->nombre, nombre) == 0)
  {
    aSumarPuntos->pHabilidad += pHabilidad;
    printf("\nPuntos de habilidad agregados con exito.\n");
    Accion * queHizo = (Accion*) malloc(sizeof(Accion));
    
    strcpy(queHizo->accion, "opcion5");
    queHizo->dato = (void *) pHabilidad;
        
    stack_push(aSumarPuntos->acciones, queHizo);
  }
}

/*
en la opcion 6 nos encontramos con la asignacion de los jugadores a una variable en donde comparamos el arreglo de los items de cada persona 
*/

void opcion6(char item[],HashMap *jugadores)
{
  
  Pair* aux = firstMap(jugadores);
  Jugador * datosJug  = aux->value;
  int i;
  bool flag = false;
  
  printf("Jugadores con este objeto : ");
  while(aux!= NULL)
  {
    datosJug = aux->value;
    
    for(i = 0; i < datosJug->item; i ++)
    {
      if(strcmp(item, datosJug->items[i]) == 0)
      {
        printf("\nNombre: %s", datosJug->nombre);
        flag = true;
        break;
      }
    }
    aux = nextMap(jugadores);
  }
  if(flag == false) printf("Ninguno");
}

void opcion7(char nombre[], HashMap *jugadores)
{
  /* para hacer esta funcion debo de crear una pila esa pila me tiene que guardar las acciones del jugador como agregar un item o eliminarlo o el aumentar los puntos de habilidad
  de ser el caso que no exista acciones por deshacer mostrar un aviso 
  */
  
  Jugador * player = searchMap(jugadores, nombre)->value;
  if(player == NULL) return;
  Accion* ultimaAccion = stack_top(player->acciones);

  if(ultimaAccion == NULL)
  {
    puts("======================================================");
    printf("No hay accion a eliminar\n");
    puts("======================================================");
    return;
  }
  
  if(strcmp(ultimaAccion->accion, "opcion3") == 0)
  {
    stack_pop(player->acciones);
    player->items[player->item-1] = NULL;
    player->item --;
    puts ("======================================================");
    printf("Item Eliminado\n");
    puts("======================================================");
  }
  
  if(strcmp(ultimaAccion->accion, "opcion4") == 0)
  {
    stack_pop(player->acciones);
    player->items[player->item+1] = ultimaAccion->dato;
    player->item ++;
    puts("======================================================");
    printf("Item Agregado\n");
    puts("======================================================");
  }

  if(strcmp(ultimaAccion->accion, "opcion5") == 0)
  {
    int puntosMenos =(int*) ultimaAccion->dato;
    stack_pop(player->acciones);
    player->pHabilidad =player->pHabilidad - puntosMenos ;
    puts("======================================================");
    printf("Chao Puntos\n");
    puts("======================================================");
  }
}

//funcion exportar, arroja segmentation fault (core dumped)
void opcion8(HashMap *mapJuga)
{
  FILE *jugadores;
  Jugador *exportar;
  
  jugadores = fopen("output.csv", "w");
  if (!jugadores) exit(EXIT_FAILURE);
  
  exportar = firstMap(mapJuga)->value;
  
  if(jugadores == NULL)
  {
    printf("Se produjo un error al crear el archivo\n");
    return;
  }
  if(exportar == NULL)
  {
    printf("Se produjo un error al crear el archivo\n");
    return;
  }
  fprintf(jugadores, "NOMBRE, PUNTOS DE HABILIDAD, CANTIDAD DE ITEM, ITEMS\n");
  
  while(exportar != NULL)
  {
    fprintf(jugadores, "%s, %i, %i", exportar->nombre, exportar->pHabilidad, exportar->item);
    for(int i = 0; i < exportar->item; i++)
      {
        fprintf(jugadores,", %s",exportar->items[i]);
      }
    //fprintf(jugadores, "\n");
    exportar = nextMap(mapJuga)->value;
  }
  fclose(jugadores);
}

//Cargar datos de jugadores desde un archivo de texto
void opcion9(HashMap *jugador, char *arch)
{
  FILE *ju = fopen(arch, "r");

  if(!ju)
  {
    printf("Se produjo un error");
    return;
  }
  else
  {
    char line[1024];

    while (fgets(line, 1024, ju))
    {
      Jugador *juga = malloc(sizeof(Jugador));
      
      juga->items = (char **)malloc(MAX_ITEMS * sizeof(char *));
      
      for (int i = 0; i < MAX_ITEMS; i++)
      {
        juga->items[i] = (char *)malloc(Max * sizeof(char));
      }
      char *token = strtok(line, ",");
      
      if (token != NULL)
      {
        strcpy(juga->nombre, token);
      }
      token = strtok(NULL, ",");
      
      if (token != NULL)
      {
        juga->pHabilidad = atoi(token);
      }
      token = strtok(NULL, ",");
      
      if (token != NULL)
      {
        juga->item = atoi(token);
      }

      int j = 0;
      
      while ((token = strtok(NULL, ",")) != NULL && j < MAX_ITEMS)
      {
        strcpy(juga->items[j], token);
        j++;
      }
      insertMap(jugador, juga->nombre, juga);
    }
    fclose(ju);
  }
}

void menu(HashMap *jugadores)
{
  int opcion;
  char nombre[Max];
  int pHabilidad;
  char nombreItem[Max];
  char nombreArc[Max];
      
  printf("Menú\n");
  puts("================================================================");
  printf("\t1.- Crear jugador\n");
  printf("\t2.- Mostrar jugador\n");
  printf("\t3.- Agregar item a jugador\n");
  printf("\t4.- Eliminar item de jugador\n");
  printf("\t5.- Agregar puntos de habilidad al jugador\n");
  printf("\t6.- Mostrar jugadores con item específico\n");
  printf("\t7.- Deshacer última acción\n");
  printf("\t8.- Exportar datos de jugadores a archivo de texto\n");
  printf("\t9.- Cargar datos de jugadores desde un archivo de texto\n");
  puts("================================================================");
  printf("\nPor favor, ingrese el número de opción que desea seleccionar:\n");
	scanf("%d", &opcion);

  if(opcion == 1)
  {
    opcion1(jugadores);
  }
  
  if(opcion == 2)
  {
    getchar();
  	printf("\nIngrese el nombre del jugador: ");
    scanf("%[^\n]s", nombre);
    
    opcion2(nombre, jugadores);
  }
  
  if(opcion == 3)
  {
    int cantItem;
    
    getchar();
    printf("\nIngrese el nombre del jugador: ");
    scanf("%[^\n]s", nombre);
  
    printf("\nIngrese la cantidad de items que desea agregar: ");
    scanf("%d", &cantItem);
  
    getchar();
  
    for(int i = 0; i < cantItem; i++)
    {
      printf("\nIngrese el item %d que desea agregar: ", i+1);
      scanf("%[^\n]s", nombreItem);
      
      opcion3(nombre, nombreItem, jugadores, cantItem);
      getchar();
    }
  }
  
  if(opcion == 4)
  {
    getchar();
  	printf("\nIngrese el nombre del jugador: ");
    scanf("%[^\n]s", nombre);
    
    getchar();
    printf("\nIngrese item que desea eliminar: ");
    scanf("%[^\n]s", nombreItem);
    
    opcion4(nombre, nombreItem, jugadores);    
  }
  
  if(opcion == 5)
  {
    getchar();
  	printf("\nIngrese el nombre del jugador: ");
    scanf("%[^\n]s", nombre);
    
    printf("\nIngrese puntos de habilidad que desea agregar: ");
    scanf("%i", &pHabilidad);
    
    opcion5(nombre, pHabilidad, jugadores);
  }
  
  if(opcion == 6)
  {
    getchar();
  	printf("\nIngrese item: ");
    scanf("%[^\n]s", nombreItem);
    
    opcion6(nombreItem, jugadores);
  }
  
  if(opcion == 7)
  {
    getchar();
  	printf("\nIngrese el nombre del jugador: ");
    scanf("%[^\n]s", nombre);
    getchar();

    opcion7(nombre,jugadores);
  }
  
  if(opcion == 8)
  {
    opcion8(jugadores);
  }

  if(opcion == 9)
  {
    getchar();
  	printf("\nIngrese nombre del archivo: ");
    scanf("%[^\n]s", nombreArc);
    getchar();

    opcion9(jugadores, nombreArc);
  }
}

int main()
{
  HashMap *jugadores = createMap(100000);
  
  menu(jugadores);
  
  while(1)
  {
    char neg[3] = "no";
    char opc[3];
    
    printf("\n¿Desea realizar alguna otra operacion? si/no\n");
    scanf("%s", opc);
    getchar();
      
    if(strcmp(opc, neg) == 0)
    {
      free(jugadores); //se libera memoria
      printf("\nEsperamos verte de nuevo por aquí.");
      break;
    }
    printf("\n");
    menu(jugadores);
  }
  return 0;
}