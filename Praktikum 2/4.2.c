#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();
    if (pid == 0) { // Child process
        printf("Ich habe die Prozessnummer %d\n", getpid());
        printf("Papa hat die Nummer %d\n", getppid());
    } else if (pid > 0) { // Parent process
        int wstatus;
        wait(&wstatus); // Wait for the child process to finish
        printf("Elternprozess (Papa) hat die Prozessnummer %d\n", getpid());
    } else {
        // Fork failed
        perror("Fork failed");
        return 1;
    }
    
    return 0;
}
