/*
	code
	File:/C/Bf_Optimized.c
	Date:2021.10.05
	By MIT License.
	Copyright (c) 2021 Ziyao.All rights reserved.
*/

#include<assert.h>
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>

#define VMDATA_SIZE 65536
#define PARSER_STACKSIZE 128

#define VMCODE_NULL 0
#define VMCODE_ADD 1
#define VMCODE_SUB 2
#define VMCODE_PUT 3
#define VMCODE_GET 4
#define VMCODE_PREV 5
#define VMCODE_NEXT 6
#define VMCODE_JZ 7		// This is a special instruction.
#define VMCODE_JMP 8		// This is similar
/*
	VMCODE_JZ has a three-byte argument.It is the offset in vmCode.
	VMCODE_JMP is similar to it.
*/

uint8_t *vmCode;
size_t vmCodeSize = 1024,vmCodeUsed;
uint8_t *vmData;

static void eval(void)
{
	uint8_t *pc = vmCode;
	uint8_t *dp = vmData;
	uint8_t op;
	while (pc < vmCode + vmCodeUsed) {
		op = *pc;
		pc++;
		if (op == VMCODE_ADD) {
			*dp += *pc;
		} else if (op == VMCODE_SUB) {
			*dp -= *pc;
		} else if (op == VMCODE_PUT) {
			for (uint8_t count = 0;count < *pc;count++)
				putchar(*dp);
		} else if (op == VMCODE_GET) {
			for (uint8_t count = 0;count < *pc;count++)
				*dp = getchar();
		} else if (op == VMCODE_PREV) {
			dp -= *pc;
		} else if (op == VMCODE_NEXT) {
			dp += *pc;
		} else if (op == VMCODE_JMP) {
			uint32_t offset = (uint32_t)*pc << 16;
			pc++;
			offset |= (uint32_t)*pc << 8;
			pc++;
			offset |= (uint32_t)*pc;
			pc = vmCode + offset - 1;
		} else if (op == VMCODE_JZ) {
			if (*dp) {
				pc += 2;
			} else {
				uint32_t offset = (uint32_t)*pc << 16;
				pc++;
				offset |= (uint32_t)*pc << 8;
				pc++;
				offset |= (uint32_t)*pc;
				pc = vmCode + offset - 1;
			}
		}
		pc++;
	}

	return;
}

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

static const char *parse_sub(const char *src)
{
	static uint8_t convert[256] = {
					['+'] = VMCODE_ADD,
					['-'] = VMCODE_SUB,
					['.'] = VMCODE_PUT,
					[','] = VMCODE_GET,
					['>'] = VMCODE_NEXT,
					['<'] = VMCODE_PREV,
				   };

	char tmp;
	while (*src != ']' && *src) {
		tmp = *src;
		if (tmp == '[') {
			uint32_t offset = vmCodeUsed;
			vmcode_emit(VMCODE_JZ);		// Jump
			vmcode_emit(VMCODE_NULL);	/* Three-bytes arg */
			vmcode_emit(VMCODE_NULL);
			vmcode_emit(VMCODE_NULL);

			src++;
			src = parse_sub(src);
			src++;

			uint32_t target = vmCodeUsed + 4;
			vmCode[offset + 1] = target >> 16;
			vmCode[offset + 2] = target >> 8 & 0xff;
			vmCode[offset + 3] = target & 0xff;
			vmcode_emit(VMCODE_JMP);
			vmcode_emit(offset >> 16);
			vmcode_emit(offset >> 8 & 0xff);
			vmcode_emit(offset & 0xff);

			continue;
		}
		if (!convert[(uint8_t)(*src)]) {
			src++;
			continue;
		}

		uint8_t count = 0;
		while (*src == tmp && count !=0xff) {
			src++;
			count++;
		}
		vmcode_emit(convert[(uint8_t)tmp]);
		vmcode_emit(count);
	}

	return src;
}

static void parse(const char *src)
{
	parse_sub(src);
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
