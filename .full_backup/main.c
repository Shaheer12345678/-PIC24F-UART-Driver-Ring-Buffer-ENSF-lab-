#include "uart.h"
#include <xc.h>

int main(){
    uart_init(16000000UL, 115200);
    const char* msg = "UART echo ready\r\n";
    for (const char* p=msg; *p; ++p) uart_write(*p);
    while(1){
        uint8_t b;
        if (uart_read(&b)){
            uart_write(b); // echo
        }
    }
    return 0;
}
