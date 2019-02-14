#ifndef __AES_DEC_IMP_H
#define __AES_DEC_IMP_H

#include "scarv/util.h"

#include "scarv/aes/aes_conf.h"
#include "scarv/aes/aes_mulx.h"

#include "scarv/aes/aes_dec.h"

extern void aes_dec_rnd_key( uint8_t* s, const uint8_t* rk );
extern void aes_dec_rnd_sub( uint8_t* s                    );
extern void aes_dec_rnd_row( uint8_t* s                    );
extern void aes_dec_rnd_mix( uint8_t* s                    );

#endif

