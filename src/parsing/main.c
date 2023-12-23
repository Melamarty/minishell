#include <stdio.h>
#include <fcntl.h>
#include "parsing.h"
int is_fd_closed(int fd)
{
    int flags = fcntl(fd, F_GETFD);
    return (flags == -1);
}

int main()
{
    int fd = 0;  // File descriptor 0 represents standard input (stdin)
	close(fd);
    if (is_fd_closed(fd))
    {
        printf("File descriptor %d is closed.\n", fd);
    }
    else
    {
        printf("File descriptor %d is open.\n", fd);
    }

    return 0;
}