/**
 * @file zombie.c
 * @author Harshit Maurya (hmaurya999@gmail.com)
 * @brief A C program to demonstrate Orphan Process.  
 * Parent process finishes execution while the 
 * child process is running. The child process 
 * becomes orphan. 
 * @version 0.1
 * @date 2019-08-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t child_pid = fork();
    if (child_pid > 0)
    {
        printf("Parent process started\n");
        sleep(5);
        printf("Parent process finished\n");
    }
    else
    {
        printf("Child process started and terminated\n");
        exit(0);
    }
    return 0;
}
