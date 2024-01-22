#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int main() {
    int pid;

    pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        char* cmd = (char *) "/bin/ls";
        char* const argv[] = {cmd, 0};
        int ret = 0;

        ret = execv(cmd, argv);
        printf("Never return to this position (%d)\n", ret);
    } else {
        wait(nullptr);
    }

    return 0;
}
