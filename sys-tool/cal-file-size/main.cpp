#include <stdio.h>
#include <sys/stat.h>

long long cal_large_file_size(const char *pathname) {
    long long size = 0;
    FILE *pFile = fopen(pathname, "rb");
    if (pFile == NULL) {
        perror("fopen");
        return -1;
    }

    fseeko(pFile, 0, SEEK_END);
    size = ftello(pFile);
    rewind(pFile);

    fclose(pFile);
    return size;
}

long cal_file_size(const char *pathname) {
    long size = 0;
    FILE *pFile = fopen(pathname, "rb");
    if (pFile == NULL) {
        perror("fopen");
        return -1;
    }

    fseek(pFile, 0, SEEK_END);
    size = ftell(pFile);
    rewind(pFile);

    fclose(pFile);
    return size;
}

off_t stat_file_size(const char *pathname) {
    struct stat filestat;
    if (stat(pathname, &filestat) == -1) {
        perror("stat");
        return -1;
    }

    return filestat.st_size;
}

int main() {
    const char *FILE_NAME = "example.txt";
    printf("large file size: %lld\n", cal_large_file_size(FILE_NAME));
    printf("file size: %ld\n", cal_file_size(FILE_NAME));
    printf("stat file size: %ld\n", stat_file_size(FILE_NAME));
    return 0;
}
