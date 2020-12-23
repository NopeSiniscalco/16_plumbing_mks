#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

char * capitalize(char * in_args){
	int i;
	for(i=0; i<strlen(in_args); i++) {
        if(in_args[i]=='\n')
            in_args[i]=0;
		else if(in_args[i]>=97 && in_args[i]<=122)
			in_args[i]=in_args[i]-32;
	}

	return in_args;
}

int main(){
	mkfifo("to_processor",0644);
	mkfifo("to_console",0644);

	int out_fd,in_fd;
	out_fd=open("to_console", O_WRONLY);
	in_fd=open("to_processor", O_RDONLY);
	printf("Pipe Opened:\n");
    //write(out_fd,"BRUHH",6);


	while(1) {
		char line[100];
		read(in_fd,line,sizeof(line));
		printf("\nRecieved:%s ...\n", line);
        capitalize(line);
		write(out_fd,line,sizeof(line));
	}

    close(out_fd);
    close(in_fd);
	return 0;

}
