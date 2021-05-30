	.text
	.globl	aes_128_key_expansion
	.type	aes_128_key_expansion, @function
aes_128_key_expansion:
.LFB507:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$40, %rsp
	movaps	%xmm0, -144(%rbp)
	movaps	%xmm1, -160(%rbp)
	movdqa	-160(%rbp), %xmm0
	pshufd	$255, %xmm0, %xmm0
	movaps	%xmm0, -160(%rbp)
	movdqa	-144(%rbp), %xmm0
	pslldq	$4, %xmm0
	movdqa	%xmm0, %xmm1
	movdqa	-144(%rbp), %xmm0
	movaps	%xmm0, -32(%rbp)
	movaps	%xmm1, -16(%rbp)
	movdqa	-32(%rbp), %xmm1
	movdqa	-16(%rbp), %xmm0
	pxor	%xmm1, %xmm0
	movaps	%xmm0, -144(%rbp)
	movdqa	-144(%rbp), %xmm0
	pslldq	$4, %xmm0
	movdqa	%xmm0, %xmm1
	movdqa	-144(%rbp), %xmm0
	movaps	%xmm0, -64(%rbp)
	movaps	%xmm1, -48(%rbp)
	movdqa	-64(%rbp), %xmm1
	movdqa	-48(%rbp), %xmm0
	pxor	%xmm1, %xmm0
	movaps	%xmm0, -144(%rbp)
	movdqa	-144(%rbp), %xmm0
	pslldq	$4, %xmm0
	movdqa	%xmm0, %xmm1
	movdqa	-144(%rbp), %xmm0
	movaps	%xmm0, -96(%rbp)
	movaps	%xmm1, -80(%rbp)
	movdqa	-96(%rbp), %xmm1
	movdqa	-80(%rbp), %xmm0
	pxor	%xmm1, %xmm0
	movaps	%xmm0, -144(%rbp)
	movdqa	-144(%rbp), %xmm0
	movaps	%xmm0, -128(%rbp)
	movdqa	-160(%rbp), %xmm0
	movaps	%xmm0, -112(%rbp)
	movdqa	-128(%rbp), %xmm1
	movdqa	-112(%rbp), %xmm0
	pxor	%xmm1, %xmm0
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE507:
	.size	aes_128_key_expansion, .-aes_128_key_expansion
	.globl	aes128_load_key
	.type	aes128_load_key, @function
