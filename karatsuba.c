/*
http://graphics.stanford.edu/~seander/bithacks.html

bit hacks, for later
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX(a,b) ((a)>(b)?(a):(b))

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

void sum(int *a, int *b, unsigned int len, int *apb) {
	int i;
	// lenth of apb is 1+ than len
	for (i = 0; i < len; i++) {
		apb[i] = apb[i] + a[i] + b[i];
		if (apb[i] > 9) {
			apb[i+1] = apb[i]/10;
			apb[i] = apb[i]%10;
		}
	}
	
	return;
}

#if 0
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
#endif

void multiply(int *num1, int *num2, int len, int *prod) {
	if (len == 1) {
		prod[0] = num1[0] * num2[0];
		if (prod[0] > 9) {
			prod[1] = prod[0]/10;
			prod[0] = prod[0]%10;
		}
		return;
	}

	printnum("num1----", num1, len);
	printf("%d\n", len);
	printnum("num2----", num2, len);
	printf("%d\n", len);

	int *ac = calloc(len, sizeof(int));
	int *bd = calloc(len, sizeof(int));
	int *apb = calloc(len+1, sizeof(int));
	int *cpd = calloc(len+1, sizeof(int));
	int *apbcpd = calloc((len+1)*2, sizeof(int));

	multiply(&(num1[len/2]), &(num2[len/2]), len/2, ac);
	printnum("ac", ac , len);
	multiply(&(num1[0]), &(num2[0]), len/2, bd);
	printnum("bd", bd , len);

	// calculate (a+b)
	sum(&(num1[len/2]), &(num1[0]), len/2, apb);
	// calculate (c+d)
	sum(&(num2[len/2]), &(num2[0]), len/2, cpd);

	unsigned int l = MAX(getlen(apb, len), getlen(cpd, len));
	printf("l = %d\n", l);
	while (l & (l-1))
		l++;
	printf("new l = %d\n", l);
	multiply(apb, cpd, l, apbcpd);
	printnum("apbcpd", apbcpd, len*2);

	// calculate (3)-(2)-(1)
	sub(apbcpd, (len+1)*2, ac, len);
	sub(apbcpd, (len+1)*2, bd, len);
	printnum("apbcpd after sub", apbcpd, (len+1)*2);

	int i = 0, j = 0, k = 0;
	while (i < len) {
		prod[i] = bd[j];
		i++; j++;
	}
	printnum("prod 1", prod, len*2);
	while (i < len*2) {
		prod[i] = ac[k];
		i++; k++;
	}
	printnum("prod 2", prod, len*2);
	for (i = len/2, j = 0; j < len+1; j++, i++) {
		prod[i] += apbcpd[j];
		printf("prod[i]: %d[%d], apbcpd[j]:%d[%d]\n",
				prod[i], i, apbcpd[j], j);
		if (prod[i] > 9) {
			prod[i+1] += prod[i]/10;
			printf("prod[i+1]: %d[%d]\n", prod[i+1], i+1);
			prod[i] = prod[i]%10;
			printf("prod[i]: %d[%d]\n", prod[i], i);
		}
	}
	printnum("prod 3", prod, len*2);

	printf("--------------------------\n");

	free(ac);
	free(bd);
	free(apb);
	free(cpd);
	free(apbcpd);
}

int main() {
	printf("karatsub multiplications\n");

	//	const char *num1 = "3141592653589793238462643383279502884197169399375105820974944592";
	//	const char *num2 = "2718281828459045235360287471352662497757247093699959574966967627";
	//	const char *num1 = "5678";
	//	const char *num2 = "1234";
	const char *num1 = "9999";
	const char *num2 = "9999";
	//	const char *num1 = "99";
	//	const char *num2 = "99";
	//	const char *num1 = "5";
	//	const char *num2 = "7";

	unsigned int l1 = strlen(num1);
	unsigned int l2 = strlen(num2);
	unsigned int len = MAX(l1, l2);
	int *n1 = calloc(len, sizeof(int));
	int *n2 = calloc(len, sizeof(int));
	int *prod = calloc(len*2, sizeof(int));

	int i, j;
	for (i = len-1, j = 0; j < len; i--, j++) {
		n1[j] = num1[i] - 48;
		n2[j] = num2[i] - 48;
	}
	
	printnum("n1", n1, len);
	printnum("n2", n2, len);

	//	multiply_old(n1, l1, n2, l2, prod, l);

	// asume lenghts of both numbers are same for now
	// max size of answer will be 2*len
	multiply(n1, n2, len, prod);

	printnum("prod", prod, len*2);

	free(n1);
	free(n2);
	free(prod);

	return 0;
}
