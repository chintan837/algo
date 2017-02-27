#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_number(int *ans, int len) {
	for (int i = len-1; i >= 0; i--) {
		printf("%d", ans[i]);
	}
	printf("\n");
}

int *multiply(int *arr1, int *arr2, int len) {
	int *ans = calloc(len*2, sizeof(int));
	//base case
	if (len <= 1) {
		ans[0] = arr1[0]*arr2[0];
		if (ans[0] > 9) {
			ans[1] = ans[0]/10;
			ans[0] = ans[0]%10;
		}
		return ans;
	}
	//rest
	`

	return ans;
}

int main() {
	char *num1 = "65";
	char *num2 = "17";
	
	int len = strlen(num1);
	int *arr1 = calloc(len, sizeof(int));
	int *arr2 = calloc(len, sizeof(int));
	int *ans;
	
	for(int i = 0; i < len; i++) {
		arr1[i] = num1[len-1-i] - '0';
		arr2[i] = num2[len-1-i] - '0';
	}

	ans = multiply(arr1, arr2, len);

	print_number(ans, len*2);

	free(ans);
	free(arr1);
	free(arr2);

	return 0;
}

