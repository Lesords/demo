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

std::string getMacAddress(const char* ifrName) {
    std::string wifiName = "xx:xx:xx:xx:xx:xx";
    int fd;
    struct ifreq ifr;

    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        return wifiName;
    }

    strncpy(ifr.ifr_name, ifrName, IFNAMSIZ);

    if (ioctl(fd, SIOCGIFHWADDR, &ifr) < 0) {
        perror("ioctl");
        close(fd);
        return wifiName;
    }

    const char* data = ifr.ifr_hwaddr.sa_data;
    sprintf(&wifiName[0], "%2x:%2x:%2x:%2x:%2x:%2x",
            (uint8_t) data[0],
            (uint8_t) data[1],
            (uint8_t) data[2],
            (uint8_t) data[3],
            (uint8_t) data[4],
            (uint8_t) data[5]);

    close(fd);

    return wifiName;
}

int main() {
    std::string macAddress;

    macAddress = getMacAddress(IFR_NAME);

    std::cout << "MAC Address: " << macAddress << "\n";

    return 0;
}

