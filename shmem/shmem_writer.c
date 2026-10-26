#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int main(void)
{
    key_t key = ftok("ipc.key", 'U');

    if (key == -1)
    {
        perror("ftok");
        return 1;
    }

    int shmid = shmget(key, 128, IPC_CREAT | 0600);

    if (shmid == -1)
    {
        perror("shmget");
        return 1;
    }

    char *mem = shmat(shmid, NULL, 0);

    if (mem == (void *)-1)
    {
        perror("shmat");
        return 1;
    }

    snprintf(mem, 128, "\nHello from process %ld\n", (long)getpid());

    if (shmdt(mem) == -1)
    {
        perror("shmdt");
        return 1;
    }

    return 0;
}