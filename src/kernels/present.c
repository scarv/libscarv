
#include "present.h"

#ifndef CONF_KERNELS_PRESENT_SLAYER_EXTERN
/*
@details Slow, C implementation of the present substitution layer.
*/
uint64_t present_slayer(uint64_t in){

    uint64_t out = 0;
    
    for(uint8_t i = 0; i < 63; i ++) {
        
        uint64_t pos = (16*i)%63;

        out |= ((in >> i) & 0x1) << pos;

    }
        
    out |= ((in >> 63) & 0x1) << 63;

    return out;

}
#endif
