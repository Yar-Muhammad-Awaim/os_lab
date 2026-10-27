#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int fd[2];
    pipe(fd);
    // after pipe, fd[0] is now the reader end, fd[1] is the writer end

    write(fd[1], "Hello\n", 6);

    char msg[20] = {0};

    read(fd[0], msg, 6);

    printf("%s", msg);

    close(fd[0]);
    close(fd[1]);
    return 0;
}