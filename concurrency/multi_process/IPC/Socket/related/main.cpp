#include <iostream>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCK_PATH "/tmp/server.sock"

int main() {
    int server_fd;
    struct sockaddr_un address;
    char buffer[20] = {0};

    if ((server_fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return 1;
    }

    memset(&address, 0, sizeof(struct sockaddr_un));
    address.sun_family = AF_UNIX;
    strncpy(address.sun_path, SOCK_PATH, sizeof(address.sun_path) - 1);

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
        int client_fd = socket(AF_UNIX, SOCK_STREAM, 0);
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
        struct sockaddr_un peer_addr;
        socklen_t peer_addr_size = sizeof(peer_addr);
        int new_socket = accept(server_fd, (struct sockaddr *) &peer_addr, &peer_addr_size);
        if (new_socket < 0) {
            perror("accept");
            return 1;
        }

        std::cout << "peer_addr.sun_path: " << peer_addr.sun_path << "\n";

        strcpy(buffer, "I'm dad");
        write(new_socket, buffer, sizeof(buffer));

        read(new_socket, buffer, sizeof(buffer));
        std::cout << "Father process recv: " << buffer << "\n";
        wait(nullptr);

        close(server_fd);

        // remove the UNIX path name from the file system
        unlink(SOCK_PATH);
    }

    return 0;
}
