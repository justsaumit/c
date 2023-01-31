//Program 1: Program for IPC using Message Queues To send data to a message queue

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#define MAX_TEXT 512   //maximum length of the message that can be sent allowed

//message must have defined structure smaller than system limit
//must start with long int and another variable character array some_text to store the message
//written into the message queue
//So whagtever data the user will type
//to send will be first read into a buffer
//and then copied into ths variable 
//to be then finally written into the message queue using the
//message queue function
//
struct my_msg{
        long int msg_type;
        char some_text[MAX_TEXT];
};
int main()
{
        int running=1; //while loop true
        int msgid;     
        struct my_msg some_data;
        char buffer[50]; //array to store user input
        msgid=msgget((key_t)12345,0666|IPC_CREAT); //message queue with key 12345 and permissions to read write from user, group and all users
        //will return a positive number is successfully created
        if (msgid == -1) // -1 means the message queue is not created
        {
                printf("Error in creating queue\n");
                exit(0);
        }

        while(running) //while true
        {
                printf("Enter some text:\n");
                fgets(buffer,50,stdin); //fgets to temp store in buffer + how much data read+ from where? only 50 char
                some_data.msg_type=1;   //somedata variable we assign value 1 and used in reciever progrsm
                strcpy(some_data.some_text,buffer); //copy from buffer to var
                if(msgsnd(msgid,(void *)&some_data, MAX_TEXT,0)==-1) // msgsnd returns -1 if the message is not sent
                //msgsnd function will take 4 parameters msgid identitifer from msget pointer to the nesssage, max size of 50 that is to be send, control if message queue is full if 0 it will be suspended until cleared out
                {
                        printf("Msg not sent\n");
                }

                if(strncmp(buffer,"end",3)==0)
                //we use string compare function to stop the while loop if the buffer has reached it's last character if use says "end" then it means user wishes to stop sending data, 3 prolly the chars in end
                {
                        running=0;
                }
        }
}
