// Programa de prueba de la BD simulada
// Es una prueba simple, secuencial.
// La prueba concurrente está en test_pthreads.c

#include "recurso.h"
#include <stdio.h>

void test_recurso()
{
  char* str;
  recurso_escribir("hola mundo");
  str = recurso_leer();
  printf("He leído: %s\n",str);
  free(str);
}

main()
{
  printf("Prueba de acceso secuencial al recurso...\n");
  recurso_inicializa();
  test_recurso();
  printf("Prueba terminada\n");
}

