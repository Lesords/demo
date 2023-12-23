#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>

#define SHM_KEY 0x12345

struct shm_data {
    int cnt;
    int write_complete;
    int read_complete;
};

int main() {
    int shmid;
    struct shm_data *data;

    shmid = shmget(SHM_KEY, sizeof(struct shm_data), 0644 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        return 1;
    }

    data = (shm_data *) shmat(shmid, NULL, 0);
    if (data == (shm_data *) -1 ) {
        perror("shmat");
        return 1;
    }

    while (data->write_complete != 2) {
        if (data->cnt == -1) {
            perror("read");
            return 1;
        }
        sleep(3);
    }

    printf("Read Process - cnt: %d\n", data->cnt);
    data->read_complete = 1;

    if (shmdt(data) == -1) {
        perror("shmdt");
        return 1;
    }

    shmctl(shmid, IPC_RMID, 0);
    return 0;
}
