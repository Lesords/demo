#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int main() {
    int pid = fork();
    if (pid < 0) {
        printf("fork failed\n");
    } else if (pid == 0) {
        printf("this is son process\n");
        sleep(3);
    } else {
        printf("this is father process\n");
        printf("wait for son process\n");
        wait(nullptr);
        printf("son process done here\n");
    }
    return 0;
}
