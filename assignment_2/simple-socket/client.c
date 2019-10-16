/**
 * @file client.c
 * @author Harshit Maurya (hmaurya999@gmail.com)
 * @brief Simple text-based TCP client.
 * @version 0.1
 * @date 2019-08-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define HOST "127.0.0.1"
#define PORT 8080

int main(int argc, char const *argv[])
{
    /// Socket file descriptor
    int sock = 0;
    /// Stored read buffer from server
    int valread;
    /// Stores server address parameters like host and port
    struct sockaddr_in serv_addr;
    /// Default connection message sent to server
    char *hello = "Hello from client";
    /// Buffer to hold read message
    char buffer[1024] = {0};
    const char *host = HOST;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Socket creation error\n");
        return -1;
    }
    serv_addr.sin_family = AF_INET;
    /// If host and port are passed as command-line args
    if (argc == 3)
    {
        host = argv[1];
        serv_addr.sin_port = htons(atoi(argv[2]));
    }
    else
    {
        serv_addr.sin_port = htons(PORT);
    }

    /// inet_pton() converts internet address from text to binary using host and port
    if (inet_pton(AF_INET, host, &serv_addr.sin_addr) <= 0)
    {
        printf("Invalid address / Address not supported");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("Connection failed\n");
        return -1;
    }
    send(sock, hello, strlen(hello), 0);
    printf("Hello message sent\n");
    valread = read(sock, buffer, 1024);
    printf("Server: %s\n", buffer);
    return 0;
}