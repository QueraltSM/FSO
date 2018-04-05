#include <stdio.h>
#include "mistring.h"
#include "mistring.c"
#ifndef TEST
#endif
#include <assert.h>
#ifdef TEST
#define mi_strlen strlen
#define mi_strcpy strcpy
#define mi_strdup strdup
#define mi_strcat strcat
#define mi_strequals strequals
#endif
#define DebeSerCierto(x) assert(x)
#define DebeSerFalso(x) assert(!(x))

void INICIO_TEST (const char* titulo_test)
{
    printf("- batería de pruebas para %s: ", titulo_test);
    fflush(stdout);
}

void FIN_TEST (const char* titulo_test)
{
     printf ("hecho\n");
}

void test_mi_strlen()
{
      char* s1 = "Big";
      char s2[4];

      char cadena_1000 [1000];
      int i;
      #define LONGITUD_TEST 500
      for (i=0; i<LONGITUD_TEST; i++)
      {
        cadena_1000[i] = 32+(rand()%96);
      }
      cadena_1000[LONGITUD_TEST] = '\0';

   
      INICIO_TEST("mi_strlen");
      DebeSerCierto(mi_strlen("Hello World!") == 12);
      DebeSerCierto(mi_strlen(cadena_1000) == LONGITUD_TEST);
      DebeSerCierto(mi_strlen(mi_strcpy(s2, s1)) == 3);
      DebeSerCierto(mi_strlen(mi_strdup("Programming in C")) == 16);
      DebeSerFalso(mi_strlen(mi_strdup("")) != 0);
      DebeSerCierto(mi_strlen(mi_strdup("00"))==2);
      FIN_TEST("mi_strlen");
}


void test_mi_strcpy()
{
      char* s3 = "Play";
      char s4[5];

      char* s5 = "";
      char s6[1];
        
      char* resultado = mi_strcpy(s4,s3);
     

      INICIO_TEST("mi_strcpy");
      DebeSerFalso(mi_strlen(resultado)!=4);
      DebeSerCierto(mi_strequals(mi_strcpy(s4, s3), "Play"));
      DebeSerCierto(mi_strequals(mi_strcpy(s6,s5), ""));
      DebeSerCierto(mi_strequals(mi_strcat(mi_strcpy(s4, s3), s5), "Play"));
      FIN_TEST("mi_strcpy");
}



void test_mi_strcat()
{

      char cadena1[15] = { 'h','o','l','a', '\0' };
      char* resultado = mi_strcat(cadena1," mundo");
    
      char s1[6] = { 'A','B', '\0' };
      char* s2 = mi_strcat(s1,"BA");
    
      char* s3 = "la";
      char s4[3];

     INICIO_TEST("mi_strcat");
     DebeSerCierto(cadena1 == resultado);
     DebeSerCierto(mi_strlen(cadena1)==10);
     DebeSerCierto(mi_strequals(cadena1,"hola mundo"));
     DebeSerFalso(mi_strequals(cadena1,"hola"));
     DebeSerCierto(mi_strequals(s2, "ABBA"));
     DebeSerCierto(mi_strequals(mi_strcat(mi_strdup(s3), mi_strcpy(s4,s3)), "lala"));
     FIN_TEST("mi_strcat");
}


void test_mi_strdup()
{
    char* s1 = "C";
    char* s2 = "10";
    char s3[3];
    
    char* resultado = mi_strdup(mi_strcpy(s3, s1));

    INICIO_TEST("mi_strdup");
    DebeSerCierto(mi_strequals(mi_strdup("Jungle"), "Jungle"));
    DebeSerCierto(mi_strequals(mi_strcat(mi_strdup(s1), "++"), "C++"));
    DebeSerFalso(!mi_strequals(mi_strcpy(s3, mi_strdup(s2)),"10"));
    DebeSerCierto(mi_strequals(mi_strdup("1010"), "1010\0"));
    DebeSerCierto(mi_strequals(resultado, "C"));
    DebeSerFalso(mi_strlen(resultado)!=1);
    FIN_TEST("mi_strdup");
}

void test_mi_strequals()
{
    char* s1 = "";
    char s2[1];

    char* s3 = "Music";
    char* s4 = "Music\0";

    INICIO_TEST("mi_strequals");
    DebeSerCierto(mi_strequals("clouds", "clouds"));
    DebeSerCierto(mi_strequals(mi_strcpy(s2,s1), ""));
    DebeSerCierto(mi_strequals("A\0", "A"));
    DebeSerCierto(mi_strequals(mi_strdup(s3), mi_strdup(s4)));
    FIN_TEST("mi_strequals");
}

void ejecuta_tests ()
{
     test_mi_strlen();
     test_mi_strcpy();
     test_mi_strcat();
     test_mi_strdup();
     test_mi_strequals();
}

int main()
{
    puts("Iniciando tests...");
    ejecuta_tests();
    puts("Batería de test completa.");
}
