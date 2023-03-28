//1 b) Write a program to create a child process and send a message from parent to child using PIPE.
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 

#define BUF_SIZE 10

int main(){ 
    int fd[2]; //array fd of size 2, 0 - read end of pipe, 1 - writeend of pipe
    char buffer[BUF_SIZE];
    int result;
    pid_t pid;

    //Creating a pipe 
    result = pipe (fd); 
    if (result < 0) {  //failure in creating a pipe 
        perror("pipe"); 
        exit (1); 
    }

    //Creating a child process 
    pid = fork(); 
    if (pid < 0) {          //failure in creating a child 
        perror ("fork"); 
        exit(2); 
    } else if (pid == 0) {  //Child process 
        read(fd[0],buffer,BUF_SIZE); //reads upto 100bytes
        printf("Message from parent is: %s",buffer);
        close(fd[0]);       //close read end of pipe
    } else{                 //Parent Process
        close(fd[0]);       //close read end of pipe
        printf("Enter message for the child: ");
        fgets(buffer, BUF_SIZE , stdin); //The fgets() function reads input from a stdin stream, and stores it in the buffer.
        write(fd[1], buffer, strlen(buffer)+1); //write data to the pipe +1 for NULL Terminator
        close(fd[1]);       //close write end of pipe
        // Exit the parent process
        exit(0);
    }
  }
