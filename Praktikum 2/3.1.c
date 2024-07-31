#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
    printf("Ich habe die Prozessnummer %d\n", getpid());
    printf("Papa hat die Nummer %d\n", getppid());

    return 0;
}
