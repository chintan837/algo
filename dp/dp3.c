/*
 *
Let us discuss Longest Increasing Subsequence (LIS) problem as an 
example problem that can be solved using Dynamic Programming.
The Longest Increasing Subsequence (LIS) problem is to find the length 
of the longest subsequence of a given sequence such that all elements 
of the subsequence are sorted in increasing order. For example, the 
length of LIS for {10, 22, 9, 33, 21, 50, 41, 60, 80} is 6 and LIS is 
{10, 22, 33, 50, 60, 80}.

Input  : arr[] = {3, 10, 2, 1, 20}
Output : Length of LIS = 3
The longest increasing subsequence is 3, 10, 20

Input  : arr[] = {3, 2}
Output : Length of LIS = 1
The longest increasing subsequences are {3} and {2}

Input : arr[] = {50, 3, 10, 7, 40, 80}
Output : Length of LIS = 4
The longest increasing subsequence is {3, 7, 40, 80}

*/


#include <stdio.h>
#include <stdlib.h>

int main(void) {
	printf("Hello, world\n");

	void *ptr = malloc(1);
	ptr = malloc(4);

	for (int i = 0; i < sizeof(int); i++) {
		printf("Sizeof %p\n", ptr+i);
	}

	while (((int) ptr % sizeof (int))  != 0) {
		printf("ptr %p\n", ptr);
		ptr++;
	}


	int arr[] = {3, 10, 2, 1, 20, 30};
	int num = sizeof(arr)/sizeof(int);
	int max = 0;

	int *ans = calloc(num, sizeof(int));

	// always include the first element as the base case
	ans[0] = 1;
	max = 1;
	for (int i = 0; i < num; i++) {
		for (int j = i-1; j >= 0; j--) {
			if (arr[j] <= arr[i]) {
				printf("here\n");
				ans[i] = ans[j] + 1;
				if (ans[i] > max) {
					max = ans[i];
				}
				break;
			}
		}
		// didnt find any element less than me, so default length is 1
		ans[i] = 1;
	}

	printf("Size: %d\n", num);
	for (int i = 0; i < num; i++) {
		printf("%d ", ans[i]);
	}
	printf("\n");

	free(ans);
	return 0;
}

