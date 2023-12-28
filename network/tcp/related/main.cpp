#include <iostream>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
    int server_fd;
    struct sockaddr_in address;
    char buffer[20] = {0};

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return 1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8888);

    if (bind(server_fd, (struct sockaddr *) &address, sizeof(address)) < 0) {
        perror("bind");
        return 1;
    }

    if (listen(server_fd, 1) < 0) {
        perror("listen");
        return 1;
    }

    int pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        int client_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (socket < 0) {
            perror("socket");
            return 1;
        }

        int nRet = connect(client_fd, (struct sockaddr *) &address, sizeof(address));
        if (nRet < 0) {
            perror("connect");
            return 1;
        }

        read(client_fd, buffer, sizeof(buffer));
        std::cout << "Child process recv: " << buffer << "\n";

        strcpy(buffer, "I'm son");
        write(client_fd, buffer, sizeof(buffer));

        close(client_fd);
    } else {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);

        int new_socket = accept(server_fd, (struct sockaddr *) &client_addr, &client_len);
        if (new_socket < 0) {
            perror("accept");
            return 1;
        }

        std::cout << "Addr: " << inet_ntoa(client_addr.sin_addr) << "\n";
        std::cout << "port: " << client_addr.sin_port << "\n";

        strcpy(buffer, "I'm dad");
        write(new_socket, buffer, sizeof(buffer));

        read(new_socket, buffer, sizeof(buffer));
        std::cout << "Father process recv: " << buffer << "\n";
        wait(nullptr);

        close(server_fd);
    }

    return 0;
}
