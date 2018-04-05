// Prueba concurrente de acceso a la BD simulada
// Se lanzan unos hilos lectores y unos hilos escritores
// Al no haber sincronización entre los hilos,
// el resultado es que la BD se corrompe

#include "semaforo.h"
#include "semaforo.c"
#include "recurso.h"
#include "recurso.c"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

Semaforo mutex, writeblock;
int data = 0,rcount = 0;


void* lector (void* arg){
  int f;
  f = ((int) arg);
  WAIT(&writeblock);
  data++;

    int i;
    unsigned id_hilo = (unsigned)pthread_self();
    // Lee diez veces de la BD
    for (i=0;i<10;i++) 
    {
        char* str = recurso_leer();
        // imprime la cadena leída y el ID del hilo
        printf("<<< Leí    (%u) <<< %s\n", id_hilo, str);
        free(str);
    }

    sleep(1);
    SIGNAL(&writeblock);
    return NULL;
}


void* escritor (void* arg){
  	int f;
  	f = ((int)arg);
  	WAIT(&mutex);
  	rcount = rcount + 1;
  	if (rcount==1)
  		WAIT(&writeblock);
  		SIGNAL(&mutex);
  		

    char* texto = (char*)arg;
    int i;
    // Escribimos la cadena tres veces
    for (i=0;i<3;i++)
    {
        recurso_escribir(texto);
        printf(">>> escribí >>> %s\n",texto);
    }
    
    sleep(1);
    WAIT(&mutex);
  	rcount = rcount - 1;
  	if(rcount==0)
  		SIGNAL(&writeblock);
  		SIGNAL(&mutex);
    return NULL;
}


// Rutina que lanza los hilos y los pone a acceder a la BD
void test_recurso_hilos()
{
    // Cinco lectores, cada uno lee 10 veces
    const int NLECTORES = 5;
    pthread_t lectores[NLECTORES];
    
    // Tres escritores, cada uno escribe 3 veces
    pthread_t escritor1,escritor2,escritor3;
    
    // Textos que escriben los escritores
    const char* texto1 = "-----------------------------------------------";
    const char* texto2 = "En un lugar de la Mancha, de cuyo nombre no quiero acordarme";
    const char* texto3 = "Como una loncha de queso en un sandwich preso";
    
    // Lanzamiento de los hilos
    int lec;
    for (lec=0;lec<NLECTORES;lec++)
    {
        pthread_create(&lectores[lec],NULL,lector,NULL);
    }
    
    pthread_create(&escritor1,NULL,escritor,(void*)texto1);
    pthread_create(&escritor2,NULL,escritor,(void*)texto2);
    pthread_create(&escritor3,NULL,escritor,(void*)texto3);
    
    // Espera por la finalización de todos los hilos
    void* dummy;
    for (lec=0;lec<5;lec++)
    {
        pthread_join(lectores[lec],&dummy);
    }
    pthread_join(escritor1,&dummy);
    pthread_join(escritor2,&dummy);
    pthread_join(escritor3,&dummy);
    
}

int main()
{
	// Inicializamos a 1 los semáforos para garantizar exclusión mutua
	mutex = NEWSEM(1);
	writeblock = NEWSEM(1);
    
    printf("Comienza la prueba de hilos...\n");
    recurso_inicializa();
    test_recurso_hilos();
    printf("Fin de la prueba de hilos\n");
    exit(0);
}
