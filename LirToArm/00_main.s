	.arch armv7
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"00_main.c"
	.text
	.align	1
	.global	main
	.syntax unified
	.thumb
	.thumb_func
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
	add	r7, sp, #0
	movs	r3, #3
	mov	r0, r3
	mov	sp, r7
	@ sp needed
	pop	{r7}
	bx	lr
	.size	main, .-main
	.ident	"GCC: (SUSE Linux) 14.1.1 20240621 [revision 272e8c90af527fc1d0055ad0f17f1d97bb0bd6cb]"
