#include "00.head.h"
#define INS 5

struct Num {
    int now;
    int sum;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
};
struct Num *share_memory;
void do_add(int x) {
    while (1) {
        pthread_mutex_lock(&share_memory->mutex);
        pthread_cond_wait(&share_memory->cond, &share_memory->mutex);
        int flag = 0;
        for (int i = 0; i < 100; i++) {
            if (share_memory->now > 1000) {
                pthread_mutex_unlock(&share_memory->mutex);
                pthread_cond_signal(&share_memory->cond);
                exit(0);
            }
            share_memory->sum += share_memory->now;
            share_memory->now++;
            printf("<%d> now = %d, sum = %d\n", x, share_memory->now, share_memory->sum);
            fflush(stdout);
            //pthread_mutex_unlock(&share_memory->mutex);
        }
        pthread_mutex_unlock(&share_memory->mutex);
        pthread_cond_signal(&share_memory->cond);
    }
    exit(0);
}

int main() {
    pid_t pid;
    int x = 0, shmid;
    key_t key = ftok(".", 2021);
    if ((shmid = shmget(key, sizeof(struct Num), IPC_CREAT | IPC_EXCL | 0666)) < 0) {
        perror("sshmget");
        exit(-1);
    }
    share_memory = (struct Num*)shmat(shmid, NULL, 0);
    if (share_memory == (struct Num*)-1) {
        perror("share_memory");
        exit(-1);
    }
    share_memory->now = 0;
    share_memory->sum = 0;


    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(&share_memory->mutex, &attr);

    pthread_condattr_t condattr;
    pthread_condattr_init(&condattr);
    pthread_condattr_setpshared(&condattr, 1);
    pthread_cond_init(&share_memory->cond, &condattr);


    //printf("before fork()\n");
    for (int i = 1; i <= INS; i++) {
        if ((pid = fork()) < 0) {
            perror("fork");
        } 
        x = i;
        if (pid == 0) break;
    }
    
    if (pid == 0) {
        do_add(x);
    } else {
        sleep(1);
        pthread_cond_signal(&share_memory->cond);
        for (int i = 1; i <= INS; i++) {
            wait(NULL);
        }
    }
    printf("end ==> share_memory->sum = %d \n", share_memory->sum);
    shmdt(share_memory);
    shmctl(shmid, IPC_RMID,NULL);
    
    return 0;
}

