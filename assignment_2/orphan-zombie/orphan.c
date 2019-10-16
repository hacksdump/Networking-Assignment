/**
 * @file orphan.c
 * @author Harshit Maurya (hmaurya999@gmail.com)
 * @brief A C program to demonstrate Zombie Process.  
 * Child becomes Zombie as parent is sleeping 
 * when child process exits. 
 * @version 0.1
 * @date 2019-08-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();
    if (pid > 0)
    {
        printf("In parent process\n");
        printf("Parent process terminated\n");
    }
    else if (pid == 0)
    {
        printf("Started child process\n");
        sleep(5);
        printf("Child process terminated\n");
    }
    return 0;
}
