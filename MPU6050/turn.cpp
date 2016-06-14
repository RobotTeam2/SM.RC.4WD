#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/socket.h> 
#include <sys/un.h> 
#include <errno.h> 
 
#define MAX_BUF 1024

int main()
{
    int fd = socket( AF_LOCAL, SOCK_DGRAM, 0 );
	
	struct sockaddr_un addr;
	bzero( &addr, sizeof(addr) );
	addr.sun_family = AF_LOCAL;
	strcpy( addr.sun_path, "/tmp/mpu.6050.unix.domain" );
	
    char buf[MAX_BUF];
    
   if(::bind(fd, (struct sockaddr*)&addr, sizeof(addr)) < 0)
   {

     printf(" cannot bind socket: %d. Passed in address is invalid or port is in use",errno);

     return 0;

   }

    int degree = 90;
    while(degree >0) {
    	socklen_t len = sizeof(addr);
        int ret = ::recvfrom(fd, buf, MAX_BUF, 0, (struct sockaddr *)&addr, &len);
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
