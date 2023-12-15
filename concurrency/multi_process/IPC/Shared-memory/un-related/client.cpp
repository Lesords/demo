#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>

#define BUF_SIZE 20
#define SHM_KEY 0x123

struct shmsg {
    int cnt;
    int complete;
    char buf[BUF_SIZE];
};

int main() {
    int shmid;
    shmsg *p_shm;

    shmid = shmget(SHM_KEY, sizeof(struct shmsg), 0644 | IPC_CREAT);
    if (shmid == -1) {
        printf("Shared memory creation failed\n");
        return 1;
    }

    p_shm = (shmsg *) shmat(shmid, NULL, 0);
    if (p_shm == (shmsg *) -1) {
        printf("Shared memory attach failed\n");
        return -1;
    }

    for (int i = 0; i < 3; ++i) {
        p_shm->cnt = 10;
        p_shm->complete = 0;
        for (int j = 0; j < 10; ++j) {
            p_shm->buf[j] = 'a' + i;
        }
        sleep(1);
    }
    p_shm->complete = 1;

    printf("client process done here\n");
    shmdt(p_shm);
    shmctl(shmid, IPC_RMID, 0);

    return 0;
}
