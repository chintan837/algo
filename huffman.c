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

struct alphabet {
	unsigned long p;
	alphabet_t *left;
	alphabet_t *rght;
};

int compar(const void *p1, const void *p2) {
	alphabet_t *n1 = (alphabet_t *) p1;
	alphabet_t *n2 = (alphabet_t *) p2;

	return (n1->p-n2->p);
}

static void
bubble_up(alphabet_t *head, size_t child) {
	if (child <= 1)
		return;
	size_t parent = child/2;

	if (head[parent].p > head[child].p) {
		alphabet_t *tmp = malloc(sizeof(alphabet_t));
		memcpy(&(head[parent]), tmp, sizeof(alphabet_t));
		memcpy(&(head[child]), &(head[parent]), sizeof(alphabet_t));
		memcpy(tmp, &(head[child]), sizeof(alphabet_t));

		free(tmp);

		realloc
	}
}

static void
heap_insert(alphabet_t *head, size_t *len, alphabet_t *elem) {
	head[*len] = elem;
	(*len)++;

	bubble_up(head, *len);
}

static alphabet_t *
heap_extract_min() {

}

int main(void) {
	FILE *fp = fopen("huffman.txt", "r");
	int N = 0;
	char *line = NULL;
	size_t len;
	ssize_t read;
	read = getline(&line, &len, fp);
	sscanf(line, "%d\n", &N);
	printf("no of alphabets: %d\n", N);
	alphabet_t *alphabets = calloc(N, sizeof (alphabet_t));

	int i = 0;
	while ((read = getline(&line, &len, fp)) != -1) {
		sscanf(line, "%lu\n", &(alphabets[i].p));
		i++;
	}

	for (i = 0; i < 10; i++) {
		printf("%lu\n", alphabets[i].p);
	}

	// sort the array
	qsort(alphabets, N, sizeof(alphabet_t), compar);

	//treat the sorted array as a heap. It satisfies the heap property

	for (i = 0; i < 10; i++) {
		printf("%lu\n", alphabets[i].p);
	}

	free(alphabets);
	fclose(fp);
}
