#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    int fd[2];
    if (pipe(fd) == -1)
    {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork");
        close(fd[0]);
        close(fd[1]);
        return 1;
    }

    if (pid == 0)
    {
        // CHILD PROCESS
        close(fd[1]); // close the writing end
        char buffer[100] = {0};
        ssize_t n = read(fd[0], buffer, sizeof(buffer) - 1);

        if (n == -1)
        {
            perror("read");
            return 1;
        }

        printf("Child received: %s", buffer);
    }
    else if (pid > 0)
    {
        // PARENT PROCESS
        close(fd[0]); // close the reading end
        const char msg[] = "Hey cutie patotie, Yar Muhammad Uwaim loves you!!!";
        if (write(fd[1], msg, sizeof(msg)) != sizeof(msg))
        {
            perror("write");
            return 1;
        }
        close(fd[1]); // closing the write end is MANDATORY, otherwise RACE CONDITIONS can occur
        waitpid(pid, NULL, 0);
    }

    return 0;
}