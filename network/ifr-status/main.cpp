#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define IFR_NAME "wlan0"

bool getIfrStatus(const char* ifrName) {
    int fd;
    struct ifreq ifr;

    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        return 0;
    }

    strncpy(ifr.ifr_name, ifrName, IFNAMSIZ);

    if (ioctl(fd, SIOCGIFFLAGS, &ifr) < 0) {
        perror("ioctl");
        close(fd);
        return 0;
    }

    close(fd);

    if (ifr.ifr_flags & IFF_UP) {
        return 1;
    }

    return 0;
}

int main() {
    bool ret = getIfrStatus(IFR_NAME);

    if (ret) {
        printf("%s is UP\n", IFR_NAME);
    } else {
        printf("%s is DOWN\n", IFR_NAME);
    }

    return 0;
}
