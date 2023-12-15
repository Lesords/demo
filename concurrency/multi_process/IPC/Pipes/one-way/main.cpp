#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
    int fd[2];
    char recv[20];
    char send[20] = "Hello, my son";

    if (pipe(fd) < 0) {
        printf("Pipe creation failed\n");
        return 1;
    }

    int pid = fork();
    if (pid < 0) {
        printf("fork failed\n");
    } else if (pid == 0) {
        close(fd[1]); // close the write side
        read(fd[0], recv, sizeof(recv));
        printf("son process recv: %s\n", recv);
    } else {
        close(fd[0]); // close the read side
        write(fd[1], send, sizeof(send));
        printf("father process send: %s\n", send);
    }
    return 0;
}
