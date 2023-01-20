#include<sys/syscall.h>

	.global		_start

_start:
	movq		$msg		,%rdi
	movq		%rdi		,%rsi
	callq		.len
	movq		%rcx		,%rdx
	movq		$0		,%rdi
	movq		$SYS_write	,%rax
	syscall

	movq		$SYS_exit	,%rax
	movq		$0x00		,%rdi
	syscall

.len:
	xor		%rcx		,%rcx
	not		%rcx
	movb		$0		,%al
repne	scasb
	neg		%rcx
	ret

msg:	.asciz		"Hello World\n"
