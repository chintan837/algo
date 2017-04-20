#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void print_heap(char *label, int *heap, int len) {
	printf("%s", label);
	for (int i = 1; i <= len; i++)
		printf("%d ", heap[i]);
	printf("\n");
}

int peek(int *heap, int len) {
	int ret = INT_MAX;

	if (len >= 1)
		ret = heap[1];

	return ret;
}

void bubble_up_max(int *heap, int len, int child) {
	if (child <= 1)
		return;

	int parent = child / 2;

	if (heap[parent] < heap[child]) {
		swap(&heap[parent], &heap[child]);
		bubble_up_max(heap, len, parent);
	}
}

int add_max(int *heap, int len, int value) {
	len++;
	heap[len] = value;

	bubble_up_max(heap, len, len);

	return len;
}

void bubble_down_max(int *heap, int len, int parent) {
	for (int child = parent*2; child <= parent*2+1; child++) {
		if (child > len)
			return;
		if (heap[parent] < heap[child]) {
			swap(&heap[parent], &heap[child]);
			bubble_down_max(heap, len, child);
		}
	}
}

int get_max(int *heap, int *len) {
	if (*len <= 0)
		return -1;
	int ret = heap[1];
	swap(&heap[1], &heap[*len]);
	*len -= 1;

	bubble_down_max(heap, *len, 1);

	return ret;
}

void bubble_up_min(int *heap, int len, int child) {
	if (child <= 1)
		return;

	int parent = child / 2;

	if (heap[parent] > heap[child]) {
		swap(&heap[parent], &heap[child]);
		bubble_up_min(heap, len, parent);
	}
}

int add_min(int *heap, int len, int value) {
	len++;
	heap[len] = value;

	bubble_up_min(heap, len, len);

	return len;
}

void bubble_down_min(int *heap, int len, int parent) {
	for (int child = parent*2; child <= parent*2+1; child++) {
		if (child > len)
			return;
		if (heap[parent] > heap[child]) {
			swap(&heap[parent], &heap[child]);
			bubble_down_min(heap, len, child);
		}
	}
}

int get_min(int *heap, int *len) {
	if (*len <= 0)
		return -1;
	int ret = heap[1];
	swap(&heap[1], &heap[*len]);
	*len -= 1;

	bubble_down_min(heap, *len, 1);

	return ret;
}

int main(int argc, char *argv[]) {
	FILE *fp = fopen("median.txt", "r");
	char *line;
	ssize_t read;
	size_t len;
	int n = 0;

	int *minheap = calloc(10001, sizeof (int));
	int *maxheap = calloc(10001, sizeof (int));
	int mk[10001];
	int min_len = 0;
	int max_len = 0;
	int i = 1;
	long long median;

	while ((read = getline(&line, &len, fp)) != -1) {
		sscanf(line, "%d", &n);

		if (n < peek(maxheap, max_len)) 


		
		min_len = add_min(minheap, min_len, n);
		max_len = add_max(maxheap, max_len, n);

		printf("median: %lld\n", median);
	}

	free(line);
	free(minheap);
	free(maxheap);

	fclose(fp);
}
