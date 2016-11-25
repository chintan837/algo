#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void printnum(char *label, int *array, int len) {
	printf("%s: ", label);
	for (int i=len-1; i >= 0; i--)
		printf("%d", array[i]);
	printf("\n");

}

int getlen(int *array, int max) {
	int i; int len = 0;
	for (i = 0; i < max; i++) {
		if (array[i])
			len = i+1;
	}
	return len;
}

// in place subtraction
void sub(int *a, unsigned int l1, int *b, unsigned int l2) {
	int i;
	for (i = 0; i < l2; i++) {
		if (a[i] < b[i]) {
			a[i] += 10;
			a[i+1]--;
			if (a[i+1] < 0) {
				printf("subtraction exception. Result might be negative\n");
				exit(-1);
			}
		}
		a[i] = a[i]-b[i];
	}
	
	return;
}

void sum(int *a, unsigned int l1, int *b, unsigned int l2, int *apb, unsigned int l) {
	int i;
	for (i = 0; i < l1; i++) {
		apb[i] = apb[i] + a[i] + b[i];
		if (apb[i] > 9) {
			apb[i+1] = apb[i]/10;
			apb[i] = apb[i]%10;
		}
	}
	
	return;
}

void multiply_old(int *ab, unsigned int l1, int *cd, unsigned int l2, int *prod, unsigned int l) {
	int i;
	unsigned int len1 = 0, len2= 0, len = 0;
	len1 = getlen(ab, l1);
	printnum("orig ab", ab, l1);
	printnum("new ab", ab, len1);

	len2 = getlen(cd, l2);
	printnum("orig cd", cd, l2);
	printnum("new cd", cd, len2);
	
	if ((len1 <= 1) && (len2 <= 1)) {
		prod[0] = ab[0] * cd[0];
		if (prod[0] > 9) {
			prod[1] = prod[0]/10;
			prod[0] = prod[0]%10;
		}
		return;
	}

	
	int *ac = calloc(l1, sizeof(int));
	int *bd = calloc(l2, sizeof(int));
	int *apb = calloc(l1+1, sizeof(int));
	int *cpd = calloc(l2+1, sizeof(int));
	int *apbcpd = calloc(l1+1+l2+1, sizeof(int));


	// calculate ac
	multiply_old(&(ab[l1/2]), l1/2, &(cd[l2/2]), l2/2, ac, l1);
	printnum("a", &(ab[l1/2]), l1/2);
	printnum("c", &(cd[l2/2]), l2/2);
	printnum("ac", ac , l1);
	getchar();
	
	
	// calculate bd
	multiply_old(&(ab[0]), l1/2, &(cd[0]), l2/2, bd, l2);
	printnum("b", &(ab[0]), l1/2);
	printnum("d", &(cd[0]), l2/2);
	printnum("bd", bd, l2);
	getchar();

	// calculate (a+b)
	sum(&(ab[l1/2]), l1/2, &(ab[0]), l1/2, apb, (l1/2)+1);
	printnum("apb", apb, l1/2+1);
	getchar();

	// calculate (c+d)
	sum(&(cd[l1/2]), l2/2, &(cd[0]), l2/2, cpd, (l2/2)+1);
	printnum("cpd", cpd, l2/2+1);
	getchar();
	
	// calculate (a+b)*(c+d)
	multiply_old(&(apb[0]), l1/2+1, &(cpd[0]), l2/2+1, apbcpd, l1/2+1+l2/2+1);
	printnum("apbcpd", apbcpd, l1/2+1+l2/2+1);
	getchar();

	// calculate (3)-(2)-(1)
	sub(apbcpd, l1+l2+2, ac, l1);
	sub(apbcpd, l1+l2+2, bd, l2);

	printnum("apbcpd after sub", apbcpd, l1+l2+2);
	getchar();
	printf("--------\n");

	// sum 10^n(1) + 10^n/2(4) + (2)

	return;
}

int main() {
	printf("karatsub multiplications\n");

	//	const char *num1 = "3141592653589793238462643383279502884197169399375105820974944592";
	//	const char *num2 = "2718281828459045235360287471352662497757247093699959574966967627";
	//	const char *num1 = "5678";
	//	const char *num2 = "1234";
	const char *num1 = "15";
	const char *num2 = "23";
	//	const char *num1 = "5";
	//	const char *num2 = "7";

	unsigned int l1 = strlen(num1);
	unsigned int l2 = strlen(num2);
	unsigned int l = l1 + l2 + 1;
	int *n1 = calloc(l1, sizeof(int));
	int *n2 = calloc(l2, sizeof(int));
	int *prod = calloc(l, sizeof(int));

	int i, j;
	for (i = l1-1, j = 0; j < l1; i--, j++) {
		n1[j] = num1[i] - 48;
	}
	for (i = l2-1, j = 0; j < l2; i--, j++) {
		n2[j] = num2[i] - 48;
	}

	printnum("n1", n1, l1);
	printnum("n2", n2, l2);

	multiply_old(n1, l1, n2, l2, prod, l);

	for(i = l; i >= 0; i--) {
		printf("%d", prod[i]);
	}
	printf("\n");

	free(n1);
	free(n2);
	free(prod);

	return 0;
}
