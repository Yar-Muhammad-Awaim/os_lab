#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{

    int shmid = shmget(IPC_PRIVATE, sizeof(int), 0600);

    if (shmid == -1)
    {
        perror("shmget");
        return 1;
    }

    int *shared = shmat(shmid, NULL, 0);

    if (shared == (void *)-1)
    {
        perror("shmat");
        return 1;
    }

    *shared = 10;

    pid_t pid = fork();

    if (pid == 0)
    {
        printf("VALUE IN CHILD BEFORE CHANGING, shared = %d\n", *shared);
        *shared = 529;
        printf("VALUE IN CHILD, shared = %d\n", *shared);

        if (shmdt(shared) == -1)
        {
            perror("shmdt");
            return 1;
        }
    }
    else if (pid > 0)
    {
        waitpid(pid, NULL, 0);

        printf("VALUE IN PARENT, shared = %d\n", *shared);

        if (shmdt(shared) == -1)
        {
            perror("shmdt");
            return 1;
        }

        if (shmctl(shmid, IPC_RMID, NULL) == -1)
        {
            perror("shmctl");
            return 1;
        }
    }
    return 0;
}