/* Author: Harshit Maurya
 * Enrollment No: 17114037
 * Course: CSN-361
 *
 * Write a C++ program to print the MAC address of your computer.
 */

#include <ifaddrs.h>
#include <iostream>
#include <net/if.h>
#include <string>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <vector>

using namespace std;

vector<string> getActiveInterfaces()
{
    vector<string> iface_list;
    struct ifaddrs *interfaces = nullptr;
    struct ifaddrs *temp_addr = nullptr;
    int success = 0;
    success = getifaddrs(&interfaces);
    if (!success)
    {
        temp_addr = interfaces;
        while (temp_addr != NULL)
        {
            if (temp_addr->ifa_addr->sa_family == AF_INET)
            {
                iface_list.push_back(temp_addr->ifa_name);
            }
            temp_addr = temp_addr->ifa_next;
        }
    }
    freeifaddrs(interfaces);
    return iface_list;
}

string getMacAddress(string interface)
{
    int fd;
    char uc_Mac[32] = {0};

    struct ifreq ifr;
    char const *iface = interface.c_str();
    char *mac;

    fd = socket(AF_INET, SOCK_DGRAM, 0);

    ifr.ifr_addr.sa_family = AF_INET;
    strncpy((char *)ifr.ifr_name, (const char *)iface, IFNAMSIZ - 1);

    ioctl(fd, SIOCGIFHWADDR, &ifr);
    close(fd);

    mac = (char *)ifr.ifr_hwaddr.sa_data;

    sprintf(
        (char *)uc_Mac,
        (const char *)"%.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n",
        (unsigned char)mac[0], (unsigned char)mac[1], (unsigned char)mac[2],
        (unsigned char)mac[3], (unsigned char)mac[4], (unsigned char)mac[5]);

    return uc_Mac;
}

int main()
{
    vector<string> interface_list = getActiveInterfaces();
    if (interface_list.size() > 1)
    {
        cout << "Interface\tMAC Address\n\n";
        for (auto ptr = interface_list.begin() + 1; ptr != interface_list.end(); ptr++)
        {
            string interface = *ptr;
            string mac = getMacAddress(interface);
            cout << *ptr << "\t\t" << mac;
        }
    }
    return 0;
}