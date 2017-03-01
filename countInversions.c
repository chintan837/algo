#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int mergesort(int *array, int len) {
	//exit condition
	int count = 0;
	if (len <= 1) {
		return count;
	}

	count += mergesort(&array[0], len/2);
	count += mergesort(&array[len/2], len-len/2);

	int *result = calloc(len, sizeof(int));
	//merge now
	int i = 0;
	int j = len/2;
	int k = 0;
	for ( ; k < len; k++) {
		if (() && (array[i] <= array[j])) {
			result[k] = array[i];
			i++;
		} else {
			result[k] = array[j];
			j++;
			// inc count by all emaining elements in array[i]
			count += len/2-i;

		}
	}
	for (i = 0; i < len; i++)
		array[i] = result[i];

	free(result);

	return count;
}

int main(void) {
	time_t t;
	int array[] = {1, 2, 3, 4, 5, 6, 7, 8};
	int len = sizeof(array)/sizeof(int);
	//	srand((unsigned) time(&t));
	srand(1);

	for(int i = 0; i < len; i++) {
		int random = rand()%len;
		int tmp = array[i];
		array[i] = array[random];
		array[random] = tmp;
	}

	len = 2;
	for (int i = 0; i < len; i++) {
		printf("%d", array[i]);
	}
	printf("\n");
	printf("Inversions: %d\n", mergesort(array, len));

	for (int i = 0; i < len; i++) {
		printf("%d", array[i]);
	}
	printf("\n");

}
