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

#include <boost/algorithm/string.hpp>


#define DUMP_VAR(x) std::cout << __func__ << #x << "=<" << x <<">" << std::endl;

std::list<std::string> gCarCommand;

std::mutex mtx;
std::condition_variable cv;
static std::string gCarSpeed = "10000";

void push_command(const std::string &cmd)
{
   std::unique_lock<std::mutex> lock(mtx);
   if("init"==cmd) {
      gCarCommand.clear();
   }
   if("top"==cmd) {
      gCarCommand.push_back("a.speed:" + gCarSpeed + "\n");
      gCarCommand.push_back("a.turn:fwd\n");
      gCarCommand.push_back("b.speed:" + gCarSpeed + "\n");
      gCarCommand.push_back("b.turn:fwd\n");
      gCarCommand.push_back("c.speed:" + gCarSpeed + "\n");
      gCarCommand.push_back("c.turn:fwd\n");
      gCarCommand.push_back("d.speed:" + gCarSpeed + "\n");
      gCarCommand.push_back("d.turn:fwd\n");
      gCarCommand.push_back("run\n");
   }
   if("buttom"==cmd) {
      gCarCommand.push_back("a.speed:" + gCarSpeed + "\n");
      gCarCommand.push_back("a.turn:rev\n");
      gCarCommand.push_back("b.speed:" + gCarSpeed + "\n");
      gCarCommand.push_back("b.turn:rev\n");
      gCarCommand.push_back("c.speed:" + gCarSpeed + "\n");
      gCarCommand.push_back("c.turn:rev\n");
      gCarCommand.push_back("d.speed:" + gCarSpeed + "\n");
      gCarCommand.push_back("d.turn:rev\n");
      gCarCommand.push_back("run\n");
   }
   if("left"==cmd) {
      gCarCommand.push_back("a.speed:" + gCarSpeed + "\n");
      gCarCommand.push_back("a.turn:fwd\n");
      gCarCommand.push_back("b.speed:" + gCarSpeed + "\n");
      gCarCommand.push_back("b.turn:rev\n");
      gCarCommand.push_back("c.speed:" + gCarSpeed + "\n");
      gCarCommand.push_back("c.turn:fwd\n");
      gCarCommand.push_back("d.speed:" + gCarSpeed + "\n");
      gCarCommand.push_back("d.turn:rev\n");
      gCarCommand.push_back("run\n");
   }
   if("right"==cmd) {
      gCarCommand.push_back("a.speed:" + gCarSpeed + "\n");
      gCarCommand.push_back("a.turn:rev\n");
      gCarCommand.push_back("b.speed:" + gCarSpeed + "\n");
      gCarCommand.push_back("b.turn:fwd\n");
      gCarCommand.push_back("c.speed:" + gCarSpeed + "\n");
      gCarCommand.push_back("c.turn:rev\n");
      gCarCommand.push_back("d.speed:" + gCarSpeed + "\n");
      gCarCommand.push_back("d.turn:fwd\n");
      gCarCommand.push_back("run\n");
   }
   if("stop"==cmd) {
      gCarCommand.push_back("stop\n");
   }
   std::string speedTag("speed=");
   auto posSpd = cmd.find(speedTag);
   if(posSpd != std::string::npos) {
      auto speedStr = cmd.substr(posSpd + speedTag.size());
      DUMP_VAR(speedStr);
      auto speed = std::stoi(speedStr);
      DUMP_VAR(speed);
   }
   cv.notify_one();
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


