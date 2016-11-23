#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void sum() {
	
	return;
}

void multiply(int *n1, unsigned int l1, int *n2, unsigned int l2, int *prod, unsigned int l) {
	if ((l1 == 1) && (l2 == 1)) {
		prod[0] = n1[0] * n2[0];
		if (prod[0] > 9) {
			prod[1] = prod[0]/10;
			prod[0] = prod[0]%10;
		}
	}

	// calculate ac
	
	
	// calculate bd
	//
	//
	// calculate (a+b)*(c+d)
	//
	//
	// calculate (3)-(2)-(1)
	//
	//
	// sum 10^n(1) + 10^n/2(4) + (2)
	//
	//

	return;
}

int main() {
	printf("karatsub multiplications\n");

	//	const char *num1 = "3141592653589793238462643383279502884197169399375105820974944592";
	//	const char *num2 = "2718281828459045235360287471352662497757247093699959574966967627";
	const char *num1 = "5678";
	const char *num2 = "1234";

	unsigned int l1 = strlen(num1);
	unsigned int l2 = strlen(num2);
	unsigned int l = l1+ l2 + 1;
	int *n1 = calloc(l1, sizeof(int));
	int *n2 = calloc(l2, sizeof(int));
	int *prod = calloc(l, sizeof(int));

	int i;
	for (i = l1-1; i  >= 0; i--) {
		n1[i] = num1[i] - 48;
	}
	for (i = l2-1; i >= 0; i--) {
		n2[i] = num2[i] - 48;
	}

	multiply(n1, l1, n2, l2, prod, l);

	for(i = l; i >= 0; i--) {
		printf("%d", prod[i]);
	}
	printf("\n");

	free(n1);
	free(n2);
	free(prod);

	return 0;
}
