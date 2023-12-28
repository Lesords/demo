#include <iostream>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int init_server(int &fd, int nPort, int nNum, int nOpt) {
    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("[server] - socket");
        return -1;
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(nPort);

    if (nOpt) {
        if(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &nOpt, sizeof(nOpt)) < 0) {
            perror("[server] - setsockopt");
            return -1;
        }
    }

    if (bind(fd, (struct sockaddr *) &address, sizeof(address)) < 0) {
        perror("[server] - bind");
        return -1;
    }

    if (listen(fd, nNum) < 0) {
        perror("[server] - listen");
        return -1;
    }

    return 0;
}

int main() {
    int server_fd;
    const int nPort = 9090;
    const int nNum = 1;

    if (-1 == init_server(server_fd, nPort, nNum, 1)) {
        printf("[server] - init_server failed\n");
        return 1;
    }

    char buffer[20] = {0};
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    std::cout << "[server] - wait for client...\n";
    int client_fd = accept(server_fd, (struct sockaddr *) &client_addr, &client_len);
    if (client_fd < 0) {
        perror("[server] - accept");
        return 1;
    }

    std::cout << "\n[server] - Addr: " << inet_ntoa(client_addr.sin_addr) << "\n";
    std::cout << "[server] - port: " << client_addr.sin_port << "\n\n";

    while (true) {
        int ret = read(client_fd, buffer, sizeof(buffer));
        if (ret) {
            std::cout << "[server] - recv: " << buffer << "\n";
        }

        if (strcmp(buffer, "byebye") == 0) {
            break;
        }
    }

    close(client_fd);
    close(server_fd);

    return 0;
}
