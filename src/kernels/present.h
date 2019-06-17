
#include <stdint.h>

#ifndef KERNELS_PRESENT_H
#define KERNELS_PRESENT_H

/*
@brief Implements the present block cipher substitution layer.
@param in - The input 64-bit present state
@returns The permuted state.
*/
uint64_t present_slayer(uint64_t in);

#endif

