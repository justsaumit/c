#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>

#define SHM_SIZE 100

int main() {
    void *shm;
    int shmid;
    key_t key;

    // generate the same unique key as the writer
    key = ftok(".", 'S');

    // get the shared memory segment
    shmid = shmget(key, SHM_SIZE, 0666);
    if (shmid == -1) {
        perror("Error getting shared memory segment");
        exit(1);
    }

    // attach the shared memory segment to the reader's address space
    shm = shmat(shmid, NULL, 0);
    if (shm == (char *) -1) {
        perror("Error attaching shared memory segment");
        exit(1);
    }
    printf("Message received from shared memory segment: %s", shm);

    // detach the shared memory segment from the reader's address space
    if (shmdt(shm) == -1) {
        perror("Error detaching shared memory segment");
        exit(1);
    }

    // remove the shared memory segment
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("Error removing shared memory segment");
        exit(1);
    }

    return 0;
}
