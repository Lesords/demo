#include <iostream>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <sys/select.h>

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
    int server_fd, max_fd = 0;
    const int nPort = 9090;
    const int nNum = 5;

    if (-1 == init_server(server_fd, nPort, nNum, 1)) {
        printf("[server] - init_server failed\n");
        return 1;
    }

    fd_set read_fds, tmp_fds;
    struct timeval time_val = {
        .tv_sec = 0,
        .tv_usec = 300 * 1000,
    };
    
    FD_ZERO(&read_fds);
    FD_SET(server_fd, &read_fds);
    max_fd = std::max(max_fd, server_fd);

    while (true) {
        FD_ZERO(&tmp_fds);
        tmp_fds = read_fds;

        int num = select(max_fd + 1, &tmp_fds, NULL, NULL, &time_val);
        if (num == 0) {
            // printf("[sever] - select timeout\n");
            continue;
        } else if (num == -1) {
            perror("select");
            break;
        }

        for (int i = 0; i <= max_fd && num; ++i) {
            if (!FD_ISSET(i, &tmp_fds)) {
                continue;
            }

            --num;
            if (i == server_fd) {
                int client_fd = accept_client(server_fd);

                max_fd = std::max(max_fd, client_fd);
                FD_SET(client_fd, &read_fds);
            } else {
                char buffer[30] = {0};
                int ret = read(i, buffer, sizeof(buffer));
                if (ret) {
                    std::cout << "[server] - recv: " << buffer << "\n";
                } else {
                    close(i);
                    FD_CLR(i, &read_fds);
                    std::cout << "[server] - remove client " << i << "\n";
                }
            }
        }
    }

    close(server_fd);

    return 0;
}
