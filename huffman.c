/*
In this programming problem and the next you'll code up the greedy algorithm 
from the lectures on Huffman coding.

This file describes an instance of the problem. It has the following format:

[number_of_symbols]

[weight of symbol #1]

[weight of symbol #2]

...

For example, the third line of the file is "6852892," indicating that the weight 
of the second symbol of the alphabet is 6852892. (We're using weights instead of 
frequencies, like in the "A More Complex Example" video.)

#1
Your task in this problem is to run the Huffman coding algorithm from lecture 
on this data set. What is the maximum length of a codeword in the resulting 
Huffman code?

#2
Continuing the previous problem, what is the minimum length of a codeword in your 
Huffman code?

ADVICE: If you're not getting the correct answer, try debugging your algorithm 
using some small test cases. And then post them to the discussion forum!
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct alphabet alphabet_t;
typedef struct heap heap_t;

struct alphabet {
	unsigned long p;
	alphabet_t *left;
	alphabet_t *rght;
};

struct heap{
	void *array;
	size_t len;
	size_t max_len;
	size_t elem_size;
	int (*compare)(const void *, const void *);
};

int compar(const void *p1, const void *p2) {
	alphabet_t *n1 = (alphabet_t *) p1;
	alphabet_t *n2 = (alphabet_t *) p2;

	return (n1->p>n2->p);
}

static heap_t *
heap_init(size_t max, size_t elem_size, int (*compare)(const void *, const void *)) {
	heap_t *heap = malloc(sizeof(heap_t));

	heap->len = 0;
	heap->max_len = 10;
	heap->elem_size = elem_size;
	heap->array = malloc(heap->elem_size * (heap->max_len+1));
	heap->compare = compare;
	return heap;
}

static void
heap_del(heap_t *heap) {
	free(heap->array);
}

static void
bubble_up(heap_t *heap, size_t child) {
	if (child <= 1)
		return;
	size_t parent = child/2;

	void *p = (heap->array)+(parent*heap->elem_size);
	void *c = (heap->array)+(child*heap->elem_size);
	if ((heap->compare)(p, c)) {
		void *t = malloc(heap->elem_size);
		memcpy(t, p, heap->elem_size);
		memcpy(p, c, heap->elem_size);
		memcpy(c, t, heap->elem_size);
		free (t);
		bubble_up(heap, parent);
	}
}

static void
heap_insert(heap_t *heap, void *elem) {
	heap->len++;
	if (heap->len >= heap->max_len) {
		heap->max_len *= 2;
		heap->array = realloc(heap->array, (heap->max_len+1)*heap->elem_size);
	}
	const void *src = elem;
	void *dst = (heap->array)+(heap->len*heap->elem_size);

	memcpy(dst, src, heap->elem_size);
	bubble_up(heap, heap->len);
}

static void
bubble_down(heap_t *heap, size_t parent) {
	for (size_t child = parent*2; child <= (parent*2)+1; child++) {
		if (child > heap->len)
			return;
		void *p = (heap->array)+(parent*heap->elem_size);
		void *c = (heap->array)+(child*heap->elem_size);
		if ((heap->compare)(p, c)) {
			void *t = malloc(heap->elem_size);
			memcpy(t, p, heap->elem_size);
			memcpy(p, c, heap->elem_size);
			memcpy(c, t, heap->elem_size);
			free (t);
			bubble_down(heap, child);
		}
	}
}

static void *
heap_extract_min(heap_t *heap) {
	if (heap->len == 0)
		return NULL;
	void *t = malloc(heap->elem_size);
	void *d = (heap->array)+heap->elem_size;
	void *s = (heap->array)+heap->elem_size*heap->len;
	heap->len--;
	memcpy(t, d, heap->elem_size);
	memcpy(d, s, heap->elem_size);

	bubble_down(heap, 1);
	return t;
}

static size_t 
tree_max_height(alphabet_t *a) {
	if (a == NULL)
		return 0;
	size_t left_height = tree_max_height(a->left);
	size_t rght_height = tree_max_height(a->rght);
	if (left_height > rght_height)
		return (left_height + 1);
	else
		return (rght_height + 1);
}

static size_t 
tree_min_height(alphabet_t *a) {
	if (a == NULL)
		return 0;
	size_t left_height = tree_min_height(a->left);
	size_t rght_height = tree_min_height(a->rght);
	if (left_height < rght_height)
		return (left_height + 1);
	else
		return (rght_height + 1);
}

int main(void) {
	FILE *fp = fopen("huffman2.txt", "r");
	int N = 0;
	char *line = NULL;
	size_t len;
	ssize_t read;
	read = getline(&line, &len, fp);
	sscanf(line, "%d\n", &N);
	printf("no of alphabets: %d\n", N);

	heap_t *heap = heap_init(10, sizeof(alphabet_t), compar);

	int i = 0;
	alphabet_t *alphabet = malloc(sizeof (alphabet_t));
	while ((read = getline(&line, &len, fp)) != -1) {
		sscanf(line, "%lu\n", &(alphabet->p));
		alphabet->left = NULL;
		alphabet->rght = NULL;
	
		heap_insert(heap, alphabet);

		i++;
	}
	free(alphabet);

	alphabet_t *alphabet1;
	alphabet_t *alphabet2;
	while (heap->len >= 2) {
		alphabet1 = heap_extract_min(heap);
		printf("extracted 1 %lu\n", alphabet1->p);
		alphabet2 = heap_extract_min(heap);
		printf("extracted 2 %lu\n", alphabet2->p);
		
		alphabet = malloc(sizeof (alphabet_t));
		alphabet->p = alphabet1->p + alphabet2->p;
		alphabet->left = alphabet1;
		alphabet->rght = alphabet2;
		heap_insert(heap, alphabet);
		printf("insterted %lu\n", alphabet->p);

		free(alphabet);
	}
	// this heap now has only one node which is the root of a huffman tree
	alphabet = heap_extract_min(heap);

	size_t max = tree_max_height(alphabet);
	size_t min = tree_min_height(alphabet);

	printf("min number of bits: %lu\n", min);
	printf("max number of bits: %lu\n", max);

	heap_del(heap);

	fclose(fp);
}
