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
    IEC1bits.U2TXIE = 1;
    U2MODEbits.UARTEN = 1;
}

void uart_write(uint8_t b){
    if (!rb_push(&txrb, b)) return;
    IEC1bits.U2TXIE = 1;
}

int uart_read(uint8_t* b){
    return rb_pop(&rxrb, b);
}

void __attribute__((interrupt, no_auto_psv)) _U2RXInterrupt(void){
    IFS1bits.U2RXIF = 0;
    while (U2STAbits.URXDA){
        rb_push(&rxrb, U2RXREG);
    }
}
void __attribute__((interrupt, no_auto_psv)) _U2TXInterrupt(void){
    IFS1bits.U2TXIF = 0;
    uint8_t v;
    if (rb_pop(&txrb, &v)){
        U2TXREG = v;
        IEC1bits.U2TXIE = 1;
