#include <iostream>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <sys/epoll.h>

#define MAX_EVENTS 128

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

int add_event(const int& epoll_fd, const int& fd) {
    struct epoll_event event;

    event.events = EPOLLIN;
    event.data.fd = fd;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &event) == -1) {
        perror("epoll_ctl");
        return 1;
    }

    return 0;
}

int main() {
    int server_fd;
    const int nPort = 9090;
    const int nNum = 5;

    if (-1 == init_server(server_fd, nPort, nNum, 1)) {
        printf("[server] - init_server failed\n");
        return 1;
    }

    struct epoll_event event_array[MAX_EVENTS];
    int epoll_fd;
    int timeout = 300;

    epoll_fd = epoll_create(MAX_EVENTS);
    if (epoll_fd == -1) {
        perror("epoll_create");
        return 1;
    }

    add_event(epoll_fd, server_fd);

    while (true) {
        int events = epoll_wait(epoll_fd, event_array, MAX_EVENTS, timeout);
        if (events == 0) {
            // printf("[sever] - epoll_wait timeout\n");
            continue;
        } else if (events == -1) {
            perror("epoll_wait");
            return 1;
        }

        for (int i = 0; i < events; i++) {
            if (event_array[i].events != EPOLLIN) {
                printf("error, events = %d\n", event_array[i].events);
                break;
            }

            if (event_array[i].data.fd == server_fd) {
                int client_fd = accept_client(server_fd);

                add_event(epoll_fd, client_fd);
            } else {
                char buffer[30] = {0};
                int ret = read(event_array[i].data.fd, buffer, sizeof(buffer));
                if (ret) {
                    std::cout << "[server] - recv: " << buffer << "\n";
                } else {
                    std::cout << "[server] - remove client " << event_array[i].data.fd << "\n";
                    close(event_array[i].data.fd);
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, event_array[i].data.fd, NULL);
                }
            }
        }
    }

    close(server_fd);

    return 0;
}
