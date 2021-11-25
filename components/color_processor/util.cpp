#include "colproc/util/util.h"

uint32_t hash(uint32_t data, uint32_t out_min, uint32_t out_max) {
    //Ref: https://stackoverflow.com/questions/664014/what-integer-hash-function-are-good-that-accepts-an-integer-hash-key
    data = ((data >> 16) ^ data) * 0x45d9f3b;
    data = ((data >> 16) ^ data) * 0x45d9f3b;
    data = (data >> 16) ^ data;

    return (data-out_min)%(out_max-out_min) + out_min;
}