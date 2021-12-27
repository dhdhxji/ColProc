#ifndef UTIL_H
#define UTIL_H


#include <stdint.h>

uint32_t hash(uint32_t data, uint32_t min, uint32_t max);

void hsv2rgb(uint32_t h, uint32_t s, uint32_t v, uint8_t *r, uint8_t *g, uint8_t *b);
#endif // UTIL_H
