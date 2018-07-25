	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 12
	.globl	_main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	pushq	%rbp
Lcfi0:
	.cfi_def_cfa_offset 16
Lcfi1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Lcfi2:
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movl	$0, -4(%rbp)
	movl	$0, -8(%rbp)
	movl	$0, -12(%rbp)
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	cmpl	$10000, -12(%rbp)       ## imm = 0x2710
	jge	LBB0_4
## BB#2:                                ##   in Loop: Header=BB0_1 Depth=1
	leaq	_sin_vals(%rip), %rax
	movl	-12(%rbp), %ecx
	andl	$255, %ecx
	movslq	%ecx, %rdx
	movzbl	(%rax,%rdx), %ecx
	addl	-8(%rbp), %ecx
	movl	%ecx, -8(%rbp)
## BB#3:                                ##   in Loop: Header=BB0_1 Depth=1
	movl	-12(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -12(%rbp)
	jmp	LBB0_1
LBB0_4:
	movl	-8(%rbp), %eax
	movb	%al, %cl
	movsbl	%cl, %edi
	movb	$0, %al
	callq	_puts
	xorl	%edi, %edi
	movl	%eax, -16(%rbp)         ## 4-byte Spill
	movl	%edi, %eax
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.section	__DATA,__data
	.globl	_sin_vals               ## @sin_vals
	.p2align	4
_sin_vals:
	.ascii	"\000\002\003\005\006\b\t\013\r\016\020\021\023\024\026\027\031\033\034\036\037!\"$%')*,-/0235689;<>?ACDFGIJLMOPQSTVWYZ\\]_`bcdfgijlmnpqstuwxz{|~\177\200\202\203\204\206\207\210\212\213\214\216\217\220\222\223\224\225\227\230\231\232\234\235\236\237\241\242\243\244\245\247\250\251\252\253\254\256\257\260\261\262\263\264\265\267\270\271\272\273\274\275\276\277\300\301\302\303\304\305\306\307\310\311\312\313\314\315\316\317\320\320\321\322\323\324\325\326\327\327\330\331\332\333\334\334\335\336\337\337\340\341\342\342\343\344\344\345\346\347\347\350\350\351\352\352\353\354\354\355\355\356\356\357\360\360\361\361\362\362\363\363\364\364\364\365\365\366\366\367\367\367\370\370\370\371\371\371\372\372\372\373\373\373\374\374\374\374\374\375\375\375\375\375\376\376\376\376\376\376\376\377\377\377\377\377\377\377\377\377"


.subsections_via_symbols
