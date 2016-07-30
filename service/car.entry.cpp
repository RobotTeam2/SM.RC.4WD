#include <string>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <atomic>

#include <boost/asio/serial_port.hpp>
using namespace::boost::asio;


#define DUMP_VAR(x) std::cout << __func__ << #x << "=<" << x <<">" << std::endl;

std::string gCarCommand("");

std::mutex mtx;
std::condition_variable cv;


void car_uart_main(void)
{
    io_service io_;
    serial_port port_( io_, "/dev/ttyUSB0" );
    port_.set_option( serial_port_base::baud_rate( 9600 ) );
    while(true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock);
        if(false == gCarCommand.empty()) {
            boost::asio::write(port, boost::asio::buffer(gCarCommand, gCarCommand.size()));
        }
    }
}

