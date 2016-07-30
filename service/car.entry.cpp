#include <string>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <thread>

#include <boost/asio/serial_port.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/read.hpp>
using namespace::boost::asio;


#define DUMP_VAR(x) std::cout << __func__ << #x << "=<" << x <<">" << std::endl;

std::string gCarCommand("");

std::mutex mtx;
std::condition_variable cv;

void push_command(const std::string &cmd)
{
   std::unique_lock<std::mutex> lock(mtx);
   if(cmd)
   gCarCommand = cmd;
}

void read_dummy()
{
  ::system("cat /dev/ttyUSB0");
}






void car_uart_main(void)
{
    io_service io_;
    serial_port port_( io_, "/dev/ttyUSB0" );
    port_.set_option( serial_port_base::baud_rate( 9600 ) );
    std::thread thr_read(read_dummy);
    thr_read.detach();
    while(true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock);
        if(false == gCarCommand.empty()) {
            boost::asio::write(port_, boost::asio::buffer(gCarCommand.c_str(), gCarCommand.size()));
            gCarCommand = "";
        }
    }
}


