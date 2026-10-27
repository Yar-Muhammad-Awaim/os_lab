#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int x = 3;
    printf("Before fork x => %d.\n", x);

    pid_t pid = fork();

    if (pid == 0)
    {
        printf("VARIABLE FROM CHILD => %d\n", x);
    }
    else if (pid > 0)
    {
        printf("VARIABLE FROM PARENT => %d\n", x);
    }
    return 0;
}