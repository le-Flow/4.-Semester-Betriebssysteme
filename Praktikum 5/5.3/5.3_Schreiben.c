#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_SIZE 20

int main() {
    key_t key = ftok("/tmp", 'A');  // Erzeugung eines Schlüssels
    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);  // Erzeugung des Shared-Memory-Segments

    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    char *shmaddr = shmat(shmid, NULL, 0);  // Attach des Shared-Memory-Segments

    if (shmaddr == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    // Füllen des Shared-Memory-Segments mit ASCII-Zeichen
    for (int i = 0; i < SHM_SIZE; i++) {
        shmaddr[i] = 'A' + (i % 26);
    }

    printf("Shared memory segment filled with ASCII characters.\n");
    printf("Press any key to detach the shared memory segment and exit...\n");
    getchar();  // Warten auf eine Benutzereingabe

    // Detach des Shared-Memory-Segments
    if (shmdt(shmaddr) == -1) {
        perror("shmdt");
        exit(1);
    }

    return 0;
}
