#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_BUF 1024

int main()
{
    int fd;
    const char * gMpufifo = "/tmp/mpu.6050.fifo";
    char buf[MAX_BUF];

    /* open, read, and display the message from the FIFO */
    fd = open(gMpufifo, O_RDONLY);
    read(fd, buf, MAX_BUF);
    printf("Received: %s\n", buf);
    close(fd);

    return 0;
}
