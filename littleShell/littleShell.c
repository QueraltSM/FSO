#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <string.h>

void  parse(char *line, char **argv)
{
     while (*line != '\0') {       /* if not the end of line ....... */ 
          while (*line == ' ' || *line == '\t' || *line == '\n'){
               *line++ = '\0';     /* replace white spaces with 0    */
		  }
          *argv++ = line;          /* save the argument position     */
          while (*line != '\0' && *line != ' ' && 
                 *line != '\t' && *line != '\n'){
               line++;             /* skip the argument until ...    */
		  }
     }
     *argv = '\0';                 /* mark the end of argument list  */
}

int main (){
	pid_t pidHijo;
	int status;
	char buffer [512];
	buffer[0] = '\0';
	char* tokens[64];
	printf("Ha entrado en My Little Shell, recuerde que este es un shell limitado \ny algunas llamadas al sistema no funcionaran.\n");
	while(1){
		printf("$-");
		//Obtenemos el comando que hemos escrito
		gets(buffer);

		// EXTRA: MAYUSCULAS
		int i = 0;
		while (buffer[i]!='\0') {
			if (buffer[i]>='A' && buffer[i]<='Z') {
				buffer[i] += 'a' - 'A';
			}
			i++;
		}

		parse(buffer, tokens);
		//En caso de escribir exit, salimos del shell
		if(strncmp(buffer,"exit",4) == 0){
			exit(getpid());
		}
		
		if ((pidHijo = fork()) < 0) {     
		      printf("No se pudo hacer el fork\n");
		      exit(1);
		 }else{
			 if (pidHijo == 0) {          
				//Ejecutamos el comando escrito
		     	if (execvp(*tokens, tokens) < 0) {     
		           printf("No se pudo hacer el execvp\n");
		           exit(1);
		      	}
		 	}else{                                  
		    	while (wait(&status) != pidHijo){
		       		/*El padre espera a que el hijo termine*/
		    	}
			}
		 }
	}
}

