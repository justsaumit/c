# The fork () System Call 
   
System call fork() is the only way in Unix to create a new process.
The speciality of this function is that it is called _once_ but it returns _twice_.
It return once in the caller process(called the parent) with a return value that is the process ID of the newly created process(called the child).
It also returns once in the child, with a return value of 0.
Hence, the return value tells the process whether it is the parent or the child.

In order to distinguish the parent from the child, we can check the returned value of fork(): 
1. If fork() returns a negative value, the creation of a child process was unsuccessful. 
2. fork() returns a zero to the newly created child process. 
3. fork() returns a positive value, the process ID of the child process, to the parent.


The reason **fork** returns 0 to to the newly created child process, instead of the parent's process ID, is because a child only has one parent and it can always obtain the parent's process ID, by calling **getppid**.
A parent, on the other hand, can have any number of children, and there is no way to obrain the process IDs of its children.
If a parent wants to keep track of the process IDs of all it's children, it must record the return values from **fork**. 

The returned process ID is of type _pid_t_ defined in **sys/types.h**. 

All descriptors open in theparent before the call to **fork** are shared with the child after **fork** returns.
This is used by network servers where: The parent calls **accept** and then calls **fork**. The connected socket is then shared between the parent and the child.
Normally, the child then reads and writes the connected socket and the parent closes the connected socket.

There are two typical uses of fork:
1. A process makes a copy of itself so that one copy can handle one peration while the other copy does another task. This is typical for network servers.
2. A process wants to execute another program. Since the only way to create a new process is by calling **fork**, the process first calls **fork** to make a copy of itself, and the one of the copies(typically the child process) calls the **exec**(next) to replace itself with the new program.
