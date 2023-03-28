//5 Write a reader and a writer program to send the message from writer to reader using shared memory.
///writer
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>

#define SHM_SIZE 100

int main() {
    int shmid;
    key_t key;
    char *shm;

    // generate a unique key for the shared memory segment
    key = ftok(".", 'S');

    // create or get the shared memory segment
    shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("Error creating shared memory segment");
        exit(EXIT_FAILURE);
    }

    // attach the shared memory segment to the writer's address space
    shm = (char *) shmat(shmid, NULL, 0);
    if (shm == (char *) -1) {
        perror("Error attaching shared memory segment");
        exit(EXIT_FAILURE);
    }

    // get input from the user
    printf("Enter a message to send: ");
    fgets(shm, SHM_SIZE, stdin);

    printf("Message sent to shared memory segment\n");

    // detach the shared memory segment from the writer's address space
    if (shmdt(shm) == -1) {
        perror("Error detaching shared memory segment");
        exit(EXIT_FAILURE);
    }

    return 0;
}
