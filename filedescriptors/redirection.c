#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
    int fd = open("hello.txt", O_WRONLY | O_TRUNC | O_CREAT, 0644);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("dup2");
        close(fd);
        return 1;
    }

    close(fd);

    if (write(STDOUT_FILENO, "OK\n", 3) != 3)
    {
        perror("write");
        return 1;
    }

    return 0;
}