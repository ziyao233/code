/*
 *	code
 *	File:/C/ucontext.c
 *	Date:2021.07.03
 *	By MIT License.
 *	Copyright(C) 2021 Suote127.All rights reserved.
*/

#include<assert.h>
#include<stdio.h>
#include<stdlib.h>

#include<ucontext.h>

ucontext_t ctxA,ctxB;
ucontext_t ctxMain;
int end;

void func_a(void)
{
	while(1) {
		puts("Hello World!This is function A");
		swapcontext(&ctxA,&ctxB);
	}
	return;
}

void func_b(void)
{
	for (int i = 0;i < 512;i++) {
		puts("Hello World!This is function B");
		swapcontext(&ctxB,&ctxA);
	}
	end = 1;
	return;
}

int main(void)
{
	assert(getcontext(&ctxA) != -1);
	assert(getcontext(&ctxB) != -1);
	assert((ctxA.uc_stack.ss_sp = malloc(4096)));
	assert((ctxB.uc_stack.ss_sp = malloc(4096)));
	ctxA.uc_stack.ss_size	   = 4096;
	ctxB.uc_stack.ss_size	   = 4096;

	getcontext(&ctxMain);
	if (!end) {
		ctxA.uc_link = &ctxMain;
		ctxB.uc_link = &ctxMain;
		makecontext(&ctxA,func_a,0);
		makecontext(&ctxB,func_b,0);
		setcontext(&ctxA);
	}

	free(ctxA.uc_stack.ss_sp);
	free(ctxB.uc_stack.ss_sp);

	return 0;
}
