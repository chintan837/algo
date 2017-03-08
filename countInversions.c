#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

unsigned long long mergesort(int *array, int len) {
	//exit condition
	unsigned long long count = 0;
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
	while (k < len) {
		if (array[i] <= array[j]) {
			result[k] = array[i];
			i++;
		} else {
			result[k] = array[j];
			j++;
			// inc count by all emaining elements in array[i]
			count += len/2-i;
		}
		k++;
		if (i >= len/2) {
			while (k < len) {
				result[k] = array[j];
				k++; j++;
			}
			break;
		}
		if (j >= len) {
			while (k < len) {
				result[k] = array[i];
				k++; i++;
			}
			break;
		}
	}
	for (i = 0; i < len; i++)
		array[i] = result[i];

	free(result);

	return count;
}

int main(void) {

#if 0
	time_t t;
	int array[] = {1, 2, 3, 4, 5, 6, 7};
	int len = sizeof(array)/sizeof(int);
	//	srand((unsigned) time(&t));
	srand(1);
	for(int i = 0; i < len; i++) {
		int random = rand()%len;
		int tmp = array[i];
		array[i] = array[random];
		array[random] = tmp;
	}
#endif
	int len = 100000;
	int *array = calloc(len, sizeof(int));
	
	FILE *fp = fopen("IntegerArray.txt", "r");

	for (int i = 0; i < len; i++) {
		fscanf(fp, "%d\n", &array[i]);
		printf("%d\n", array[i]);
	}
	printf("\n");
	printf("Inversions: %llu\n", mergesort(array, len));
#if 0
	for (int i = 0; i < len; i++) {
		printf("%d\n", array[i]);
	}
	printf("\n");
#endif
	free(array);
	fclose(fp);
}
