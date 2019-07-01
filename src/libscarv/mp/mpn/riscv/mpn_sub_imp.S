#include "scarv/share/conf.h"

// ============================================================================

.section .text

.global mpn_sub

# limb_t mpn_sub( limb_t* r, const limb_t* x, int l_x, 
#                            const limb_t* y, int l_y );
#
# a0 = limb_t*   r
# a1 = limb_t*   x
# a2 = int     l_x
# a3 = limb_t*   y
# a4 = int     l_y

#if ( LIBSCARV_CONF_MPN_SUB_GUARD  )
mpn_sub: ret
#endif

#if ( LIBSCARV_CONF_MPN_SUB_UNROLL )
mpn_sub: ret
#endif

// ============================================================================
