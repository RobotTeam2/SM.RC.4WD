#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>



#define DUMP_VAR(x) std::cout << __func__<< #x << "=<" << x <<">" << std::endl;

void mpu_udp_main(void)
{     
    using namespace boost::asio::ip;

    boost::asio::io_service io_service;
    udp::socket sock(io_service, udp::endpoint(udp::v4(), 41235));
//    DUMP_VAR(sock);
    while(true)
    {
        boost::array<char, 128> recv_buf;
        udp::endpoint endpoint;
        DUMP_VAR(endpoint);
        size_t len = sock.receive_from(boost::asio::buffer(recv_buf), endpoint);
        //std::cout.write(recv_buf.data(), len);
        std::string recv_str(recv_buf.data(),len); 
        DUMP_VAR(recv_str);
    }
}

