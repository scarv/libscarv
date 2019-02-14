#ifndef __AES_ENC_IMP_H
#define __AES_ENC_IMP_H

#include "scarv/util.h"

#include "scarv/aes/aes_conf.h"
#include "scarv/aes/aes_mulx.h"

#include "scarv/aes/aes_enc.h"

extern void aes_enc_rnd_key( uint8_t* s, const uint8_t* rk );
extern void aes_enc_rnd_sub( uint8_t* s                    );
extern void aes_enc_rnd_row( uint8_t* s                    );
extern void aes_enc_rnd_mix( uint8_t* s                    );

#endif

