#ifndef UART_H
#define UART_H
#include <stdint.h>
void uart_init(uint32_t pbclk, uint32_t baud);
void uart_write(uint8_t b);
int  uart_read(uint8_t* b);
#endif
