#include<stdio.h>
#include<stdlib.h>

int main(void)
{
	int target = 0;
	scanf("%d",&target);

	double pi = 1.;
	int sign = -1;
	for (int count = 0;count < target;count++) {
		pi += sign / (count * 2 + 3.);
		sign = -sign;
	}

	printf("%lf\n",pi * 4);

	return 0;
}
