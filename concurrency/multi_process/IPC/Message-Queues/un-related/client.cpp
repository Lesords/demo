#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/msg.h>

#define PERMS 0666

struct msg_data {
    long mtype;
    char mtext[20];
};

int main() {
    msg_data data;
    int msqid;
    key_t key;

    if ((key = ftok(".", 'a')) == -1) {
        perror("ftok");
        return 1;
    }

    if ((msqid = msgget(key, PERMS | IPC_CREAT)) == -1) {
        perror("msgget");
        return 1;
    }

    data.mtype = 1;
    strcpy(data.mtext, "This is client");
    if (msgsnd(msqid, (void *) &data, sizeof(data.mtext), 0) == -1) {
        perror("msgsnd");
        return 1;
    }

    if (msgrcv(msqid, (void *) &data, sizeof(data.mtext), 2, 0) == -1) {
        perror("msgrcv");
        return 1;
    }
    printf("client process recv: %s\n", data.mtext);

    if (msgctl(msqid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        return 1;
    }
    printf("message queue: remove message queue\n");
    return 0;
}
