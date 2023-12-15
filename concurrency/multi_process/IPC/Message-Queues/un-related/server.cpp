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

    if (msgrcv(msqid, (void *) &data, sizeof(data.mtext), 1, 0) == -1) {
        perror("msgrcv");
        return 1;
    }
    printf("server process recv: %s\n", data.mtext);

    data.mtype = 2;
    strcpy(data.mtext, "This is server");
    if (msgsnd(msqid, (void *) &data, sizeof(data.mtext), 0) == -1) {
        perror("msgsnd");
        return 1;
    }

    printf("server: done sending messages\n");
    return 0;
}
