	.arch	armv8-a

	.global asm_scale_img
	.type asm_scale_img, %function
	.text
	.align 2

asm_scale_img:
	stp x29,	x30,	[sp, #-16]!
	stp	x20,	x21,	[sp, #-16]!
	stp	x22,	x23,	[sp, #-16]!
	stp	x24,	x25,	[sp, #-16]!
	stp	x26,	x27,	[sp, #-16]!

	scvtf	d0,	w2	// w
	scvtf	d1,	w3	// h
	scvtf	d2,	w4	// nw
	scvtf	d3,	w5	// nh
	fdiv	d0,	d0,	d2	// x_ratio
	fdiv	d1,	d1,	d3	// y_ratio
	
	mov	w10,	#0	// j
0:
	cmp	w10,	w5
	bge	asm_scale_img_end
	mov	w11,	#0	// i
1:
	cmp	w11,	w4
	bge	4f
	mov	w12,	#0	// cc

	scvtf	d2,	w10	// j
	scvtf	d3,	w11	// i

	fmul	d4,	d3,	d0	// i * x_ratio
	fmul	d5,	d2,	d1	// j * y_ratio
	fcvtms	x20,	d4	//	floor x
	fcvtms	x21,	d5	//	floor y
2:
	cmp	w12,	w6
	bge	3f

	madd	w13,	w10,	w4,		w11
	madd	x13,	x13,	x6,		x12
	madd	w14,	w21,	w2,		w20
	madd	x14,	x14,	x6,		x12
	ldrb	w15,	[x0,	x14]
	strb	w15,	[x1,	x13]
	add		w12,	w12,	#1
	b	2b
3:
	add	w11,	w11,	#1
	b	1b
4:
	add	w10,	w10,	#1
	b	0b

asm_scale_img_end:
	ldp	x26,	x27,	[sp],	#16
	ldp	x24,	x25,	[sp],	#16
	ldp	x22,	x23,	[sp],	#16
	ldp	x20,	x21,	[sp],	#16
	ldp	x29,	x30,	[sp],	#16
	mov	x0,	x1
	ret
	.size asm_scale_img, .-asm_scale_img
	
