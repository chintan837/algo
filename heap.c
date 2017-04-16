#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define LEN 24

void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int heap_add(int **heap, int heap_len, int *p) {
	assert(heap_len <= LEN);


	heap_len++;
	heap[heap_len] = p;
	printf("Added %d to index %d\n", *heap[heap_len], heap_len);

	/* bubble up */

	return heap_len;
}

int *get_min(int **heap, int *len) {
	int heap_len = *len;
	if (heap_len == 0)
		return NULL;
	int *ret = &(*heap[1]);
	--*len;

	printf("Extracted %d from index 1\n", *ret);
	/* bubble down */

	return ret;
}

int main(int argc, char *argv[]) {
	int array[LEN];

	for (int i = 0; i < LEN; i++) {
		array[i] = i+1;
	}

	time_t t;
	//	srand(time(&t));
	srand((0));

	for (int i = 0; i < LEN; i++) {
		swap(&array[i], &array[rand()%LEN]);
	}

	for (int i = 0; i < LEN; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
	
	int **heap = calloc(LEN+1, sizeof (int *));
	int heap_len = 0;
	
	for (int i = 0; i < LEN; i++) {
		heap_len = heap_add(heap, heap_len, &array[i]);
	}

	printf("added %d elements\n", heap_len);

	int *min = NULL;
	while ((min = get_min(heap, &heap_len))) {
		printf("Extracted %d new len: %d\n", *min, heap_len);
	}
}
