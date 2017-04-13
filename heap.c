#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define LEN 24

void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
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
	
	int **heap = calloc(LEN, 


	printf("\n");
}
