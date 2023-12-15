#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>  // O_RDWR
#include <unistd.h> // read

#define FIFO_FILE "/tmp/fifo_twoway"
int main() {
    int fd;
    char send[20] = "This is server";
    char recv[20];

    mkfifo(FIFO_FILE, S_IFIFO | 0640);
    fd = open(FIFO_FILE, O_RDWR);

    while (1) {
        int nRecv = read(fd, recv, sizeof(recv));
        printf("FIFO_SERVER - recv <- %s\n\n", recv);

        write(fd, send, sizeof(send));
        printf("FIFO_SERVER - send -> %s\n", send);
        sleep(1);
    }
    return 0;
}
