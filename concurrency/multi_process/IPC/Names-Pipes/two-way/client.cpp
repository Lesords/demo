#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>  // O_RDWR
#include <unistd.h> // write

#define FIFO_FILE "/tmp/fifo_twoway"
int main() {
    int fd;
    char send[20] = "This is client";
    char recv[20];

    fd = open(FIFO_FILE, O_CREAT | O_RDWR);

    while (1) {
        write(fd, send, sizeof(send));
        printf("FIFO_CLIENT - send -> %s\n", send);
        sleep(1);

        read(fd, recv, sizeof(recv));
        printf("FIFO_CLIENT- recv <- %s\n\n", recv);
    }
    return 0;
}
