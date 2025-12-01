#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Use example: %s 127.0.0.1\n", *argv);
        return -1;
    }

    struct in_addr addr;
    struct hostent *phost = nullptr;
    char *ptr = nullptr;

    ptr = argv[1];

    if (inet_pton(AF_INET, ptr, &addr) <= 0) {
        printf("inet_pton error:%s\n", strerror(errno));
        return -1;
    }

    phost = gethostbyaddr((const char*)&addr, sizeof(addr), AF_INET);
    if (phost == NULL) {
        printf("gethostbyaddr error:%s\n", strerror(h_errno));
        return -1;
    }	

    printf("ip: %s\n", ptr);
    printf("official hostname: %s\n", phost->h_name);
    printf("aliases hostname: %s\n", phost->h_aliases[0]);

    return 0;
}
