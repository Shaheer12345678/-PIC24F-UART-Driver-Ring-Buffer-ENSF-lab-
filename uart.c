#include "uart.h"
#include "ringbuf.h"
#include <xc.h>

static ringbuf_t txrb, rxrb;

void uart_init(uint32_t pbclk, uint32_t baud){
    rb_init(&txrb); rb_init(&rxrb);
    U2MODEbits.BRGH = 0;
    U2BRG = (pbclk/(16*baud)) - 1;
    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;
    IEC1bits.U2RXIE = 1;
