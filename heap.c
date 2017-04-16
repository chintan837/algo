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

void swapp(int **a, int **b) {
	int *tmp = *a;
	*a = *b;
	*b = tmp;
}

void print_heap(char *label, int **heap, int heap_len) {
	printf("%s: ", label);
	for (int i = 1; i <= heap_len; i++) {
		printf("%d ", *heap[i]);
	}
	printf("\n");
}

int heap_add(int **heap, int heap_len, int *p) {
	assert(heap_len <= LEN);

	heap_len++;
	heap[heap_len] = p;
	printf("Added %d to index %d\n", *heap[heap_len], heap_len);

	/* bubble up */
	int child = heap_len;
	int parent = heap_len/2;
	while (parent >= 1) {
		if (*heap[parent] > *heap[child]) {
			printf("comparing parent %d[%d] to child %d[%d]\n",
					*heap[parent], parent, *heap[child], child);
			swapp(&heap[parent], &heap[child]);
			child = parent;
			parent = child/2;
		} else 
			break;
	}

	return heap_len;
}

int *get_min(int **heap, int *len) {
	int heap_len = *len;
	if (heap_len == 0)
		return NULL;

	int *ret = heap[1];
	swapp(&heap[1], &heap[heap_len]);
	--*len;

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
		print_heap("Current heap ", heap, heap_len);
	}

	printf("added %d elements\n", heap_len);
	print_heap("Added elements to heap", heap, heap_len);

	int *min = NULL;
	while ((min = get_min(heap, &heap_len))) {
		printf("Extracted %d new len: %d\n", *min, heap_len);
		print_heap("Current heap ", heap, heap_len);
	}
}
