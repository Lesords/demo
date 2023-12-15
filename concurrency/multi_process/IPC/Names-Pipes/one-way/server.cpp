#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>  // O_RDWR
#include <unistd.h> // read

#define FIFO_FILE "/tmp/fifo_twoway"
int main() {
    int fd;
    char recv[20];

    mkfifo(FIFO_FILE, S_IFIFO | 0640);
    fd = open(FIFO_FILE, O_RDONLY);

    while (1) {
        int nRecv = read(fd, recv, sizeof(recv));
        printf("FIFO_SERVER - recv: %s, len: %d\n", recv, nRecv);
    }
    return 0;
}
