/*
MAX Weight Independent Set

In this programming problem you'll code up the dynamic programming algorithm 
for computing a maximum-weight independent set of a path graph.

Download the text file below.

mwis.txt
This file describes the weights of the vertices in a path graph (with the 
weights listed in the order in which vertices appear in the path). It has 
the following format:

[number_of_vertices]

[weight of first vertex]

[weight of second vertex]

...

For example, the third line of the file is "6395702," indicating that the 
weight of the second vertex of the graph is 6395702.

Your task in this problem is to run the dynamic programming algorithm (and 
the reconstruction procedure) from lecture on this data set. The question 
is: of the vertices 1, 2, 3, 4, 17, 117, 517, and 997, which ones belong 
to the maximum-weight independent set? (By "vertex 1" we mean the first 
vertex of the graph---there is no vertex 0.) In the box below, enter a 8-bit 
string, where the ith bit should be 1 if the ith of these 8 vertices is in 
the maximum-weight independent set, and 0 otherwise. For example, if you think 
that the vertices 1, 4, 17, and 517 are in the maximum-weight independent 
set and the other four vertices are not, then you should enter the string 
10011010 in the box below.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct vertex vertex_t;

struct vertex {
	int label;
	int weight;
};

int main(void) {
	FILE *fp = fopen("mwis.txt", "r");
	int N;

	char *line = NULL;
	size_t len;
	ssize_t read;
	read = getline(&line, &len, fp);
	sscanf(line, "%d\n", &N);
	printf("number of nodes: %d\n", N);
	vertex_t *vertices = calloc(N+1, sizeof(vertex_t));

	int i = 1;
	while ((read = getline(&line, &len, fp)) != -1) {
		(vertices+i)->label = i;
		sscanf(line, "%d\n", &((vertices+i)->weight));
		i++;
	}

	for (i = 1; i <= N; i++) {
		printf("Node: %d weight: %d\n", (vertices+i)->label, (vertices+i)->weight);

	}

	free(vertices);
	fclose(fp);
}
