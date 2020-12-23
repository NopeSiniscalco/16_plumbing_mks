#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <time.h>

int main(){
    mkfifo("to_processor",0644);
	mkfifo("to_console",0644);

	int out_fd,in_fd;
	in_fd=open("to_console", O_RDONLY);
	out_fd=open("to_processor", O_WRONLY);
    printf("Pipe Opened:\n");
    //char testtest[6];
    //read(in_fd,testtest,6);
    //printf("%s\n",testtest);


	while(1) {
        char line[100];
		//read(STDIN_FILENO,line,sizeof(line));
        fgets(line,sizeof(line),stdin);
		write(out_fd,line,sizeof(line));
        char line2[100];
		read(in_fd,line2,sizeof(line2));
        printf("\nRecieved:[%s]\n", line2);
	}

    close(out_fd);
    close(in_fd);
	return 0;
}
