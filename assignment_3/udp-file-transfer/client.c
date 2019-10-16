/**
 * @file client.c
 * @brief Client code for UDP socket programming
 * @version 0.1
 * @date 2019-08-22
 *  
 */

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define IP_PROTOCOL 0
#define IP_ADDRESS "127.0.0.1" // localhost
#define PORT_NO 15050
#define NET_BUF_SIZE 32
#define sendrecvflag 0

/**
 * @brief function to clear buffer
 * 
 * @param b 
 */
void clearBuf(char *b)
{
    int i;
    for (i = 0; i < NET_BUF_SIZE; i++)
        b[i] = '\0';
}

/**
 * @brief function to receive file
 * 
 * @param buf 
 * @param s 
 * @return int 
 */
int recvFile(char *buf, int s, FILE *fp)
{
    int i;
    char ch;
    for (i = 0; i < s; i++)
    {
        ch = buf[i];
        if (ch == EOF)
        {
            return 1;
        }
        else
        {
            printf("%c", ch);
            fputc(ch, fp);
        }
    }
    return 0;
}

/**
 * @brief Driver code
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 0;
    }
    int sockfd, nBytes;
    struct sockaddr_in addr_con;
    int addrlen = sizeof(addr_con);
    addr_con.sin_family = AF_INET;
    addr_con.sin_port = htons(PORT_NO);
    addr_con.sin_addr.s_addr = inet_addr(IP_ADDRESS);
    char net_buf[NET_BUF_SIZE];

    FILE *fp;

    // socket()
    sockfd = socket(AF_INET, SOCK_DGRAM,
                    IP_PROTOCOL);

    if (sockfd < 0)
        printf("\nfile descriptor not received!!\n");
    else
        printf("\nfile descriptor %d received\n", sockfd);

    sendto(sockfd, argv[1], strlen(argv[1]),
           sendrecvflag, (struct sockaddr *)&addr_con,
           addrlen);

    printf("\n---------Data Received---------\n");
    // Create file before receiving contents in buffer
    FILE *writeFile = fopen("received/test.txt", "w");
    while (1)
    {
        // receive
        clearBuf(net_buf);
        nBytes = recvfrom(sockfd, net_buf, NET_BUF_SIZE,
                          sendrecvflag, (struct sockaddr *)&addr_con,
                          &addrlen);

        // process
        if (recvFile(net_buf, NET_BUF_SIZE, writeFile))
        {
            fclose(writeFile);
            break;
        }
    }
    printf("\n-------------------------------\n");

    return 0;
}
