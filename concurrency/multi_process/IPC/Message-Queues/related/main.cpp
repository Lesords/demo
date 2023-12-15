#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include <sys/msg.h>

struct msg_data {
    long mtype;
    char mtext[20];
};

int main() {
    int msqid;
    msg_data data;

    msqid = msgget(IPC_PRIVATE, 0666 | IPC_CREAT);
    if (msqid < 0) {
        printf("Message creation failed\n");
        return 1;
    }

    int pid = fork();
    if (pid < 0) {
        printf("fork failed\n");
    } else if (pid == 0) {
        if (msgrcv(msqid, &data, sizeof(data.mtext), 1, 0) == -1) {
            printf("Message receive failed\n");
            perror("msgsnd error");
            return 1;
        }
        printf("son process recv: %s\n", data.mtext);
    } else {
        data.mtype = 1;
        strcpy(data.mtext, "Hello, my son");
        if (msgsnd(msqid, &data, sizeof(data.mtext), 0) == -1) {
            printf("Message send failed\n");
            perror("msgsnd error");
            return 1;
        }
        wait(nullptr);
    }

    msgctl(msqid, IPC_RMID, 0);
    return 0;
}
