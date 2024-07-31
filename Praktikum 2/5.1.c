#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main (void) {
    pid_t p = fork();

    switch(p) {
        case -1:
            return 1;
        case 0:
            printf("Kind:\nIch bin %d\n", getpid());
            printf("Mein Papa ist %d\n", getppid());
            printf("2s schlafen\n");
            sleep(2);
            printf("Mein Papa ist %d\n", getppid());
            exit(0);
        default:
            printf("Papa:\nIch bin %d\n1s schlafen\n", getpid());
            sleep(1);
            printf("Tschuess!\n");
            exit(0);
    }

    return 0;
}
