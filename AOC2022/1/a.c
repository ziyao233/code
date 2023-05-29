#include<stdio.h>
#include<stdlib.h>

int
main(void)
{
	char t[64];
	unsigned long int maxElf = 0, thisElf = 0;
	while (fgets(t, 63, stdin)) {
		if (t[0] == '\n') {
			maxElf	= maxElf > thisElf ? maxElf : thisElf;
			thisElf	= 0;
		} else {
			thisElf += atoi(t);
		}
	}

	printf("%lu\n", maxElf);

	return 0;
}
