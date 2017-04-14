#include <stdio.h>
#include <stdlib.h>
#include <time.h>


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

int heap_add(int **heap, int heap_len, int *p) {
	

}

int *get_min(int **heap, int *heap_len) {
	int *current = *heap;


	return current;
}

int main(int argc, char *argv[]) {
	int array[LEN];

	for (int i = 0; i < LEN; i++) {
		array[i] = i+1;
	}

	time_t t;
	srand(time(&t));

	for (int i = 0; i < LEN; i++) {
		swap(&array[i], &array[rand()%LEN]);
	}

	for (int i = 0; i < LEN; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
	
	int **heap = calloc(LEN+1, sizeof(int *));
	int heap_len = 0;
	int *p;

	for (int i = 1; i <= LEN; i++) {
		heap_len = heap_add(heap, heap_len, &array[i]);
	}

	while (p = get_min(heap, &heap_len)) {
		printf("%d\n", *p);
	}

	free(heap);
}
