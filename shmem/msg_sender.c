#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

typedef struct
{
    long mtype;
    char message[128];
} Message;

int main(void)
{
    key_t key = ftok("ipc.key", 'u');

    if (key == -1)
    {
        perror("ftok");
        return 1;
    }

    int qid = msgget(key, IPC_CREAT | 0600);

    if (qid == -1)
    {
        perror("msgget");
        return 1;
    }

    Message msg = {0};
    msg.mtype = 10;

    snprintf(msg.message, 128, "GIVING UP IS NOT IN THE BLOOD SIR, GIVING UP IS NOT IN THE BLOOD.");

    if (msgsnd(qid, &msg, sizeof(msg.message), 0) == -1)
    {
        perror("msgsnd");
        return 1;
    }

    printf("MESSAGE SENT SUCCESSFULLY TO THE MESSAGE QUEUE.\n");
    return 0;
}