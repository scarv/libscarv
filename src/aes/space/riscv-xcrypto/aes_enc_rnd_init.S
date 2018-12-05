
.section .text
.global aes_enc_rnd_init
aes_enc_rnd_init:
    # a0 =  uint32_t * s 
	# a1 =  uint32_t * k
	
	lw t1, 0(a0)
	lw t2, 4(a0)
	lw t3, 8(a0)
	lw t4, 12(a0)

	lw t5, 0(a1)
	xor t1, t1, t5
	lw t5, 4(a1)
	xor t2, t2, t5
	lw t5, 8(a1)
	xor t3, t3, t5
	lw t5, 12(a1)
	xor t4, t4, t5

	sw t1, 0(a0)
	sw t2, 4(a0)
	sw t3, 8(a0)
	sw t4, 12(a0)

	ret
