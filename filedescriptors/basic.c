#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
    int fd = open("hello.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    // the flags above mean
    // O_WRONLY = Open file in writing mode
    // O_CREAT = Create file if it doesn't exist
    // O_TRUNC = Truncate file if it already exist
    // 0644 -> sets the file permissions

    printf("fd = %d\n", fd);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    write(fd, "Hello from YAR MUHAMMAD UWAIM.\n", 31);

    if (close(fd) == -1)
    {
        perror("close");
        return 1;
    }

    return 0;
}