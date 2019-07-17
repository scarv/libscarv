/* Copyright (C) 2019 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which
 * can be found at https://opensource.org/licenses/MIT (or should be included
 * as LICENSE.txt within the associated archive or repository).
 */

#ifndef __LIBSCARV_CHACHA20_IMP_H
#define __LIBSCARV_CHACHA20_IMP_H

#include "scarv/share/conf.h"

#if ( !LIBSCARV_CONF_XCRYPTO_CLASS_1   )
#error "no implementation for !LIBSCARV_CONF_XCRYPTO_1"
#endif
#if ( !LIBSCARV_CONF_XCRYPTO_CLASS_2_3 )
#error "no implementation for !LIBSCARV_CONF_XCRYPTO_2_3"
#endif
#if ( !LIBSCARV_CONF_XCRYPTO_CLASS_2_4 )
#error "no implementation for !LIBSCARV_CONF_XCRYPTO_2_4"
#endif

#endif

