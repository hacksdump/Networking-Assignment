/**
 * @file server.c
 * @author Harshit Maurya (hmaurya999@gmail.com)
 * @brief Simple text-based TCP server
 * @version 0.1
 * @date 2019-08-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080

/**
 * @brief This method will be used to debug and error to the console
 * and exit the main program.
 * 
 * @param message The message to print along with the default error message.
 */
void raise_error(const char *message)
{
    perror(message);
    exit(EXIT_FAILURE);
}

int main(int argc, char const *argv[])
{
    /// server_fd stores the file descriptor for serving socket.
    int server_fd;

    /// new_socket holds every new connection.
    int new_socket;

    /// valread stores the buffered message from the client.
    int valread;

    /// stores socket address parameters like host and port.
    struct sockaddr_in address;

    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {};

    /// The default reply to the client upon creating a new connection.
    char *connection_reply = "Hello from server";

    /**
     * AF_INET implies the address format for Internet Protocol version 4
     * 
     * SOCK_STREAM is used for TCP communication
     */
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0)
    {
        raise_error("Socket creation failed");
    }

    /**
     * SOL_SOCKET implies the level the request applies to, which in this case is, socket layer.
     * SO_REUSEADDR | SO_REUSEPORT indicates that the local socket address can be reused.
     */
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        raise_error("setsockopt");
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;

    int port = PORT;
    address.sin_port = htons(PORT);

    /// Keep looking for any available port since PORT(=8080)
    while (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        address.sin_port = htons(++port);
    }
    if (port != PORT)
    {
        printf("Port %d was already in use. Using port %d instead.\n", PORT, port);
    }
    else
    {
        printf("Running on port 8080\n");
    }

    if (listen(server_fd, 3) < 0)
    {
        raise_error("listen");
    }

    /// Infinite loop to listen to incoming connections.
    while (1)
    {
        new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
        if (new_socket < 0)
        {
            raise_error("accept");
        }
        valread = read(new_socket, buffer, 1024);
        printf("Client: %s\n", buffer);
        send(new_socket, connection_reply, strlen(connection_reply), 0);
        printf("Hello message sent\n");
    }
    return 0;
}