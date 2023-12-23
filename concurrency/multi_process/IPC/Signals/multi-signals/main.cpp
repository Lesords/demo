#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void handleSignals(int signum);

int main(void) {
    void (*sigHandlerInterrupt)(int);
    void (*sigHandlerQuit)(int);
    void (*sigHandlerReturn)(int);
    sigHandlerInterrupt = sigHandlerQuit = handleSignals;
    sigHandlerReturn = signal(SIGINT, sigHandlerInterrupt);
    if (sigHandlerReturn == SIG_ERR) {
        perror("signal error: ");
        return 1;
    }
    sigHandlerReturn = signal(SIGQUIT, sigHandlerQuit);

    if (sigHandlerReturn == SIG_ERR) {
        perror("signal error: ");
        return 1;
    }
    while (1) {
        printf("\nTo terminate this program, perform the following: \n");
        printf("1. Open another terminal\n");
        printf("2. Issue command: kill %d or issue CTRL+C 2 times (second time it terminates)\n", getpid());
        sleep(10);
    }
    return 0;
}

void handleSignals(int signum) {
    switch(signum) {
        case SIGINT:
            printf("\nYou pressed CTRL+C \n");
            printf("Now reverting SIGINT signal to default action\n");
            signal(SIGINT, SIG_DFL);
            break;
        case SIGQUIT:
            printf("\nYou pressed CTRL+\\ \n");
            break;
        default:
            printf("\nReceived signal number %d\n", signum);
            break;
    }
    return;
}
