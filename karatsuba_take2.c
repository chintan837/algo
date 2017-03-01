#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_number(const char * ch, int *ans, int len) {
	printf("%s:\t", ch);
	for (int i = len-1; i >= 0; i--) {
		printf("%d", ans[i]);
	}
	printf("\n");
}

void add(int *arr1, int *arr2, int offset, int len) {
	int carry = 0;
	int i, j;
	for (i = 0, j = offset; i < len/2; i++, j++) {
		arr1[j] += carry;
		arr1[j] += arr2[i];
		if (arr1[j] >= 10) {
			carry = arr1[j]/10;
			arr1[j] %= 10;
		} else
			carry = 0;
	}
	if (carry) {
		arr1[j] += carry;
	}
}

int *multiply(int *arr1, int *arr2, int len) {
//print_number("input 1", arr1, len);	
//print_number("input 2", arr2, len);	
	int *ans = calloc(len*2, sizeof(int));
	//base case
	if (len == 2) {
		if (arr1[1] == 0 && arr2[1] == 0) {
			len = 1;
		}
	}
	if (len <= 1) {
		ans[0] = arr1[0]*arr2[0];
		if (ans[0] > 9) {
			ans[1] = ans[0]/10;
			ans[0] = ans[0]%10;
		}
		return ans;
	}
	//rest

	//ac
	int right_start = 0;
	int right_len = len-len/2;
	int left_start = len-len/2;
	int left_len = len/2;
	int *bd = multiply(&arr1[right_start], &arr2[right_start], right_len);
	int *ac = multiply(&arr1[left_start], &arr2[left_start], left_len);
	int *ad = multiply(&arr1[left_start], &arr2[right_start], right_len);
	int *bc = multiply(&arr2[left_start], &arr1[right_start], left_len);
//print_number("bd", bd, len);	
//print_number("ac", ac, len);	
//print_number("ad", ad, len);	
//print_number("bc", bc, len);	
	//(1) + (4) + (2)
	int alen = len*2;
	add(ans, bd, 0, alen);
//print_number("ans", ans, alen);	
	add(ans, ac, len, alen);
//print_number("ans", ans, alen);	
	add(ans, ad, len/2, alen);
//print_number("ans", ans, alen);	
	add(ans, bc, len/2, alen);
//print_number("ans", ans, alen);	

	free(ac);
	free(bd);
	free(ad);
	free(bc);

	return ans;
}

int main() {
	char *num1 = "3141592653589793238462643383279502884197169399375105820974944592";
	char *num2 = "2718281828459045235360287471352662497757247093699959574966967627";
	
	int len = strlen(num1);
	int *arr1 = calloc(len, sizeof(int));
	int *arr2 = calloc(len, sizeof(int));
	int *ans;
	
	for(int i = 0; i < len; i++) {
		arr1[i] = num1[len-1-i] - '0';
		arr2[i] = num2[len-1-i] - '0';
	}

	ans = multiply(arr1, arr2, len);

	printf("-------------------------\n");
	print_number("ans", ans, len*2);

	free(ans);
	free(arr1);
	free(arr2);

	return 0;
}

