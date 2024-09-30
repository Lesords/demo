#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define IFR_NAME "wlan0"

std::string getNetmaskAddress(const char* ifrName) {
    char netmask[INET_ADDRSTRLEN];
    int fd;
    struct ifreq ifr;

    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        return std::string();
    }

    strncpy(ifr.ifr_name, ifrName, IFNAMSIZ);

    if (ioctl(fd, SIOCGIFNETMASK, &ifr) < 0) {
        perror("ioctl");
        close(fd);
        return std::string();
    }
    inet_ntop(AF_INET, &((struct sockaddr_in *)&ifr.ifr_netmask)->sin_addr, netmask, INET_ADDRSTRLEN);

    close(fd);

    return std::string(netmask);
}

int main() {
    std::string netMask;

    netMask = getNetmaskAddress(IFR_NAME);

    std::cout << "Netmask Address: " << netMask << "\n";

    return 0;
}
