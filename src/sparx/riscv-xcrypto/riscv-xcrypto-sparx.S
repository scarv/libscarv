
.text

.global sparx_encrypt_64_128
.func
// void sparx_encrypt_64_128(uint16_t * x, uint16_t k[][2*3])
// 
#define N_STEPS            8
#define ROUNDS_PER_STEPS   3
#define N_BRANCHES         2
#define K_SIZE             4
// 
// Length of x (in a0) = 2*N_BRANCHES = 4 * 16-bit
// Length of k (in a1) = [N_BRANCHES*N_STEPS+1][2*ROUNDS_PER_STEPS]
//                     = [       17           ][       6          ]
// 
sparx_encrypt_64_128:

   xc.ld.hu    c4,(0),0(a0)
   addi    t3,a1,12
   addi    t5,a1,204
   addi    t4,a0,8

   spx_l4:
        mv    a6,a0
        mv    a7,t3

   spx_l3:
        xc.ld.hu    c5,(0),2(a6)
        addi    a2,a7,-12

   spx_l1:
       xc.ld.hu    c3,(0),0(a2)
       addi    a2,a2,4
       xc.bop      c4,c4,c3,0x66
       xc.st.h    c4,(0),0(a6)
       xc.ld.hu    c1,(0),-2(a2)
       xc.prot.i  h,c4,c4,16-9
       xc.bop     c5,c5,c1,0x66
       xc.padd    h, c4,c4,c5
       xc.prot.i h,c5,c5,16-2
       xc.bop     c5,c5,c4,0x66
       xc.st.h    c4,(0),0(a6)
       xc.st.h    c5,(0),2(a6)

       bne    a7,a2, spx_l1

       addi    a6,a6,4
       addi    a7,a7,12

       beq    a6,t4,spx_l2

       xc.ld.hu    c4,(0),0(a6)
       j    spx_l3

   spx_l2:

      xc.ld.hu   c6,(0),0(a0)
      xc.ld.hu   c2,(0),2(a0)
      xc.ld.hu   c4,(0),4(a0)
      xc.ld.hu   c7,(0),6(a0)
      xc.bop     c3,c6,c2,0x66
      xc.prot.i  h,c5,c3,8
      xc.bop     c4,c5,c6, 0x96
      xc.bop     c5,c2,c7, 0x96
      xc.st.h    c4,(0),0(a0)
      xc.st.h    c6,(0),4(a0)
      xc.st.h    c5,(0),2(a0)
      xc.st.h    c2,(0),6(a0)
      addi    t3,t3,24

      bne    t5,t3,spx_l4

      xc.ld.hu   c3,(0),192(a1)
      xc.bop     c4,c4,c3,0x66
      xc.st.h    c4,(0),0(a0)
      xc.ld.hu   c4,(0),194(a1)
      xc.bop     c5,c5,c4,0x66
      xc.st.h    c5,(0),2(a0)
      xc.ld.hu   c5,(0),196(a1)
      xc.bop     c6,c6,c5,0x66
      xc.st.h    c6,(0),4(a0)
      xc.ld.hu   c5,(0),198(a1)
      xc.bop     c2,c2,c5,0x66
      xc.st.h    c2,(0),6(a0)

    ret

.endfunc
