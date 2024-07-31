#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
    pid_t p = fork();

    switch(p) {
        case -1:
            return 1;
        case 0:
            exit(0);
        default:
            sleep(10);
    }

    return 0;
}
