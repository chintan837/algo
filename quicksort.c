#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void swap(int *x, int *y) {
	int tmp = *x;
	*x = *y;
	*y = tmp;
}

void print_array(char *name, int *array, int len) {
	printf("%s", name);
	for (int i = 0; i < len; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

unsigned long long quicksort(int *array, int l, int r, int q) {
	if (l >= r)
		return 0;
	// choose pivot, as the one at index 0;
	if (q == 1) {
		// last element as pivot
		int tmp = array[r];
		array[r] = array[l];
		array[l] = tmp;
	}
	else if (q == 2) {
		//median of 3
		int m = (r-l)/2;
		m += l; // add offset
		//	printf("array[%d]: %d, array[%d]: %d,array[%d]: %d\t", l, array[l], m, array[m], r, array[r]);
		if ((array[l] < array[r]) && (array[l] < array[m])) {
			if (array[r] < array[m]) {
				// r is median
				swap(&array[r], &array[l]);
			} else {
				// m is median
				swap(&array[m], &array[l]);
			}
		}
		else if ((array[m] < array[r]) && (array[m] < array[l])) {
			if (array[r] < array[l]) {
				// r is median
				swap(&array[r], &array[l]);
			} else {
				// l is median
			}
		}
		else if ((array[r] < array[l]) && (array[r] < array[m])) {
			if (array[l] < array[m]) {
				// l is median
			} else {
				// m is median
				swap(&array[m], &array[l]);
			}
		}
		//	printf("%d\n", array[l]);
	}

	unsigned long long count = r-l;
	int p = array[l];
	int i = l+1;
	int j;
	for (j = l+1; j <= r; j++) {
		if (array[j] < p) {
			int tmp = array[j];
			array[j] = array[i];
			array[i] = tmp;
			i++;
		}
	}
	array[l] = array[i-1];
	array[i-1] = p;
	count += quicksort(array, l, i-2, q);
	count += quicksort(array, i, r, q);

	return count;
}

int main (void) {
#if 0
	int array[] = {1, 2, 3, 4, 5, 6, 7, 8};
	int len = sizeof(array)/sizeof(array[0]);


	time_t t;
	srand((unsigned) time(&t));

	for (int i = 0; i < len; i++) {
		int index = rand()%len;
		int tmp = array[i];
		array[i] = array[index];
		array[index] = tmp;
	}
#endif

	FILE *fp = fopen("QuickSort.txt", "r");
	int array_orig[10000];
	int array[10000];
	int len = 10000;
	for (int i = 0; i < len; i++) {
		fscanf(fp, "%d\n", &array_orig[i]);
	}
	fclose (fp);

	for (int q = 0; q < 3; q++) {
		for (int i = 0; i < len; i++) {
			array[i] = array_orig[i];
		}
		unsigned long long comp = quicksort(array, 0, len-1, q);
		printf("# of comparisions: %llu\n", comp);
	}
	return 0;
}
