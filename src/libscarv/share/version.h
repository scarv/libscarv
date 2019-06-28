/* Copyright (C) 2019 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#ifndef __LIBSCARV_VERSION_H
#define __LIBSCARV_VERSION_H

#define __STR(x)      #x
#define   STR(x) __STR(x)

#define LIBSCARV_VERSION_MAJOR ( 0 )
#define LIBSCARV_VERSION_MINOR ( 1 )
#define LIBSCARV_VERSION_PATCH ( 0 )

#define LIBSCARV_VERSION STR(LIBSCARV_VERSION_MAJOR) "." STR(LIBSCARV_VERSION_MINOR) "." STR(LIBSCARV_VERSION_PATCH)

#endif
