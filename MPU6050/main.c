#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "MotionSensor.h"

#define delay_ms(a) usleep(a*1000)

int main() {
	ms_open();
	do{
		ms_update();
		#if 1
		printf("yaw = %5.4f\tpitch = %5.4f\troll = %5.4f\ttemperature = %5.4f\n",
		 ypr[YAW], ypr[PITCH],
		 ypr[ROLL],temp);
		#endif

#if 0
		printf("yaw = %5.4f\tpitch = %4.5f\troll = %5.4f\ttemperature = %5.4f\n",
		 gyro[YAW], gyro[PITCH],
		 gyro[ROLL],temp);
#endif
		delay_ms(1);
	}while(1);

	return 0;
}
