	.arch  armv7
	.fpu  vfpv3
	.text 
	.align  3
	.global  main
	.syntax  unified
	.type  main, %function
main:
	/* ******** 函数预处理 ******** */ 
	@ 将 fp,lr 压栈 
	push {r7, lr}
	sub  sp, sp, #0	@ sp <- sp - #0
	add  r7, sp, #0	@ r7 <- sp + #0
	movw	r6, #65528
	movt	r6,65535
	add  sp, sp, r6	@ sp <- sp + r6
	movw	r4, #3
	movt	r4,0
	movw	r5, #65528
	movt	r5,65535
	add  r5, r7, r5	@ r5 <- r7 + r5
	str	r4,[r5]
	movw	r4, #65528
	movt	r4,65535
	add  r4, r7, r4	@ r4 <- r7 + r4
	ldr r4, [r4]
	mov  r0, r4
	add  r7, r7, #0
	mov     sp, r7
	pop     {r7, pc}
