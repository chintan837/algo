/*
In this question your task is again to run the clustering algorithm from lecture, 
but on a MUCH bigger graph. So big, in fact, that the distances (i.e., edge costs) 
are only defined implicitly, rather than being provided as an explicit list.

The data set is below.

The format is:

[# of nodes] [# of bits for each node's label]

[first bit of node 1] ... [last bit of node 1]

[first bit of node 2] ... [last bit of node 2]

...

For example, the third line of the file "0 1 1 0 0 1 1 0 0 1 0 1 1 1 1 1 1 0 1 0 1 1 0 1" 
denotes the 24 bits associated with node #2.

The distance between two nodes u and v in this problem is defined as the Hamming distance--- 
the number of differing bits --- between the two nodes' labels. For example, the Hamming 
distance between the 24-bit label of node #2 above and the label 
"0 1 0 0 0 1 0 0 0 1 0 1 1 1 1 1 1 0 1 0 0 1 0 1" is 3 (since they differ in the 3rd, 7th, 
and 21st bits).

The question is: what is the largest value of k such that there is a k-clustering with 
spacing at least 3? That is, how many clusters are needed to ensure that no pair of 
nodes with all but 2 bits in common get split into different clusters?

NOTE: The graph implicitly defined by the data file is so big that you probably can't 
write it out explicitly, let alone sort the edges by cost. So you will have to be a 
little creative to complete this part of the question. For example, is there some way 
you can identify the smallest distances without explicitly looking at every pair of nodes?
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct node node_t;
struct node {
	unsigned int label;
	struct node *leader;
	int rank;
};

unsigned int *numbits;

static char printret[] = "000000000000000000000000";

static char *
printb(unsigned int x) {
	for (int i = 23; i >= 0; i--) {
		if (x & (1 << i)) {
			printret[23-i] = '1';
		}
		else
			printret[23-i] = '0';
	}
	return printret;
}

static int
hamming_distance(unsigned int n1, unsigned int n2) {
	return (numbits[n1 ^ n2]);	
}

static int 
count_bits(unsigned int x) {
	int count = 0;
	while (x) {
		if (x & 1)
			count++;
		x >>= 1;
	}
	return count;
}

static int 
count_bits_slow(unsigned int x) {
	int count = 0;
	while (x) {
		if (x & 1)
			count++;
		x >>= 1;
	}
	return count;
}

static void
init_lookup(int b) {
	numbits = calloc(1<<b, sizeof (unsigned int));

	for (unsigned int i = 0; i < (1<<b); i++) {
		numbits[i] = count_bits(i);
		//	printf("Numbits in %d: %d\n", i, numbits[i]);
	}
}

static node_t *
uf_find(node_t *x) {
	if (x == x->leader)
		return x;
	return ((x->leader = uf_find(x->leader)));
}

static int
uf_union(node_t *n1, node_t *n2) {
	node_t *l1 = uf_find(n1);
	node_t *l2 = uf_find(n2);
	if (l1 == l2)
		return 0;
	
	if (l1->rank > l2->rank) {
		l2->leader = l1;
	} else {
		l1->leader = l2;
		if (l2->rank == l1->rank)
			l2->rank++;
	}
	return 1;
}

int main (void) {
	FILE *fp = fopen("clustering_big.txt", "r");

	int N; int b;
	clock_t begin, end;

	char *line = malloc(64);
	size_t len;
	ssize_t read;
	read = getline(&line, &len, fp);
	sscanf(line, "%d %d\n", &N, &b);
	printf("Number of nodes: %d #bits: %d\n", N, b);

	node_t *nodes = calloc(N, sizeof (node_t));
	begin = clock();
	init_lookup(b);
	end = clock();
	printf("Time taken in init lookup: %f\n", (double)(end-begin)/CLOCKS_PER_SEC);

	int i = 0;
	while ((read = getline(&line, &len, fp)) != -1) {
		char *token;
		unsigned int n = 0;
		unsigned int mask = 0;
		int bit = b-1;
		while ((token = strsep(&line, " \n")) != NULL) {
			mask = 1 << bit;
			bit--;
			if (token[0] == '1') {
				n = n | mask;
			}
		}
		nodes[i].label = n;
		nodes[i].rank = 0;
		nodes[i].leader = &nodes[i];
		i++;
	}

	getchar();
#if 0
	for (int i = 0; i < 10; i++) {
		//	printf("node %d: %s\n", i, printret);
		printf("node %d: %s\n", i, printb(nodes[i].label));
	}

	printf("Done reading nodes\n");
	printf("Hamming distance of nodes 0 and 1: %d\n", hamming_distance(nodes[0].label, nodes[1].label));
	printf("Hamming distance of nodes 1 and 2: %d\n", hamming_distance(nodes[1].label, nodes[2].label));
	printf("Hamming distance of nodes 2 and 3: %d\n", hamming_distance(nodes[2].label, nodes[3].label));
	printf("Hamming distance of nodes 3 and 4: %d\n", hamming_distance(nodes[3].label, nodes[4].label));
#endif

	// number of clusters = # of nodes N
	int k = N;
	begin = clock();
	for (int i = 0; i < N-1; i++) {
		for (int j = i+1; j < N; j++) {
			if (hamming_distance(nodes[i].label, nodes[j].label) <= 2) {
				// for every successul union, reduce number of clusters by 1
				if (uf_union(&nodes[i], &nodes[j])) {
					k--;
				}
			}
		}
		if ((i%2000) == 0) {
			end = clock();
			printf("%d%% complete t=%2fs\n", i, (double)(end-begin)/CLOCKS_PER_SEC);
			begin = end;
		}
	}

	printf("Number of clusters = %d\n", k);

	free(numbits);
	free(nodes);
	free(line);
	fclose (fp);
}
