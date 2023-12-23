#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void handler_sigtstp(int signum);

int main() {
    pid_t pid;
    printf("Testing SIGSTOP\n");
    pid = getpid();
    printf("Open Another Terminal and issue following command\n");
    printf("kill -SIGCONT %d or kill -CONT %d or kill -18 %d\n", pid, pid, pid);
    raise(SIGSTOP);
    printf("Received signal SIGCONT\n\n");

    void (*sigHandlerReturn)(int);
    sigHandlerReturn = signal(SIGTSTP, handler_sigtstp);
    if (sigHandlerReturn == SIG_ERR) {
        perror("Signal Error: ");
        return 1;
    }
    printf("raise SIGTSTP again\n");
    raise(SIGTSTP);
    printf("after raise function\n");

    return 0;
}

void handler_sigtstp(int signum) {
    if (signum == SIGTSTP) {
        printf("Received SIGTSTP\n");
        // exit(0);
    } else {
        printf("Received %d Signal\n", signum);
    }
    return;
}
