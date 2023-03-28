//1 a) Write a program to create a child process and print the process ids of the parent and child processes.  
#include<unistd.h>
#include<stdio.h>
#include <string.h> 

int main(){
  int pid;
  pid = fork();
  if (pid==0){
    printf("Child process pid: %d\n",getpid());
  }else{
    printf("Parent process pid: %d\n",getpid());
  }
  return 0;
}
