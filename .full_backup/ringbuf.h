#ifndef RINGBUF_H
#define RINGBUF_H
#include <stdint.h>
#define RB_SIZE 128
typedef struct { volatile uint8_t buf[RB_SIZE]; volatile uint16_t head, tail; } ringbuf_t;
static inline void rb_init(ringbuf_t* r){ r->head=r->tail=0; }
