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


#include "MotionSensor.h"

#define delay_ms(a) usleep(a*1000)


int main() {
	ms_open();

	const char * gMpufifo = "/tmp/mpu.6050.fifo";
	int fd = socket( AF_LOCAL, SOCK_DGRAM, 0 );
	sockaddr_un addr = SOCKADDR_UN_INIT( AF_LOCAL, gMpufifo );
	do{
		ms_update();
		printf("yaw = %5.4f\tpitch = %5.4f\troll = %5.4f\ttemperature = %5.4f\n",
		 ypr[YAW], ypr[PITCH],ypr[ROLL],temp);
		 char buff[256];
		 sprintf(buff, "{yaw:%f,pitch:%f,roll:%f,temperature:%f}\n", ypr[YAW], ypr[PITCH],ypr[ROLL],temp);
		 sendto(fd, buff, strlen(buff), 0, (sockadrr*)&addr, sizeof(addr) );
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
