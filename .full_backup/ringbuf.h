#ifndef RINGBUF_H
#define RINGBUF_H
#include <stdint.h>
#define RB_SIZE 128
typedef struct { volatile uint8_t buf[RB_SIZE]; volatile uint16_t head, tail; } ringbuf_t;
static inline void rb_init(ringbuf_t* r){ r->head=r->tail=0; }
static inline uint16_t rb_count(const ringbuf_t* r){ return (r->head - r->tail) & (RB_SIZE-1); }
static inline uint8_t rb_push(ringbuf_t* r, uint8_t v){
    uint16_t n = (r->head + 1) & (RB_SIZE-1);
    if (n == r->tail) return 0;
    r->buf[r->head] = v; r->head = n; return 1;
