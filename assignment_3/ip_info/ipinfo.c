/**
 * @file ipinfo.c
 * @brief Print IP info like subnet and class
 * @version 0.1
 * @date 2019-08-22
 * 
 */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#define DOT '.'
#define IP_ENTITIES_COUNT 4
#define NA -1

/**
 * @brief Parse input IP address
 * 
 * @param ip_addr 
 * @return int* 
 */
int *parseIP(const char *ip_addr)
{
    static int parsed_ip[IP_ENTITIES_COUNT];
    size_t str_size = strlen(ip_addr);
    int octet_idx = 0;
    for (int str_idx = 0; str_idx < str_size; str_idx++)
    {
        if (ip_addr[str_idx] == DOT)
        {
            octet_idx += 1;
        }
        else
        {
            int next_dig = ip_addr[str_idx] - '0';
            parsed_ip[octet_idx] = parsed_ip[octet_idx] * 10 + next_dig;
        }
    }
    return parsed_ip;
}

/**
 * @brief Print IP information
 * 
 * @param ip_addr 
 */
void printIPInfo(const char *ip_addr)
{
    int *parsed = parseIP(ip_addr);
    /**
     * For determining the class:
     * The idea is to check first octet of IP address.
     * for class A first octet will range from 1 – 126,
     * for class B first octet will range from 128 – 191,
     * for class C first octet will range from 192- 223,
     * for class D first octet will range from 224 – 239,
     * for class E first octet will range from 240 – 255.
     */
    char ip_class;
    if (1 <= parsed[0] && parsed[0] <= 126)
    {
        ip_class = 'A';
    }
    if (128 <= parsed[0] && parsed[0] <= 191)
    {
        ip_class = 'B';
    }
    if (192 <= parsed[0] && parsed[0] <= 223)
    {
        ip_class = 'C';
    }
    if (224 <= parsed[0] && parsed[0] <= 239)
    {
        ip_class = 'D';
    }
    if (240 <= parsed[0] && parsed[0] <= 255)
    {
        ip_class = 'E';
    }
    printf("Class %c\n", ip_class);

    /**
     * Finding the subnet mask 
     */
    int subnet_mask;
    if (ip_class == 'A')
    {
        subnet_mask = 8;
    }
    if (ip_class == 'B')
    {
        subnet_mask = 16;
    }
    if (ip_class == 'C')
    {
        subnet_mask = 24;
    }
    if (ip_class == 'D' || ip_class == 'E')
    {
        subnet_mask = NA;
    }
    if (subnet_mask > 0)
    {
        printf("The subnet mask is %d\n", subnet_mask);
    }
    else if (subnet_mask == NA)
    {
        printf("The subnet mask is not defined for class %c", ip_class);
    }

    /**
     * For determining the Network and Host ID:
     * We know that Subnet Mask for Class A is 8,
     * for Class B is 16 and
     * for Class C is 24 whereas 
     * Class D and E is not divided into Network and Host ID.
     */
    char network_id[11], host_id[11];
    if (subnet_mask == 8)
    {
        sprintf(network_id, "%d", parsed[0]);
        sprintf(host_id, "%d.%d.%d", parsed[1], parsed[2], parsed[3]);
    }
    else if (subnet_mask == 16)
    {
        sprintf(network_id, "%d.%d", parsed[0], parsed[1]);
        sprintf(host_id, "%d.%d", parsed[2], parsed[3]);
    }
    else if (subnet_mask == 24)
    {
        sprintf(network_id, "%d.%d.%d", parsed[0], parsed[1], parsed[2]);
        sprintf(host_id, "%d", parsed[3]);
    }

    if (subnet_mask == 8 || subnet_mask == 16 || subnet_mask == 24)
    {
        printf("Network id is %s\n", network_id);
        printf("Host id is %s\n", host_id);
    }
    else if (subnet_mask == NA)
    {
        printf("Network and host ids don't exist for network of class %c", ip_class);
    }
}

/**
 * @brief Main driver function
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Incorrect input format.\nPlease pass IP address as the only parameter.");
        return EINVAL;
    }
    const char *ip_addr = argv[1];
    printIPInfo(ip_addr);
    return 0;
}