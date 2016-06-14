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
#include <string>
using namespace std;
#include <boost/property_tree/json_parser.hpp>

static int fd = -1;
#include <signal.h>
#include <stdio.h>
void sigcatch(int) {
	if(fd > 0) {
		close(fd);
	}
	exit(0);
}
int main(int ac,char*av[])
{
	if (SIG_ERR == signal(SIGINT, sigcatch)) {
		printf("failed to set signal handler.n");
		exit(1);
	}
     fd = socket( AF_LOCAL, SOCK_DGRAM, 0 );
	
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

     printf(" cannot bind socket: %d. \n",errno);
     close(fd);

     return 0;

   }

    char buf[MAX_BUF];
    double degree = 20.0;
    double startDeg = 0.0;
    bool first = true;
    while(degree >0) {
    	socklen_t len = sizeof(addr);
        int ret = ::recvfrom(fd, buf, MAX_BUF, 0, (struct sockaddr *)&addr, &len);
        if(ret>0){
            //printf("Received: %s\n", buf);
            string recvStr(buf,ret);
            //std::cout << recvStr << std::endl;
            std::stringstream ss;
            ss << recvStr;
            try {
            	boost::property_tree::ptree pt;
            	boost::property_tree::read_json(ss, pt);
            	auto current = pt.get<double>("yaw");
            	//std::cout <<  current << std::endl;
            	if(first) {
            		startDeg = current;
            	}
            	auto diff = current - startDeg;
            	std::cout <<  "diff=<" << diff <<">"<< std::endl;
            	if( diff >= degree) {
            		break;
            	}
            } catch(std::exception e) {
            	std::cout << e.what() << std::endl;
            }
        } else if (ret==0){
        } else {
            printf("ret=<%d>\n",ret);
        }
    }
    close(fd);

    return 0;
}
