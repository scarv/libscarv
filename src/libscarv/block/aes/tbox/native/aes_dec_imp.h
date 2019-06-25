#ifndef __LIBSCARV_AES_DEC_IMP_H
#define __LIBSCARV_AES_DEC_IMP_H

#define AES_DEC_RND_INIT() {                                                 \
  t_0 = rkp[ 0 ] ^ t_0;                                                      \
  t_1 = rkp[ 1 ] ^ t_1;                                                      \
  t_2 = rkp[ 2 ] ^ t_2;                                                      \
  t_3 = rkp[ 3 ] ^ t_3;                                                      \
                                                                             \
  rkp -= AES_128_NB;                                                         \
}
#define AES_DEC_RND_ITER() {                                                 \
  t_4 = rkp[ 0 ] ^ ( AES_DEC_TBOX_0[ ( t_0 >>  0 ) & 0xFF ]              ) ^ \
                   ( AES_DEC_TBOX_1[ ( t_3 >>  8 ) & 0xFF ]              ) ^ \
                   ( AES_DEC_TBOX_2[ ( t_2 >> 16 ) & 0xFF ]              ) ^ \
                   ( AES_DEC_TBOX_3[ ( t_1 >> 24 ) & 0xFF ]              ) ; \
  t_5 = rkp[ 1 ] ^ ( AES_DEC_TBOX_0[ ( t_1 >>  0 ) & 0xFF ]              ) ^ \
                   ( AES_DEC_TBOX_1[ ( t_0 >>  8 ) & 0xFF ]              ) ^ \
                   ( AES_DEC_TBOX_2[ ( t_3 >> 16 ) & 0xFF ]              ) ^ \
                   ( AES_DEC_TBOX_3[ ( t_2 >> 24 ) & 0xFF ]              ) ; \
  t_6 = rkp[ 2 ] ^ ( AES_DEC_TBOX_0[ ( t_2 >>  0 ) & 0xFF ]              ) ^ \
                   ( AES_DEC_TBOX_1[ ( t_1 >>  8 ) & 0xFF ]              ) ^ \
                   ( AES_DEC_TBOX_2[ ( t_0 >> 16 ) & 0xFF ]              ) ^ \
                   ( AES_DEC_TBOX_3[ ( t_3 >> 24 ) & 0xFF ]              ) ; \
  t_7 = rkp[ 3 ] ^ ( AES_DEC_TBOX_0[ ( t_3 >>  0 ) & 0xFF ]              ) ^ \
                   ( AES_DEC_TBOX_1[ ( t_2 >>  8 ) & 0xFF ]              ) ^ \
                   ( AES_DEC_TBOX_2[ ( t_1 >> 16 ) & 0xFF ]              ) ^ \
                   ( AES_DEC_TBOX_3[ ( t_0 >> 24 ) & 0xFF ]              ) ; \
                                                                             \
  rkp -= AES_128_NB; t_0 = t_4; t_1 = t_5; t_2 = t_6; t_3 = t_7;             \
}
#define AES_DEC_RND_FINI() {                                                 \
  t_4 = rkp[ 0 ] ^ ( AES_DEC_TBOX_4[ ( t_0 >>  0 ) & 0xFF ] & 0x000000FF ) ^ \
                   ( AES_DEC_TBOX_4[ ( t_3 >>  8 ) & 0xFF ] & 0x0000FF00 ) ^ \
                   ( AES_DEC_TBOX_4[ ( t_2 >> 16 ) & 0xFF ] & 0x00FF0000 ) ^ \
                   ( AES_DEC_TBOX_4[ ( t_1 >> 24 ) & 0xFF ] & 0xFF000000 ) ; \
  t_5 = rkp[ 1 ] ^ ( AES_DEC_TBOX_4[ ( t_1 >>  0 ) & 0xFF ] & 0x000000FF ) ^ \
                   ( AES_DEC_TBOX_4[ ( t_0 >>  8 ) & 0xFF ] & 0x0000FF00 ) ^ \
                   ( AES_DEC_TBOX_4[ ( t_3 >> 16 ) & 0xFF ] & 0x00FF0000 ) ^ \
                   ( AES_DEC_TBOX_4[ ( t_2 >> 24 ) & 0xFF ] & 0xFF000000 ) ; \
  t_6 = rkp[ 2 ] ^ ( AES_DEC_TBOX_4[ ( t_2 >>  0 ) & 0xFF ] & 0x000000FF ) ^ \
                   ( AES_DEC_TBOX_4[ ( t_1 >>  8 ) & 0xFF ] & 0x0000FF00 ) ^ \
                   ( AES_DEC_TBOX_4[ ( t_0 >> 16 ) & 0xFF ] & 0x00FF0000 ) ^ \
                   ( AES_DEC_TBOX_4[ ( t_3 >> 24 ) & 0xFF ] & 0xFF000000 ) ; \
  t_7 = rkp[ 3 ] ^ ( AES_DEC_TBOX_4[ ( t_3 >>  0 ) & 0xFF ] & 0x000000FF ) ^ \
                   ( AES_DEC_TBOX_4[ ( t_2 >>  8 ) & 0xFF ] & 0x0000FF00 ) ^ \
                   ( AES_DEC_TBOX_4[ ( t_1 >> 16 ) & 0xFF ] & 0x00FF0000 ) ^ \
                   ( AES_DEC_TBOX_4[ ( t_0 >> 24 ) & 0xFF ] & 0xFF000000 ) ; \
                                                                             \
  rkp -= AES_128_NB; t_0 = t_4; t_1 = t_5; t_2 = t_6; t_3 = t_7;             \
}

#endif
