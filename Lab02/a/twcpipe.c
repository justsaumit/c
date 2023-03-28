//2 a) Write a program, to demonstrate two way communications between parent and child using 
PIPE.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 100
int main()
{
    int fd1[2],fd2[2];
    char buffer[BUF_SIZE];
    pid_t pid;

    if (pipe(fd1) == -1){ // 1st pipe is created
        perror("pipe1");
        exit(1);
    }

    if (pipe(fd2) == -1){ // 2nd pipe is created
        perror("pipe2");
        exit(1);
    }

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {     // child process
        close(fd1[1]);  // close unused write end of the pipe1
        close(fd2[0]);  // close unused read end of the pipe2
        // Read from the pipe
        read(fd1[0],buffer,BUF_SIZE); 
        printf("Message from Parent is: %s",buffer);
        printf("Enter message for Parent: ");
        fgets(buffer, BUF_SIZE , stdin);
        write(fd2[1], buffer, strlen(buffer)+1); 
        close(fd1[0]);
        close(fd2[1]);
    }else{
        close(fd1[0]);  // close unused read end of the pipe1
        close(fd2[1]);  // close unused write end of the pipe2
        printf("Enter message for Child: ");
        fgets(buffer, BUF_SIZE , stdin);
        write(fd1[1], buffer, strlen(buffer)+1); 
        read(fd2[0],buffer,BUF_SIZE); 
        printf("Message from Child is: %s",buffer);
        close(fd1[1]);
        close(fd2[0]);
    }
    return 0;
}
