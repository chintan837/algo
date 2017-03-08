#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SWAP(x, y, T) do {T tmp = x; x = y; y = x} while(0)

void print_array(char *name, int *array, int len) {
	printf("%s", name);
	for (int i = 0; i < len; i++) {
		printf("%d", array[i]);
	}
	printf("\n");
}

void quicksort(int *array, int l, int r) {
	if (l >= r)
		return;
	// choose pivot, as the one at index 0;
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
	quicksort(array, l, i-2);
	quicksort(array, i, r);
}

int main (void) {
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

	print_array("array :", array, len);
	
	quicksort(array, 0, len-1);
	print_array("sorted :", array, len);
	
	return 0;
}
