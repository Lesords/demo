#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
    int fa_pipe[2], son_pipe[2];
    char fa_recv[20], fa_send[20] = "Hello, my son";
    char son_recv[20], son_send[20] = "Hello, my dad";

    if (pipe(fa_pipe) < 0 || pipe(son_pipe)) {
        printf("Pipe creation failed\n");
        return 1;
    }

    int pid = fork();
    if (pid < 0) {
        printf("fork failed\n");
    } else if (pid == 0) {
        close(fa_pipe[1]);  // close the write side on fa_pipe
        close(son_pipe[0]); // close the read side on son_pipe
        read(fa_pipe[0], son_recv, sizeof(son_recv));
        printf("son process recv: %s\n", son_recv);

        write(son_pipe[1], son_send, sizeof(son_send));
        printf("son process send: %s\n", son_send);
    } else {
        close(fa_pipe[0]);  // close the read side on fa_pipe
        close(son_pipe[1]); // close the write side on son_pipe
        write(fa_pipe[1], fa_send, sizeof(fa_send));
        printf("father process send: %s\n", fa_send);

        read(son_pipe[0], fa_recv, sizeof(fa_recv));
        printf("father process recv: %s\n", fa_recv);
    }
    return 0;
}
