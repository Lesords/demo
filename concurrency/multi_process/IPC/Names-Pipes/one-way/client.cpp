#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>  // O_RDWR
#include <unistd.h> // write

#define FIFO_FILE "/tmp/fifo_twoway"
int main() {
    int fd;
    char send[20] = "hello";

    fd = open(FIFO_FILE, O_CREAT | O_WRONLY);

    while (1) {
        write(fd, send, sizeof(send));
        printf("FIFO_CLIENT - send: %s\n", send);
        sleep(1);
    }
    return 0;
}
