#include "uart.h"
#include "ringbuf.h"
#include <xc.h>

static ringbuf_t txrb, rxrb;

void uart_init(uint32_t pbclk, uint32_t baud){
