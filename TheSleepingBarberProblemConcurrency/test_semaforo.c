// Test simple de la API de semáforos

#include "semaforo.h"

Semaforo sem, semPadre;

void* UnHilo (void* arg)
{
  puts("HILO 1. Voy a bloquearme en un semáforo");
  WAIT(&sem);
  puts("HILO 1. Alguien me ha desbloqueado");
  sleep(1);
  puts("HILO 1. Hago un signal para avisar al main");
  SIGNAL(&semPadre);
  puts("HILO 1. Terminé");
}

void* OtroHilo (void* arg)
{
  puts("--hilo 2. Realizo una pausa de 2 segundos...");
  sleep(2);
  puts("--hilo 2. Hago un signal para despertar al hilo 1");
  SIGNAL(&sem);
  puts("--hilo 2. Hago un signal para avisar al main");
  SIGNAL(&semPadre);
  puts("--hilo 2. Terminé");
}

int main()
{
  pthread_t unhilo, otrohilo;
  void* dummy;
  
  INICIASEM(&sem,0);
  INICIASEM(&semPadre,0);
  
  pthread_create(&unhilo, NULL, UnHilo, NULL);
  pthread_create(&otrohilo, NULL, OtroHilo, NULL);
  
  puts("main: espero a que acaben los hilos");
  WAIT(&semPadre);
  WAIT(&semPadre);
  puts("main: los dos hilos han acabado");
}
