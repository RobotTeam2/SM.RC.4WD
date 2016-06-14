#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/socket.h> 
#include <sys/un.h> 
 
#define MAX_BUF 1024

int main()
{
    int fd = socket( AF_LOCAL, SOCK_DGRAM, 0 );
	
	struct sockaddr_un addr;
	bzero( &addr, sizeof(addr) );
	addr.sun_family = AF_LOCAL;
	strcpy( addr.sun_path, "/tmp/mpu.6050.unix.domain" );
	
    char buf[MAX_BUF];

    /* open, read, and display the message from the FIFO */
    fd = open(gMpufifo, O_RDONLY|O_NONBLOCK);
    int degree = 90;
    while(degree >0) {
        int ret = ::recvfrom(fd, buf, MAX_BUF, 0, (struct sockaddr *)addr, sizeof(addr));
        if(ret>0){
            printf("Received: %s\n", buf);
        } else if (ret==0){
        } else {
            printf("ret=<%d>\n",ret);
        }
    }
    close(fd);

    return 0;
}
