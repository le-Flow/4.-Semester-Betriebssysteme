#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main( void ) {
    int status;
    int procId;
    procId = fork();
    switch(procId){
        case -1:
            break;
        case 0:
             //Kindprozess
            printf("PID von Kind: %d\n", getpid());
            execlp("ps","ps","xlf",NULL);
            break;
        default:
             //Vaterprozess
            wait(&status);
            printf("CTRL+C zum Beenden druecken\n");
            while(1);
            break;
    }
    return EXIT_SUCCESS;
}
