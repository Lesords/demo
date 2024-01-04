#include <iostream>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <poll.h>

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

int accept_client(const int &server_fd) {
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    int client_fd = accept(server_fd, (struct sockaddr *) &client_addr, &client_len);
    if (client_fd < 0) {
        perror("[server] - accept");
        exit(1);
    }

    std::cout << "\n[server] - id: " << client_fd << "\n";
    std::cout << "[server] - Addr: " << inet_ntoa(client_addr.sin_addr) << "\n";
    std::cout << "[server] - port: " << client_addr.sin_port << "\n\n";

    return client_fd;
}

int main() {
    int server_fd;
    const int nPort = 9090;
    const int nNum = 5;

    if (-1 == init_server(server_fd, nPort, nNum, 1)) {
        printf("[server] - init_server failed\n");
        return 1;
    }

    struct pollfd fds[200];
    int nfds = 1, tmp = 0;
    int timeout = 300;

    memset(fds, 0, sizeof(fds));
    fds[0] = {
        .fd = server_fd,
        .events = POLLIN,
    };

    while (true) {
        int num = poll(fds, nfds, timeout);
        if (num == 0) {
            // printf("[sever] - poll timeout\n");
            continue;
        } else if (num == -1) {
            perror("poll");
            break;
        }

        tmp = nfds;
        for (int i = 0; i < tmp && num; ++i) {
            if (fds[i].revents == 0) {
                continue;
            }

            if (fds[i].revents != POLLIN) {
                printf("error, revents = %d\n", fds[i].revents);
                break;
            }

            --num;
            if (fds[i].fd == server_fd) {
                int client_fd = accept_client(server_fd);

                fds[nfds++] = {
                    .fd = client_fd,
                    .events = POLLIN,
                };
            } else {
                char buffer[30] = {0};
                int ret = read(fds[i].fd, buffer, sizeof(buffer));
                if (ret) {
                    std::cout << "[server] - recv: " << buffer << "\n";
                } else {
                    std::cout << "[server] - remove client " << fds[i].fd << "\n";
                    close(fds[i].fd);
                    fds[i].fd = -1;
                }
            }
        }
    }

    close(server_fd);

    return 0;
}
