#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define SHM_KEY 0x12345
#define SEM_KEY 0x54321

struct shm_data {
    int cnt;
    int write_complete;
    int read_complete;
};

union semun {
    int val;               /* val for SETVAL */
    struct semid_ds *buf;  /* Buffer for IPC_STAT and IPC_SET */
    unsigned short *array; /* Buffer for GETALL and SETALL */
    struct seminfo *__buf; /* Buffer for IPC_INFO and SEM_INFO*/
};

void init_sem(int semid, int value) {
    semun sem;
    sem.val = value;

    if (semctl(semid, 0, SETVAL, sem) == -1) {
        perror("init semaphore");
        return ;
    }
}

void lock_sem(int semid) {
    struct sembuf sem_buf = {
        .sem_num = 0,
        .sem_op = -1,
        .sem_flg = SEM_UNDO,
    };

    if (semop(semid, &sem_buf, 1) == -1) {
        perror("lock semaphore");
    }
}

void unlock_sem(int semid) {
    struct sembuf sem_buf = {
        .sem_num = 0,
        .sem_op = 1,
        .sem_flg = SEM_UNDO,
    };

    if (semop(semid, &sem_buf, 1) == -1) {
        perror("unlock semaphore");
    }
}

void increase_cnt(int semid, struct shm_data *data, int tot_cnt) {
    sleep(3);

    lock_sem(semid);
    for (int i = 1; i <= tot_cnt; ++i) {
        ++(data->cnt);
    }
    ++(data->write_complete);
    unlock_sem(semid);
}

int main() {
    int shmid;
    struct shm_data *data;

    shmid = shmget(SHM_KEY, sizeof(struct shm_data), 0644 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        return 1;
    }

    data = (shm_data *) shmat(shmid, NULL, 0);
    if (data == (shm_data *) -1) {
        perror("shmat");
        return 1;
    }
    data->write_complete = 0;

    /* Create a semaphore set */
    int semid = semget(SEM_KEY, 1, 0644 | IPC_CREAT);
    if (semid == -1) {
        perror("semget");
        return 1;
    }
    init_sem(semid, 1);

    int pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        printf("Write Process - son - start\n");
        increase_cnt(semid, data, 10000);
        printf("Write Process - son - done\n");
    } else {
        printf("Write Process - father - start\n");
        increase_cnt(semid, data, 10000);
        printf("Write Process - father - done\n");
        wait(nullptr);
    }

    if (shmdt(data) == -1) {
        perror("shmdt");
        return 1;
    }

    if (pid > 0 && semctl(semid, 0, IPC_RMID) == -1) {
        perror("semctl");
        return 1;
    }

    return 0;
}
