#include <iostream>
#include <string.h>
#include <unistd.h> // getcwd, readlink

int main() {
    char szPath[128];

    getcwd(szPath, sizeof(szPath));
    printf("current directory: %s\n", szPath);

    // "/proc/self/exe" is a symbolic link, represents the absolute path of the current program
    int ret = readlink("/proc/self/exe", szPath, sizeof(szPath));
    if (ret == -1) {
        perror("readlink");
        return 1;
    }
    printf("exe path: %s\n", szPath);

    return 0;
}
