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
#include <chrono>
using namespace std;
#include <boost/property_tree/json_parser.hpp>


const static double PI = 3.14159265;
const static int iConstRound = 60;
const static double iConstRoundLimit = sin(iConstRound*PI/180.0);
const static double dConstDifferMin = 0.001;

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
	system("rm -f /tmp/mpu.6050.unix.domain");
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

	struct timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 1000;
   	if (::setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0) {
	    	perror("setsockopt(SO_RCVTIMEO) failed");
   	}

   if(::bind(fd, (struct sockaddr*)&addr, sizeof(addr)) < 0)
   {

     printf(" cannot bind socket: %d. \n",errno);
     close(fd);

     return 0;

   }

    char buf[MAX_BUF];
    double degree = 90.0;
    if(ac > 1) {
    	degree = ::atof(av[1]);
    }
    degree = std::fabs(degree);
    int iRound = degree/iConstRound;
    double dRemain = degree - (iRound *iConstRound);
    double startDeg = 0.0;
    bool restartBase = true;
    chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    int msRun = 0;
    // 1000 ms 
    while(msRun < 1000) {
    	chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    	msRun = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    	//printf("msRun=<%d>\n",msRun);


    	
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
            	if(restartBase) {
            		startDeg = current;
            		restartBase = false;
            		continue;
            	}
            	double dRoundRad = 0.0;
            	if(iRound >0) {
            		dRoundRad = iConstRoundLimit;
            	} else {
            		dRoundRad = sin(PI*dRemain/180.0);
            	}
            	double diffDeg = std::fabs(current - startDeg);
            	std::cout <<  "diffDeg=<" << diffDeg <<">"<< std::endl;
            	/// over 
            	if(diffDeg > iConstRound) {
            		diffDeg = std::fabs(360 -diffDeg);
            	}
            	std::cout <<  "diffDeg=<" << diffDeg <<">"<< std::endl;
            	double diffRad = (PI*diffDeg/180.0);
            	double diff = dRoundRad - sin(diffRad);
            	std::cout <<  "diff=<" << diff <<">"<< std::endl;
            	if(diff <= dConstDifferMin) {
            		std::cout <<  "iRound=<" << iRound <<">"<< std::endl;
            		if(iRound >0) {
            			iRound--;
	            		restartBase = true;
            		}
            		else {
            			break;
            		}
            	}
            } catch(std::exception e) {
            	std::cout << e.what() << std::endl;
            }
        } else if (ret==0){
        	//printf("ret=<%d>\n",ret);
        } else {
        	//printf("ret=<%d>\n",ret);
        }
    }
    close(fd);

    return 0;
}
