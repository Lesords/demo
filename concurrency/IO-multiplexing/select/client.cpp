#include <iostream>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int getSocketfd(const char *pIp, int nPort) {
    int nSockFd, nRet = 0;
    unsigned int nAddr = 0;
    struct sockaddr_in address;

    if (inet_pton(AF_INET, pIp, &nAddr) != 1) {
        printf("[client] - inet_pton addr error\n");
        return -1;
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(nPort);
    address.sin_addr.s_addr = nAddr;

    nSockFd = socket(AF_INET, SOCK_STREAM, 0);
    nRet = connect(nSockFd, (struct sockaddr *) &address, sizeof(address));

    if (nRet < 0) {
        printf("[client] - connect error = %d %s\n", errno, strerror(errno));
    } else {
        printf("[client] - connect successful\n");
    }

    return nSockFd;
}

int main(int argc, char* argv[]) {
    const char* const IP = "127.0.0.1";
    const int PORT = 9090;

    int fd = getSocketfd(IP, PORT);
    if (fd < 0) {
        return 1;
    }

    char send_data[30] = "This is client ";
    strcat(send_data, *(argv + argc - 1));
    for (int i = 1; i <= 3; ++i) {
        write(fd, send_data, sizeof(send_data));
    }

    printf("[client %s] - Data transmission completed\n", *(argv + argc - 1));

    close(fd);

    return 0;
}
