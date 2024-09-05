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

std::string getIpAddress(const char* ifrName) {
    char info[INET_ADDRSTRLEN];
    int fd;
    struct ifreq ifr;

    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        return std::string();
    }

    strncpy(ifr.ifr_name, ifrName, IFNAMSIZ);

    if (ioctl(fd, SIOCGIFADDR, &ifr) < 0) {
        perror("ioctl SIOCGIFADDR");
        close(fd);
        return std::string();
    }
    inet_ntop(AF_INET, &((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr, info, INET_ADDRSTRLEN);

    close(fd);

    return std::string(info);
}

int main() {
    std::string ipAddress;

    ipAddress = getIpAddress(IFR_NAME);

    std::cout << "IP Address: " << ipAddress << "\n";

    return 0;
}

