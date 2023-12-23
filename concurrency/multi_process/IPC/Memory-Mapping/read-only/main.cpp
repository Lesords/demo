#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>

void init_mmap_data() {
    int fd = open("MMAP_DATA.txt", O_CREAT|O_TRUNC|O_WRONLY, 0666);
    if (fd == -1) {
        perror("File open error ");
        return;
    }

    for (char ch = 'a'; ch <= 'z'; ch++) {
        write(fd, &ch, sizeof(ch));
    }

    close(fd);
    return;
}

int main() {
    struct stat mmapstat;
    char *data;
    int fd;
    int maxbyteindex;
    int offset;
    int unmapstatus;

    init_mmap_data();
    if (stat("MMAP_DATA.txt", &mmapstat) == -1) {
        perror("stat failure");
        return 1;
    }

    if ((fd = open("MMAP_DATA.txt", O_RDONLY)) == -1) {
        perror("open failure");
        return 1;
    }

    data = (char *) mmap((caddr_t)0, mmapstat.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if (data == MAP_FAILED) {
        perror("mmap failure");
        return 1;
    }
    maxbyteindex = mmapstat.st_size - 1;

    do {
        printf("Enter -1 to quit or enter a number between 0 and %d: ", maxbyteindex);
        scanf("%d",&offset);
        if ( (offset >= 0) && (offset <= maxbyteindex) ) {
            printf("Received char at %d is %c\n", offset, data[offset]);
        } else if (offset != -1) {
            printf("Received invalid index %d\n", offset);
        }
    } while (offset != -1);

    unmapstatus = munmap(data, mmapstat.st_size);
    if (unmapstatus == -1) {
        perror("munmap failure");
        return 1;
    }

    close(fd);
    system("rm -f MMAP_DATA.txt");
    return 0;
}
