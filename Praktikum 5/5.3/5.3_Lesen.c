#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_SIZE 20

int main() {
    key_t key = ftok("/tmp", 'A');  // Erzeugung eines Schlüssels
    int shmid = shmget(key, SHM_SIZE, 0666);  // Zugriff auf das Shared-Memory-Segment

    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    char *shmaddr = shmat(shmid, NULL, 0);  // Attach des Shared-Memory-Segments

    if (shmaddr == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    // Lesen und Ausgeben der ASCII-Zeichen aus dem Shared-Memory-Segment
    printf("Data read from shared memory: ");
    for (int i = 0; i < SHM_SIZE; i++) {
        printf("%c", shmaddr[i]);
    }
    printf("\n");

    // Detach des Shared-Memory-Segments
    if (shmdt(shmaddr) == -1) {
        perror("shmdt");
        exit(1);
    }

    return 0;
}
