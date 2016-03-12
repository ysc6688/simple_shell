#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#define MAXSIZE 256
#define ARGVSIZE 10

int main()
{
    printf("yscSH >> ");
    char cmd[MAXSIZE];
    
    while( fgets(cmd,MAXSIZE,stdin) != NULL)
    {
        cmd[strlen(cmd) - 1] = 0;  /* remove '\n' */
        int argc = 0;
        char* argv[ARGVSIZE] = { NULL };
        char *p;
        if(strcmp(cmd,"\n") != 0){
            p = strtok(cmd," ");
            argv[argc++] = p;
            while( (p = strtok(NULL," ")) ) {
                argv[argc++] = p;
            } 

            if(strcmp(argv[0],"exit") == 0) exit(0);

            pid_t pid;
            if( (pid = fork()) < 0 ) {
                fprintf(stderr, "fork error!\n");
                exit(-1);
            }
            else if(pid == 0) { /* child process */
                if( execvp(argv[0], argv) < 0 )
                    printf("command %s not found!\n",argv[0]);
                exit(0);
            }
            else {  /* father process */
                wait(0);
            }
            
        }
        printf("yscSH >> ");
    }
    return 0;
}
