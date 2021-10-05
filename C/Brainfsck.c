/*
	code
	File:/C/Brainfsck.c
	Date:2021.10.03
	By MIT License.
	Copyright (c) 2021 Suote127.All rights reserved.
*/

#include<assert.h>
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>

#define VMDATA_SIZE 65536
#define VM_STACKSIZE 128

#define VMCODE_NULL 0
#define VMCODE_ADD 1
#define VMCODE_SUB 2
#define VMCODE_PUT 3
#define VMCODE_GET 4
#define VMCODE_PREV 5
#define VMCODE_NEXT 6
#define VMCODE_LOOPB 7
#define VMCODE_LOOPE 8

uint8_t *vmCode;
size_t vmCodeSize = 1024,vmCodeUsed;
uint8_t *vmData;

static inline void vmcode_emit(uint8_t code)
{
	if (vmCodeUsed >= vmCodeSize) {
		vmCodeSize <<= 1;
		vmCode = realloc(vmCode,vmCodeSize);
		assert(vmCode);
	}
	vmCode[vmCodeUsed] = code;
	vmCodeUsed++;
	return;
}

static void eval(void)
{
	uint8_t **stack = (uint8_t**)malloc(VM_STACKSIZE);
	assert(stack);
	uint8_t *pc = vmCode;
	uint8_t *dp = vmData;
	uint8_t **sp = stack;

	while (pc < vmCode + vmCodeUsed) {
		if (*pc == VMCODE_ADD) {
			(*dp)++;
		} else if (*pc == VMCODE_SUB) {
			(*dp)--;
		} else if (*pc == VMCODE_NEXT) {
			dp++;
		} else if (*pc == VMCODE_PREV) {
			dp--;
		} else if (*pc == VMCODE_PUT) {
			putchar(*dp);
		} else if (*pc == VMCODE_GET) {
			*dp = getchar();
		} else if (*pc == VMCODE_LOOPB) {
			if (*dp) {
				*sp = pc;
				sp++;
			} else {
				unsigned int depth = 0;
				do {
					if (*pc == VMCODE_LOOPE) {
						depth--;
					} else if (*pc == VMCODE_LOOPB) {
						depth++;
					}
					pc++;
				} while (depth);
				pc--;
			}
		} else if (*pc == VMCODE_LOOPE) {
			sp--;
			pc = *sp - 1;
		}
		pc++;
	}

	free(stack);

	return;
}

static void parse(const char *src)
{
	static uint8_t convert[256] = {
					['+'] = VMCODE_ADD,
					['-'] = VMCODE_SUB,
					['.'] = VMCODE_PUT,
					[','] = VMCODE_GET,
					['>'] = VMCODE_NEXT,
					['<'] = VMCODE_PREV,
					['['] = VMCODE_LOOPB,
					[']'] = VMCODE_LOOPE
				   };
	while (*src) {
		char tmp = convert[(uint8_t)*src];
		if (tmp)
			vmcode_emit((uint8_t)tmp);
		src++;
	}

	return;
}

int main(int argc,char *argv[])
{
	if (argc != 2) {
		fprintf(stderr,"%s: Usage\n %s source\n",argv[0],argv[0]);
		return -1;
	}

	FILE *file = fopen(argv[1],"r");
	if (!file) {
		fprintf(stderr,"Cannot open %s\n",argv[1]);
		return -1;
	}
	if (fseek(file,0,SEEK_END)) {
		fputs("Error while getting the length of the source",stderr);
		return -1;
	}
	long int size = ftell(file);
	char *src = (char*)malloc(sizeof(char) * size + 1);
	rewind(file);
	assert(fread(src,size,1,file));
	fclose(file);
	src[size] = '\0';		// Add the null character

	vmCode = (uint8_t*)malloc(1024);
	assert(vmCode);
	parse(src);

	vmData = (uint8_t*)malloc(VMDATA_SIZE);
	assert(vmData);
	memset(vmData,0,VMDATA_SIZE);
	eval();

	putchar('\n');			// For beauty

	free(src);
	free(vmCode);
	free(vmData);

	return 0;
}
