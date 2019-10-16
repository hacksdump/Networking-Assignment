/* Author: Harshit Maurya
 * Enrollment No: 17114037
 * Course: CSN-361
 *
 * Write a C program to find the host name and the IP address of your computer.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <string.h>

void checkHostName(int hostname)
{
    if (hostname == -1)
    {
        perror("gethostname");
        exit(1);
    }
}

void checkHostEntry(struct hostent *hostentry)
{
    if (hostentry == NULL)
    {
        perror("gethostbyname");
        exit(1);
    }
}

int main()
{
    char hostbuffer[256];
    struct hostent *host_entry;
    int hostname;

    hostname = gethostname(hostbuffer, sizeof(hostbuffer));
    checkHostName(hostname);

    host_entry = gethostbyname(hostbuffer);
    checkHostEntry(host_entry);

    struct ifaddrs *id, *tmp_addr;
    getifaddrs(&id);
    tmp_addr = id;
    char *host_IP = "IP address not found";
    while (tmp_addr)
    {
        if (tmp_addr->ifa_addr && tmp_addr->ifa_addr->sa_family == AF_INET && strcmp(tmp_addr->ifa_name, "lo") != 0)
        {
            struct sockaddr_in *pAddr = (struct sockaddr_in *)tmp_addr->ifa_addr;
            host_IP = inet_ntoa(pAddr->sin_addr);
            break;
        }
        tmp_addr = tmp_addr->ifa_next;
    }

    printf("Hostname: %s\n", hostbuffer);
    printf("Host IP: %s\n", host_IP);
    return 0;
}