aes128_load_key:
.LFB508:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$184, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -184(%rbp)
	movq	%rsi, -192(%rbp)
	movq	-184(%rbp), %rax
	movq	%rax, -168(%rbp)
	movq	-168(%rbp), %rax
	movdqu	(%rax), %xmm0
	movq	-192(%rbp), %rax
	movaps	%xmm0, (%rax)
	movq	-192(%rbp), %rax
	movdqa	(%rax), %xmm0
	aeskeygenassist	$1, %xmm0, %xmm1
	movq	-192(%rbp), %rax
	movdqa	(%rax), %xmm0
	movq	-192(%rbp), %rax
	leaq	16(%rax), %rbx
	call	aes_128_key_expansion
	movaps	%xmm0, (%rbx)
	movq	-192(%rbp), %rax
	addq	$16, %rax
	movdqa	(%rax), %xmm0
	aeskeygenassist	$2, %xmm0, %xmm1
	movq	-192(%rbp), %rax
	addq	$16, %rax
	movdqa	(%rax), %xmm0
	movq	-192(%rbp), %rax
	leaq	32(%rax), %rbx
	call	aes_128_key_expansion
	movaps	%xmm0, (%rbx)
	movq	-192(%rbp), %rax
	addq	$32, %rax
	movdqa	(%rax), %xmm0
	aeskeygenassist	$4, %xmm0, %xmm1
	movq	-192(%rbp), %rax
	addq	$32, %rax
	movdqa	(%rax), %xmm0
	movq	-192(%rbp), %rax
	leaq	48(%rax), %rbx
	call	aes_128_key_expansion
	movaps	%xmm0, (%rbx)
	movq	-192(%rbp), %rax
	addq	$48, %rax
	movdqa	(%rax), %xmm0
	aeskeygenassist	$8, %xmm0, %xmm1
	movq	-192(%rbp), %rax
	addq	$48, %rax
	movdqa	(%rax), %xmm0
	movq	-192(%rbp), %rax
	leaq	64(%rax), %rbx
	call	aes_128_key_expansion
	movaps	%xmm0, (%rbx)
	movq	-192(%rbp), %rax
	addq	$64, %rax
	movdqa	(%rax), %xmm0
	aeskeygenassist	$16, %xmm0, %xmm1
	movq	-192(%rbp), %rax
	addq	$64, %rax
	movdqa	(%rax), %xmm0
	movq	-192(%rbp), %rax
	leaq	80(%rax), %rbx
	call	aes_128_key_expansion
	movaps	%xmm0, (%rbx)
	movq	-192(%rbp), %rax
	addq	$80, %rax
	movdqa	(%rax), %xmm0
	aeskeygenassist	$32, %xmm0, %xmm1
	movq	-192(%rbp), %rax
	addq	$80, %rax
	movdqa	(%rax), %xmm0
	movq	-192(%rbp), %rax
	leaq	96(%rax), %rbx
	call	aes_128_key_expansion
	movaps	%xmm0, (%rbx)
	movq	-192(%rbp), %rax
	addq	$96, %rax
	movdqa	(%rax), %xmm0
	aeskeygenassist	$64, %xmm0, %xmm1
	movq	-192(%rbp), %rax
	addq	$96, %rax
	movdqa	(%rax), %xmm0
	movq	-192(%rbp), %rax
	leaq	112(%rax), %rbx
	call	aes_128_key_expansion
	movaps	%xmm0, (%rbx)
	movq	-192(%rbp), %rax
	addq	$112, %rax
	movdqa	(%rax), %xmm0
	aeskeygenassist	$128, %xmm0, %xmm1
	movq	-192(%rbp), %rax
	addq	$112, %rax
	movdqa	(%rax), %xmm0
	movq	-192(%rbp), %rax
	leaq	128(%rax), %rbx
	call	aes_128_key_expansion
	movaps	%xmm0, (%rbx)
	movq	-192(%rbp), %rax
	subq	$-128, %rax
	movdqa	(%rax), %xmm0
	aeskeygenassist	$27, %xmm0, %xmm1
	movq	-192(%rbp), %rax
	subq	$-128, %rax
	movdqa	(%rax), %xmm0
	movq	-192(%rbp), %rax
	leaq	144(%rax), %rbx
	call	aes_128_key_expansion
	movaps	%xmm0, (%rbx)
	movq	-192(%rbp), %rax
	addq	$144, %rax
	movdqa	(%rax), %xmm0
	aeskeygenassist	$54, %xmm0, %xmm1
	movq	-192(%rbp), %rax
	addq	$144, %rax
	movdqa	(%rax), %xmm0
	movq	-192(%rbp), %rax
	leaq	160(%rax), %rbx
	call	aes_128_key_expansion
	movaps	%xmm0, (%rbx)
	movq	-192(%rbp), %rax
	addq	$144, %rax
	movdqa	(%rax), %xmm0
	movq	-192(%rbp), %rax
	addq	$176, %rax
	movaps	%xmm0, -32(%rbp)
	aesimc	-32(%rbp), %xmm0
	movaps	%xmm0, (%rax)
	movq	-192(%rbp), %rax
	subq	$-128, %rax
	movdqa	(%rax), %xmm0
	movq	-192(%rbp), %rax
	addq	$192, %rax
	movaps	%xmm0, -48(%rbp)
	aesimc	-48(%rbp), %xmm0
	movaps	%xmm0, (%rax)
	movq	-192(%rbp), %rax
	addq	$112, %rax
	movdqa	(%rax), %xmm0
	movq	-192(%rbp), %rax
	addq	$208, %rax
	movaps	%xmm0, -64(%rbp)
	aesimc	-64(%rbp), %xmm0
	movaps	%xmm0, (%rax)
	movq	-192(%rbp), %rax
	addq	$96, %rax
	movdqa	(%rax), %xmm0
	movq	-192(%rbp), %rax
	addq	$224, %rax
	movaps	%xmm0, -80(%rbp)
	aesimc	-80(%rbp), %xmm0
	movaps	%xmm0, (%rax)
	movq	-192(%rbp), %rax
	addq	$80, %rax
	movdqa	(%rax), %xmm0
	movq	-192(%rbp), %rax
	addq	$240, %rax
	movaps	%xmm0, -96(%rbp)
	aesimc	-96(%rbp), %xmm0
	movaps	%xmm0, (%rax)
	movq	-192(%rbp), %rax
	addq	$64, %rax
	movdqa	(%rax), %xmm0
	movq	-192(%rbp), %rax
	addq	$256, %rax
	movaps	%xmm0, -112(%rbp)
	aesimc	-112(%rbp), %xmm0
	movaps	%xmm0, (%rax)
	movq	-192(%rbp), %rax
	addq	$48, %rax
	movdqa	(%rax), %xmm0
	movq	-192(%rbp), %rax
	addq	$272, %rax
	movaps	%xmm0, -128(%rbp)
	aesimc	-128(%rbp), %xmm0
	movaps	%xmm0, (%rax)
	movq	-192(%rbp), %rax
	addq	$32, %rax
	movdqa	(%rax), %xmm0
	movq	-192(%rbp), %rax
	addq	$288, %rax
	movaps	%xmm0, -144(%rbp)
	aesimc	-144(%rbp), %xmm0
	movaps	%xmm0, (%rax)
	movq	-192(%rbp), %rax
	addq	$16, %rax
	movdqa	(%rax), %xmm0
	movq	-192(%rbp), %rax
	addq	$304, %rax
	movaps	%xmm0, -160(%rbp)
	aesimc	-160(%rbp), %xmm0
	movaps	%xmm0, (%rax)
	nop
	addq	$184, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE508:
	.size	aes128_load_key, .-aes128_load_key
	.globl	aes128_enc
	.type	aes128_enc, @function
