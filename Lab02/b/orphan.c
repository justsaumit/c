//2 b) Write a program, to create an orphan process and print the process ids
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid;
    pid = fork(); 

    if (pid == -1) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {  // Child process
        printf("Child process ID: %d\n", getpid());
        printf("Parent process ID: %d\n", getppid());
        sleep(5);  // wait for 5 seconds
        printf("Child ppid after orphan: %d\n", getppid());
    } else {  // Parent process
        printf("Parent process ID: %d\n", getpid());
        exit(0);
    }
    return 0;
}
