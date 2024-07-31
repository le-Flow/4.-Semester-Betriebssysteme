#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    key_t key = ftok("/tmp", 'A');  // Erzeugung eines Schlüssels
    int shmid = shmget(key, 0, 0666);  // Zugriff auf das Shared-Memory-Segment

    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Löschen des Shared-Memory-Segments
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(1);
    }

    printf("Shared memory segment deleted.\n");

    return 0;
}
