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

typedef struct node node_t;
struct node {
	unsigned int label;
	struct node *leader;
	int rank;
};

int main (void) {
	FILE *fp = fopen("clustering_big.txt", "r");

	int N; int b;
	char *line = NULL;
	size_t len;
	ssize_t read;
	read = getline(&line, &len, fp);
	sscanf(line, "%d %d\n", &N, &b);
	printf("Number of nodes: %d #bits: %d\n", N, b);

	node_t *nodes = calloc(N, sizeof (node_t));
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
	}

	printf("Done reading nodes\n");

	free(nodes);
	free(line);
	fclose (fp);
}
