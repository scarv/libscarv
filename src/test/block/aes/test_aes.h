#ifndef __TEST_AES_H
#define __TEST_AES_H

#include "util.h"

#if ( CONF_AES_ENC_ENABLE )
#include <scarv/block/aes/aes_enc.h>
#endif
#if ( CONF_AES_DEC_ENABLE )
#include <scarv/block/aes/aes_dec.h>
#endif

#endif
