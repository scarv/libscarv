#ifndef __AES_ENC_IMP_H
#define __AES_ENC_IMP_H

#include <scarv/share/conf.h>
#include <scarv/share/util.h>

#include <scarv/block/aes/aes_conf.h>
#include <scarv/block/aes/aes_mulx.h>

#include <scarv/block/aes/aes_enc.h>

extern void aes_enc_rnd_key( uint8_t* s, const uint8_t* rk );
extern void aes_enc_rnd_sub( uint8_t* s                    );
extern void aes_enc_rnd_row( uint8_t* s                    );
extern void aes_enc_rnd_mix( uint8_t* s                    );

#endif

