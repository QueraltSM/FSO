#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

	int f1; 
	int f2;

	char buffer[1024]; 
	char buffer2[1024];

	int update = 0;	

	int i, j = 1;

	int iflag, lflag, c, err, jump1, jump2 = 0;

	extern char *optarg;
	char *iname;
	int l, m, count, repeted = 0;


int main(int argc, char** argv){
		while((c = getopt(argc, argv, "i:l")) != -1){
		switch(c){
			case 'i':
				iflag = 1;
				iname = optarg;
				
				if (lflag == 0) {
					j = 3;
					
				} else {
					j = 4;
				}
				break;

			case 'l':
				lflag = 1;
				if (iflag == 0) {
					j = 2;
				} else {
					j = 4;
				}
				break;

			case '?':
				err = 1;
				break;
		}
	}

		if(err == 1){
		printf("%s\n", "ERROR: Invalid argument.\n\n");
		exit(0);
	}


	if(argc < 3){
		printf("%s\n", "ERROR: Insufficient arguments.\n\n");
		exit(0);
	}


	for(i = j;i< argc;i++){
		f1 = open(argv[i], O_RDONLY);
		f2 = open(argv[i+1], O_RDONLY);
		update = i+1;

		if (f1 == -1 && f2 == -1) {
			printf("%s and %s do not exist.\n\n", argv[i], argv[update]);
		} else if(f1 == -1){
			printf("%s does not exist.\n\n", argv[i]);
		} else if(f2 == -1){
			printf("%s does not exist.\n\n", argv[update]);
		} else {

		if (iflag == 0 && lflag == 0){
			int equal = 1; 	
		while(read(f1, &buffer, sizeof(char) ) == 1 && read(f2, &buffer2, sizeof(char)) == 1){
			if(*buffer != *buffer2){
				equal = 0;
				printf("%s and %s have different content.\n\n", argv[i], argv[update]);
				break;
			}
		}
		if(equal == 1 && f1 != -1 && f2 != -1) printf("%s and %s have equal content.\n\n", argv[i], argv[update]);


			} else if (lflag == 1 && iflag == 0) {

				size_t a = read(f1, buffer, 1024);
				size_t b = read(f2, buffer2, 1024);

		while (buffer[l] != '\0' || buffer2[m] != '\0'){
			if(buffer[l] != buffer2[m]){
				if (repeted == 0) {
					printf("Different content, bytes in which they differ: \n");
					repeted++;
				}

				printf("Position = %d File = %s Character = %c\n",l, argv[i], buffer[l]);
				printf("Position = %d File = %s Character = %c\n\n",m, argv[update], buffer2[m]);
				
			} else{
				count++;
			}
			l++;
			m++;
		}

		if(count == a) printf("%s and %s have equal content.\n\n", argv[i], argv[update]);

			} else if (iflag == 1 && lflag == 0) {
				jump(iname);
				lseek(f1, jump1, SEEK_SET);
				lseek(f2, jump2, SEEK_SET);

				l = jump1;
				m = jump2;

				size_t a = read(f1, buffer, 1024);
				size_t b = read(f2, buffer2, 1024);

				if (jump1 > a || jump2 > b){
					printf("ERROR\n\n");
					exit(1);
				}

				while (buffer[l] != '\0' || buffer2[m] != '\0'){
					if(buffer[l] !=  buffer2[m]){
						if (repeted == 0) {
							printf("%s and %s have different content.\n\n", argv[i], argv[update]);
							repeted++;
						}
						
					} else{
					count++;
				}
			l++;
			m++;
		}
			if(count == a) printf("%s and %s have equal content.\n\n",argv[i], argv[update]);
			

			} else if (iflag == 1 && lflag == 1) {
				jump(iname);
				lseek(f1, jump1, SEEK_SET);
				lseek(f2, jump2, SEEK_SET);

				l = jump1;
				m = jump2;

				size_t a = read(f1, buffer, 1024);
				size_t b = read(f2, buffer2, 1024);


				if (jump1 > a || jump2 > b){
					printf("ERROR\n\n");
					exit(1);
				}

				size_t d;
				d = a;

				while (a > 0 && b > 0){
					if(buffer[l] !=  buffer2[m]){
					if (repeted == 0) {
							printf("Different content, bytes in which they differ: \n");
							repeted++;
						}
						printf("Position = %d File = %s Character = %c\n",l, argv[i], buffer[l]);
						printf("Position = %d File = %s Character = %c\n\n",m, argv[update], buffer2[m]);
				

				} else{
					count++;
				}
					a--;
					b--;
					l++;
					m++;
				}

		if(count == d) printf("%s and %s have equal content.\n\n", argv[i], argv[update]);

			}
		}

		i = update;
		l = 0;
		m = 0;
		count = 0;
		repeted = 0;
		close(f1);
		close(f2);
	}
	return 0;	
}

jump(char* s){
		char* s1 = malloc(strlen(iname)+1);
		char* s2 = malloc(strlen(iname)+1);
		char* c = s1;
		char* f = s2;
		while (*iname != ':') (*s1++) = (*iname++);
    	*s1 = '\0';
		(*iname++);

		while(*iname!='\0') (*s2++) = (*iname++);
		*s2 = '\0';

		char aux1 = c;
		char aux2 = f;

		jump1 = atoi(c);
		jump2 = atoi(f);
}
