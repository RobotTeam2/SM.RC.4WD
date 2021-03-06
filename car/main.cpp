#include <string>
#include <iostream>
#include <thread>

#define DUMP_VAR(x) std::cout << #x << "=<" << x <<">" << std::endl;
extern void ble_ws_upd_main(void);
extern void mpu_udp_main(void);
extern void car_uart_main(void);

int main(int argc, char * argv[])
{     
    DUMP_VAR(argc);
    std::thread ble_udp_thd(ble_ws_upd_main);
    std::thread mpu_udp_thd(mpu_udp_main);
    std::thread car_uart_thd(car_uart_main);
    

    car_uart_thd.join();
    mpu_udp_thd.join();
    ble_udp_thd.join();
    return 0;
}

