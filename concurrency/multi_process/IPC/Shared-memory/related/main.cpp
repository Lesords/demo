#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>

int main() {
    int shmid;
    char *data = nullptr;

    shmid = shmget(IPC_PRIVATE, 20, 0666 | IPC_CREAT);
    if (shmid < 0) {
        printf("Shared memory creation failed\n");
        return 1;
    }

    data = (char *) shmat(shmid, nullptr, 0);
    if (data == (char *) -1) {
        printf("Shared memory attach failed\n");
        return 1;
    }

    int pid = fork();
    if (pid < 0) {
        printf("fork failed\n");
    } else if (pid == 0) {
        printf("son process recv: %s\n", data);
        strcpy(data, "Hello, my dad");
        shmdt(data);
    } else {
        strcpy(data, "Hello, my son");
        sleep(1);
        printf("father process recv: %s\n", data);
        shmdt(data);
    }

    shmctl(shmid, IPC_RMID, 0);
    return 0;
}
