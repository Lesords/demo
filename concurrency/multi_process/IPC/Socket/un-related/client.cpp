#include <iostream>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCK_PATH "/tmp/server.sock"

int main() {
    int client_fd;
    struct sockaddr_un address;
    char buffer[20] = {0};

    if ((client_fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return 1;
    }

    memset(&address, 0, sizeof(struct sockaddr_un));
    address.sun_family = AF_UNIX;
    strncpy(address.sun_path, SOCK_PATH, sizeof(address.sun_path) - 1);

    int nRet = connect(client_fd, (struct sockaddr *) &address, sizeof(address));
    if (nRet < 0) {
        perror("connect");
        return 1;
    }

    read(client_fd, buffer, sizeof(buffer));
    std::cout << "Client recv: " << buffer << "\n";

    strcpy(buffer, "I'm client");
    write(client_fd, buffer, sizeof(buffer));

    close(client_fd);

    return 0;
}
