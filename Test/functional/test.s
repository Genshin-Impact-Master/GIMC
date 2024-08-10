	.arch  armv7
	.fpu  softvfp
	.text 
	.align  3
	.global  main
	.syntax  unified
	.thumb 
	.thumb_func 
	.type  main, %function
main:
	/* ******** 函数预处理 ******** */ 
	@ 将 fp 压栈 
	push  {r7}
	@ 将 lr 压栈 
	push  {lr}
	sub  sp, sp, #0	@ sp <- sp - #0
	add  r7, sp, #0	@ r7 <- sp + #0
entry_main:
movw	r4, #0
movt	r4,0
	add  sp, sp, r5	@ sp <- sp + r5
movw	r4, #3
movt	r4,0
	mov  r0, r4
	add  r7, r7, 0
 mov     sp, r7
pop     {r7, pc}
putch:
putint:
putarray:
putfloat:
putfarray:
before_main:
after_main:
_sysy_starttime:
_sysy_stoptime:
getint:
getch:
getfloat:
getarray:
getfarray:
entry_main:
memset:
memcpy:
