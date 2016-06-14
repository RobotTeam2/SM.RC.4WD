#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>


#include "MotionSensor.h"

#define delay_ms(a) usleep(a*1000)


int main() {
	ms_open();

	int fd = socket( AF_LOCAL, SOCK_DGRAM, 0 );
	
	struct sockaddr_un addr;
	bzero( &addr, sizeof(addr) );
	addr.sun_family = AF_LOCAL;
	strcpy( addr.sun_path, "/tmp/mpu.6050.unix.domain" );
	
	int yes = 1; 
   if (::setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) < 0) {
    perror("setsockopt(SO_REUSEADDR) failed\n");
   }
	
	do{
		ms_update();
		printf("yaw = %5.4f\tpitch = %5.4f\troll = %5.4f\ttemperature = %5.4f\n",
		 ypr[YAW], ypr[PITCH],ypr[ROLL],temp);
		 char buff[256] = {0};
		 sprintf(buff, "{yaw:%f,pitch:%f,roll:%f,temperature:%f}\n", ypr[YAW], ypr[PITCH],ypr[ROLL],temp);
		 sendto(fd, buff, strlen(buff), 0, (struct sockaddr *)&addr, sizeof(addr) );
#if 0
		printf("yaw = %5.4f\tpitch = %4.5f\troll = %5.4f\ttemperature = %5.4f\n",
		 gyro[YAW], gyro[PITCH],
		 gyro[ROLL],temp);
#endif
		delay_ms(1);
	}while(1);
	close(fd);
	return 0;
}