aes128_enc:
.LFB509:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$312, %rsp
	movq	%rdi, -408(%rbp)
	movq	%rsi, -416(%rbp)
	movq	%rdx, -424(%rbp)
	movq	-408(%rbp), %rax
	movq	%rax, -392(%rbp)
	movq	-392(%rbp), %rax
	movdqu	(%rax), %xmm0
	movaps	%xmm0, -384(%rbp)
	movq	-424(%rbp), %rax
	movdqa	(%rax), %xmm0
	movdqa	-384(%rbp), %xmm1
	movaps	%xmm1, -32(%rbp)
	movaps	%xmm0, -16(%rbp)
	movdqa	-32(%rbp), %xmm1
	movdqa	-16(%rbp), %xmm0
	pxor	%xmm1, %xmm0
	movaps	%xmm0, -384(%rbp)
	movq	-424(%rbp), %rax
	addq	$16, %rax
	movdqa	(%rax), %xmm0
	movdqa	-384(%rbp), %xmm1
	movaps	%xmm1, -64(%rbp)
	movaps	%xmm0, -48(%rbp)
	movdqa	-64(%rbp), %xmm0
	aesenc	-48(%rbp), %xmm0
	movaps	%xmm0, -384(%rbp)
	movq	-424(%rbp), %rax
	addq	$32, %rax
	movdqa	(%rax), %xmm0
	movdqa	-384(%rbp), %xmm1
	movaps	%xmm1, -96(%rbp)
	movaps	%xmm0, -80(%rbp)
	movdqa	-96(%rbp), %xmm0
	aesenc	-80(%rbp), %xmm0
	movaps	%xmm0, -384(%rbp)
	movq	-424(%rbp), %rax
	addq	$48, %rax
	movdqa	(%rax), %xmm0
	movdqa	-384(%rbp), %xmm1
	movaps	%xmm1, -128(%rbp)
	movaps	%xmm0, -112(%rbp)
	movdqa	-128(%rbp), %xmm0
	aesenc	-112(%rbp), %xmm0
	movaps	%xmm0, -384(%rbp)
	movq	-424(%rbp), %rax
	addq	$64, %rax
	movdqa	(%rax), %xmm0
	movdqa	-384(%rbp), %xmm1
	movaps	%xmm1, -160(%rbp)
	movaps	%xmm0, -144(%rbp)
	movdqa	-160(%rbp), %xmm0
	aesenc	-144(%rbp), %xmm0
	movaps	%xmm0, -384(%rbp)
	movq	-424(%rbp), %rax
	addq	$80, %rax
	movdqa	(%rax), %xmm0
	movdqa	-384(%rbp), %xmm1
	movaps	%xmm1, -192(%rbp)
	movaps	%xmm0, -176(%rbp)
	movdqa	-192(%rbp), %xmm0
	aesenc	-176(%rbp), %xmm0
	movaps	%xmm0, -384(%rbp)
	movq	-424(%rbp), %rax
	addq	$96, %rax
	movdqa	(%rax), %xmm0
	movdqa	-384(%rbp), %xmm1
	movaps	%xmm1, -224(%rbp)
	movaps	%xmm0, -208(%rbp)
	movdqa	-224(%rbp), %xmm0
	aesenc	-208(%rbp), %xmm0
	movaps	%xmm0, -384(%rbp)
	movq	-424(%rbp), %rax
	addq	$112, %rax
	movdqa	(%rax), %xmm0
	movdqa	-384(%rbp), %xmm1
	movaps	%xmm1, -256(%rbp)
	movaps	%xmm0, -240(%rbp)
	movdqa	-256(%rbp), %xmm0
	aesenc	-240(%rbp), %xmm0
	movaps	%xmm0, -384(%rbp)
	movq	-424(%rbp), %rax
	subq	$-128, %rax
	movdqa	(%rax), %xmm0
	movdqa	-384(%rbp), %xmm1
	movaps	%xmm1, -288(%rbp)
	movaps	%xmm0, -272(%rbp)
	movdqa	-288(%rbp), %xmm0
	aesenc	-272(%rbp), %xmm0
	movaps	%xmm0, -384(%rbp)
	movq	-424(%rbp), %rax
	addq	$144, %rax
	movdqa	(%rax), %xmm0
	movdqa	-384(%rbp), %xmm1
	movaps	%xmm1, -320(%rbp)
	movaps	%xmm0, -304(%rbp)
	movdqa	-320(%rbp), %xmm0
	aesenc	-304(%rbp), %xmm0
	movaps	%xmm0, -384(%rbp)
	movq	-424(%rbp), %rax
	addq	$160, %rax
	movdqa	(%rax), %xmm0
	movdqa	-384(%rbp), %xmm1
	movaps	%xmm1, -352(%rbp)
	movaps	%xmm0, -336(%rbp)
	movdqa	-352(%rbp), %xmm0
	aesenclast	-336(%rbp), %xmm0
	movaps	%xmm0, -384(%rbp)
	movq	-416(%rbp), %rax
	movq	%rax, -400(%rbp)
	movdqa	-384(%rbp), %xmm0
	movaps	%xmm0, -368(%rbp)
	movdqa	-368(%rbp), %xmm0
	movq	-400(%rbp), %rax
	movups	%xmm0, (%rax)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE509:
	.size	aes128_enc, .-aes128_enc
	.globl	aes128_dec
	.type	aes128_dec, @function
