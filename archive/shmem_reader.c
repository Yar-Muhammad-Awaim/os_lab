#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
// #include <unistd.h>

int main(void)
{
    key_t key = ftok("ipc.key", 'W');

    if (key == -1)
    {
        perror("ftok");
        return 1;
    }

    int id = shmget(key, 128, 0600);

    if (id == -1)
    {
        perror("shmget");
        return 1;
    }

    char *mem = shmat(id, NULL, 0);

    if (mem == (void *)-1)
    {
        perror("shmat");
        return 1;
    }

    printf("Read from the shared memory: \n%s\n", mem);

    if (shmdt(mem) == -1)
    {
        perror("shmdt");
        return 1;
    }

    if (shmctl(id, IPC_RMID, NULL) == -1)
    {
        perror("shmctl");
        return 1;
    }

    return 0;
}