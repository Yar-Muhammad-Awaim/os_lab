#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

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

    int qid = msgget(key, 0600);

    if (qid == -1)
    {
        perror("msgget");
        return 1;
    }

    Message msg = {0};
    msg.mtype = 10;

    ssize_t received = msgrcv(qid, &msg, sizeof(msg.message), msg.mtype, 0);

    if (received == -1)
    {
        perror("msgrcv");
        return 1;
    }

    printf("RECIEVED FOLLOWING MESSAGE FROM THE MESSAGE QUEUE: \n\t%s\n",
           msg.message);

    if (msgctl(qid, IPC_RMID, NULL) == -1)
    {
        perror("msgctl");
        return 1;
    }

    return 0;
}