#include <stdlib.h>
#include <stdio.h>
#include "mistring.h"
#include <malloc.h>

int mi_strlen (char* str)
 {
    int length = 0;
    while (*str != '\0') 
	{
	str++;
	length++;
	}
    return length;
}


char* mi_strcpy (char* s1, char* s2) 
{
    char* aux = s1;
    while (*s2 != '\0') 
	{
       	*s1 = *s2;
         s1++;
	 s2++;
    	}
    *s1 = '\0';
    return aux;
}


char* mi_strcat (char* s1, char* s2)
   {
    char* aux = s1;
    while (*s1 != '\0') s1++;
    while (*s2 != '\0') (*s1++) = (*s2++);
    *s1 = '\0';
    return aux;
}

char* mi_strdup (char* str)
    {

    char* duplicado = malloc(mi_strlen(str)+1);
    if (duplicado == NULL) return NULL;
    mi_strcpy(duplicado, str);
    return duplicado;
}


int mi_strequals (char* s1, char* s2){
   int i = 0;
   int cont = 0;
   if (mi_strlen(s1) != mi_strlen(s2)) {
        return 0;
	} else {
		while (s1[i]) {
			if (s1[i] == s2[i]) {
				cont++;
			}
		i++;
			}
		}
	if (i==cont) {
		return 1;
	}
}
