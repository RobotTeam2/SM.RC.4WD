#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


#include "MotionSensor.h"

#define delay_ms(a) usleep(a*1000)


int main() {
	int fd;
	const char * gMpufifo = "/tmp/mpu.6050.fifo";
	ms_open();
	mkfifo(gMpufifo, 0666);
	fd = open(gMpufifo, O_WRONLY);
	do{
		ms_update();
		printf("yaw = %5.4f\tpitch = %5.4f\troll = %5.4f\ttemperature = %5.4f\n",
		 ypr[YAW], ypr[PITCH],ypr[ROLL],temp);
		 fprintf(fd, "{yaw:%f,pitch:%f,roll:%f,temperature:%f}\n", ypr[YAW], ypr[PITCH],ypr[ROLL],temp);
#if 0
		printf("yaw = %5.4f\tpitch = %4.5f\troll = %5.4f\ttemperature = %5.4f\n",
		 gyro[YAW], gyro[PITCH],
		 gyro[ROLL],temp);
#endif
		delay_ms(1);
	}while(1);
	close(fd);
	unlink(gMpufifo);

	return 0;
}
