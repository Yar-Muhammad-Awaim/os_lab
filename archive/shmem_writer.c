#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int main(void)
{
    // Create an agreed upon IPC Key.
    // ipc.key must be created before.
    // W is the label for writer process.
    key_t key = ftok("ipc.key", 'W');

    if (key == -1)
    {
        perror("ftok");
        return -1;
    }

    // Allocate a shared memory segment
    // We have to give it a key, how many memory (in bytes we want)
    // and a flag
    // that flag is going to be IPC_CREAT when using shared memory
    // reading and writing but in fork() child parent cases it is going to be IPC_PRIVATE

    int id = shmget(key, 128, IPC_CREAT | 0600);
    if (id == -1)
    {
        perror("shmget");
        return -1;
    }

    // Attach the writer to the memory and get a pointer
    char *mem = shmat(id, NULL, 0);

    if (mem == (void *)-1)
    {
        perror("shmat");
        return -1;
    }

    // snprintf safely writes exactly `n` number of bytes into a buffer truncating the out of buffer bytes, thus eliminating buffer overflow
    snprintf(mem, 128, "Hello from the process %ld", (long)getpid());

    printf("Written: %s", mem);

    if (shmdt(mem) == -1)
    {
        perror("shmdt");
        return -1;
    }

    return 0;
}