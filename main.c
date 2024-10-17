#include "uart.h"
#include <xc.h>

int main(){
    uart_init(16000000UL, 115200);
