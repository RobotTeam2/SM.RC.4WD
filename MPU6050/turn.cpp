#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/socket.h> 
#include <sys/un.h> 
#include <errno.h> 
 
#define MAX_BUF 1024

#include <sstream>
#include <iostream>
#include <boost/property_tree/json_parser.hpp>

int main()
{
    int fd = socket( AF_LOCAL, SOCK_DGRAM, 0 );
	
	struct sockaddr_un addr;
	bzero( &addr, sizeof(addr) );
	addr.sun_family = AF_LOCAL;
	strcpy( addr.sun_path, "/tmp/mpu.6050.unix.domain" );
	
   int use = 1; 
   if (::setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &use, sizeof(int)) < 0) {
    perror("setsockopt(SO_REUSEADDR) failed");
   }
   if(::bind(fd, (struct sockaddr*)&addr, sizeof(addr)) < 0)
   {

     printf(" cannot bind socket: %d. Passed in address is invalid or port is in use",errno);

     return 0;

   }

    char buf[MAX_BUF];
    int degree = 90;
    while(degree >0) {
    	socklen_t len = sizeof(addr);
        int ret = ::recvfrom(fd, buf, MAX_BUF, 0, (struct sockaddr *)&addr, &len);
        if(ret>0){
            //printf("Received: %s\n", buf);
            std::stringstream ss;
            ss << buf;
            boost::property_tree::ptree pt;
            boost::property_tree::read_json(ss, pt);
            std::cout << pt.get<double>("yaw") << std::endl;
        } else if (ret==0){
        } else {
            printf("ret=<%d>\n",ret);
        }
    }
    close(fd);

    return 0;
}