aes128_dec:
.LFB510:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$312, %rsp
	movq	%rdi, -408(%rbp)
	movq	%rsi, -416(%rbp)
	movq	%rdx, -424(%rbp)
	movq	-408(%rbp), %rax
	movq	%rax, -392(%rbp)
	movq	-392(%rbp), %rax
	movdqu	(%rax), %xmm0
	movaps	%xmm0, -384(%rbp)
	movq	-424(%rbp), %rax
	addq	$160, %rax
	movdqa	(%rax), %xmm0
	movdqa	-384(%rbp), %xmm1
	movaps	%xmm1, -32(%rbp)
	movaps	%xmm0, -16(%rbp)
	movdqa	-32(%rbp), %xmm1
	movdqa	-16(%rbp), %xmm0
	pxor	%xmm1, %xmm0
	movaps	%xmm0, -384(%rbp)
	movq	-424(%rbp), %rax
	addq	$176, %rax
	movdqa	(%rax), %xmm0
	movdqa	-384(%rbp), %xmm1
	movaps	%xmm1, -64(%rbp)
	movaps	%xmm0, -48(%rbp)
	movdqa	-64(%rbp), %xmm0
	aesdec	-48(%rbp), %xmm0
	movaps	%xmm0, -384(%rbp)
	movq	-424(%rbp), %rax
	addq	$192, %rax
	movdqa	(%rax), %xmm0
	movdqa	-384(%rbp), %xmm1
	movaps	%xmm1, -96(%rbp)
	movaps	%xmm0, -80(%rbp)
	movdqa	-96(%rbp), %xmm0
	aesdec	-80(%rbp), %xmm0
	movaps	%xmm0, -384(%rbp)
	movq	-424(%rbp), %rax
	addq	$208, %rax
	movdqa	(%rax), %xmm0
	movdqa	-384(%rbp), %xmm1
	movaps	%xmm1, -128(%rbp)
	movaps	%xmm0, -112(%rbp)
	movdqa	-128(%rbp), %xmm0
	aesdec	-112(%rbp), %xmm0
	movaps	%xmm0, -384(%rbp)
	movq	-424(%rbp), %rax
	addq	$224, %rax
	movdqa	(%rax), %xmm0
	movdqa	-384(%rbp), %xmm1
	movaps	%xmm1, -160(%rbp)
	movaps	%xmm0, -144(%rbp)
	movdqa	-160(%rbp), %xmm0
	aesdec	-144(%rbp), %xmm0
	movaps	%xmm0, -384(%rbp)
	movq	-424(%rbp), %rax
	addq	$240, %rax
	movdqa	(%rax), %xmm0
	movdqa	-384(%rbp), %xmm1
	movaps	%xmm1, -192(%rbp)
	movaps	%xmm0, -176(%rbp)
	movdqa	-192(%rbp), %xmm0
	aesdec	-176(%rbp), %xmm0
	movaps	%xmm0, -384(%rbp)
	movq	-424(%rbp), %rax
	addq	$256, %rax
	movdqa	(%rax), %xmm0
	movdqa	-384(%rbp), %xmm1
	movaps	%xmm1, -224(%rbp)
	movaps	%xmm0, -208(%rbp)
	movdqa	-224(%rbp), %xmm0
	aesdec	-208(%rbp), %xmm0
	movaps	%xmm0, -384(%rbp)
	movq	-424(%rbp), %rax
	addq	$272, %rax
	movdqa	(%rax), %xmm0
	movdqa	-384(%rbp), %xmm1
	movaps	%xmm1, -256(%rbp)
	movaps	%xmm0, -240(%rbp)
	movdqa	-256(%rbp), %xmm0
	aesdec	-240(%rbp), %xmm0
	movaps	%xmm0, -384(%rbp)
	movq	-424(%rbp), %rax
	addq	$288, %rax
	movdqa	(%rax), %xmm0
	movdqa	-384(%rbp), %xmm1
	movaps	%xmm1, -288(%rbp)
	movaps	%xmm0, -272(%rbp)
	movdqa	-288(%rbp), %xmm0
	aesdec	-272(%rbp), %xmm0
	movaps	%xmm0, -384(%rbp)
	movq	-424(%rbp), %rax
	addq	$304, %rax
	movdqa	(%rax), %xmm0
	movdqa	-384(%rbp), %xmm1
	movaps	%xmm1, -320(%rbp)
	movaps	%xmm0, -304(%rbp)
	movdqa	-320(%rbp), %xmm0
	aesdec	-304(%rbp), %xmm0
	movaps	%xmm0, -384(%rbp)
	movq	-424(%rbp), %rax
	movdqa	(%rax), %xmm0
	movdqa	-384(%rbp), %xmm1
	movaps	%xmm1, -352(%rbp)
	movaps	%xmm0, -336(%rbp)
	movdqa	-352(%rbp), %xmm0
	aesdeclast	-336(%rbp), %xmm0
	movaps	%xmm0, -384(%rbp)
	movq	-416(%rbp), %rax
	movq	%rax, -400(%rbp)
	movdqa	-384(%rbp), %xmm0
	movaps	%xmm0, -368(%rbp)
	movdqa	-368(%rbp), %xmm0
	movq	-400(%rbp), %rax
	movups	%xmm0, (%rax)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE510:
	.size	aes128_dec, .-aes128_dec
