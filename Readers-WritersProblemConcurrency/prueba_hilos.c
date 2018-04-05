// Ejemplo sencillo de dos hilos que se ejecutan de forma concurrente.
// Compilar con la biblioteca pthreads. Ejemplo:
// 	cc prueba_hilos.c -o hilos -lpthread
//

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// Objetos de tipo hilo
pthread_t un_hilo;
pthread_t otro_hilo;

// Las funciones que ejecutan los hilos SIEMPRE deben respetar ese formato:
// void* nombre_de_funcion (void*);

// Rutina que ejecutará uno de los hilos
void* rutina1 ( void* arg )
{
  int i;
  for (i=1; i<=100;i++)
  {
    printf("*** soy el HILO 1");
  }
  puts("*** HILO1 - the end");
  return NULL;
}

// Rutina que ejecutará el otro hilo
void* rutina2 ( void* arg )
{
  int i;
  for (i=1; i<=100;i++)
  {
    printf("@@@ soy el HILO 2");
  }
  puts("@@@ HILO2 - the end");
  return NULL;
}

// Aquí empieza el programa
int main()
{
  // Lanzo un hilo que ejecuta: rutina1(NULL)
  pthread_create ( &un_hilo, NULL, rutina1, NULL); 
 
  // Lanzo otro hilo que ejecuta: rutina2(NULL)
  pthread_create ( &otro_hilo, NULL, rutina2, NULL); 
  
  // El main() espera a que acaben los dos hilos.
  // Si no hacemos pthread_join(), el programa finaliza sin que 
  // los hilos hayan acabado.
  // La variable dummy no la usamos en este ejemplo.
  void* dummy;
  pthread_join ( un_hilo, &dummy );
  pthread_join ( otro_hilo, &dummy );

  exit(0);
}








