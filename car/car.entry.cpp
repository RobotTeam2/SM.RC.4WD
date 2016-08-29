#include <string>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <list>
#include <thread>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/asio/serial_port.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/read.hpp>
using namespace::boost::asio;


#define DUMP_VAR(x) std::cout << __func__ << #x << "=<" << x <<">" << std::endl;

std::list<std::string> gCarCommand;

std::mutex mtx;
std::condition_variable cv;

void push_command(const std::string &cmd)
{
   std::unique_lock<std::mutex> lock(mtx);
   if("init"==cmd) {
      gCarCommand.clear();
   }
   if("top"==cmd) {
      gCarCommand.push_back("a.speed:10000\n");
      gCarCommand.push_back("a.turn:fwd\n");
      gCarCommand.push_back("b.speed:10000\n");
      gCarCommand.push_back("b.turn:fwd\n");
      gCarCommand.push_back("c.speed:10000\n");
      gCarCommand.push_back("c.turn:fwd\n");
      gCarCommand.push_back("d.speed:10000\n");
      gCarCommand.push_back("d.turn:fwd\n");
      gCarCommand.push_back("run\n");
   }
   if("buttom"==cmd) {
      gCarCommand.push_back("a.speed:10000\n");
      gCarCommand.push_back("a.turn:rev\n");
      gCarCommand.push_back("b.speed:10000\n");
      gCarCommand.push_back("b.turn:rev\n");
      gCarCommand.push_back("c.speed:10000\n");
      gCarCommand.push_back("c.turn:rev\n");
      gCarCommand.push_back("d.speed:10000\n");
      gCarCommand.push_back("d.turn:rev\n");
      gCarCommand.push_back("run\n");
   }
   if("left"==cmd) {
      gCarCommand.push_back("a.speed:10000\n");
      gCarCommand.push_back("a.turn:fwd\n");
      gCarCommand.push_back("b.speed:10000\n");
      gCarCommand.push_back("b.turn:rev\n");
      gCarCommand.push_back("c.speed:10000\n");
      gCarCommand.push_back("c.turn:fwd\n");
      gCarCommand.push_back("d.speed:10000\n");
      gCarCommand.push_back("d.turn:rev\n");
      gCarCommand.push_back("run\n");
   }
   if("right"==cmd) {
      gCarCommand.push_back("a.speed:10000\n");
      gCarCommand.push_back("a.turn:rev\n");
      gCarCommand.push_back("b.speed:10000\n");
      gCarCommand.push_back("b.turn:fwd\n");
      gCarCommand.push_back("c.speed:10000\n");
      gCarCommand.push_back("c.turn:rev\n");
      gCarCommand.push_back("d.speed:10000\n");
      gCarCommand.push_back("d.turn:fwd\n");
      gCarCommand.push_back("run\n");
   }
   if("stop"==cmd) {
      gCarCommand.push_back("stop\n");
   }
   cv.notify_one();
}

void read_dummy()
{
  ::system("cat /dev/ttyUSB0");
}



void handle_read_content(){
   static int i = 0;
   DUMP_VAR(i++);
}


void car_uart_main(void)
{
    io_service io_;
    serial_port port_( io_, "/dev/ttyUSB0" );
    port_.set_option( serial_port_base::baud_rate(115200));
    //std::thread thr_read(read_dummy);
    //thr_read.detach();
    while(true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock);
        if(false == gCarCommand.empty()) {
           for(auto cmd:gCarCommand) {
              boost::asio::write(port_, boost::asio::buffer(cmd.c_str(), cmd.size()));
              boost::asio::streambuf b;
              boost::asio::async_read(port_,b,boost::bind(&handle_read_content));
           }
           gCarCommand.clear();
        }
    }
}

