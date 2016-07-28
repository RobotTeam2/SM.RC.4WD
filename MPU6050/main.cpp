#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
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

#define YAW360(x) (x>0 ? x*2:360 + x*2)


#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::udp;


int main() {
  ms_open();
  boost::asio::io_service io_service_;
  udp::socket socket(io_service_,udp::endpoint(udp::v4(), 0));

  udp::resolver resolver_(io_service_);
  udp::resolver::query query_(udp::v4(), "localhost", 41235);
  udp::resolver::iterator iter = resolver_.resolve(query_);
  udp::endpoint endpoint_ = *iter;
  do{
    ms_update();
    char buff[256] = {0};
    sprintf(buff, "{\"yaw\":%f,\"pitch\":%f,\"roll\":%f,\"temperature\":%f}\n", YAW360(ypr[YAW]), ypr[PITCH],ypr[ROLL],temp);
    socket_.send_to(boost::asio::buffer(buff, strlen(buff)), endpoint_);
    printf("{\"yaw\":%f,\"pitch\":%f,\"roll\":%f,\"temperature\":%f}\n", YAW360(ypr[YAW]), ypr[PITCH],ypr[ROLL],temp);
    delay_ms(1);
  }while(1);
  return 0;
}
