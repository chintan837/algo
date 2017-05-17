/*
In this programming problem and the next you'll code up the clustering 
algorithm from lecture for computing a max-spacing k-clustering.

Download the text file below.
This file describes a distance function (equivalently, a complete graph 
with edge costs). It has the following format:

[number_of_nodes]

[edge 1 node 1] [edge 1 node 2] [edge 1 cost]

[edge 2 node 1] [edge 2 node 2] [edge 2 cost]

...

There is one edge (i,j) for each choice of 1≤i<j≤n, where n is the number of nodes.

For example, the third line of the file is "1 3 5250", indicating that the distance 
between nodes 1 and 3 (equivalently, the cost of the edge (1,3)) is 5250. 
You can assume that distances are positive, but you should NOT assume that they are distinct.

Your task in this problem is to run the clustering algorithm from lecture on this data set, 
where the target number k of clusters is set to 4. What is the maximum spacing of a 4-clustering?

ADVICE: If you're not getting the correct answer, try debugging your algorithm using some 
small test cases. And then post them to the discussion forum!
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node node_t;

typedef struct nodelist {
	node_t *node;
	node_t *next;
}nodelist_t;

struct node {
	int label;
	int rank;
	node_t *leader;
	nodelist_t *disciples;	
};

typedef struct edge {
	node_t *n1;
	node_t *n2;
	int cost;
}edge_t;

typedef unsigned int unionfind_t;

int main(void) {
	FILE *fp = fopen("clustering1.txt", "r");

	char *line = NULL;
	size_t len;
	ssize_t read;

	int N, M;

	read = getline(&line, &len, fp);
	sscanf(line, "%d\n", &N);
	M = (N*(N-1))/2;
	printf("Number of Nodes: %d\n", N);
	printf("Number of Edges: %d\n", M);

	node_t *nodes = calloc(N+1, sizeof(node_t));
	unionfind_t *uf = calloc(N+1, sizeof(unionfind_t));
	edge_t *edges = calloc(M, sizeof(edge_t));

	for (int i = 1; i <= N; i++) {
		nodes[i].label = i;
		nodes[i].rank = 1;
		nodes[i].leader = &nodes[i];
		nodes[i].disciples = malloc(sizeof(nodelist_t));
		nodes[i].disciples->node = &nodes[i];
		nodes[i].disciples->next = NULL;
	}

	int count = 0;
	while ((read = getline(&line, &len, fp)) != -1) {
		int n1, n2, cost;
		sscanf(line, "%d %d %d\n", &n1, &n2, &cost);
		//	printf("%d -- %d (%d)\n", n1, n2, cost);
		edges[count].n1 = &nodes[n1];
		edges[count].n2 = &nodes[n2];
		edges[count].cost = cost;
		count++;
	}
	printf("Counted edges: %d\n", count);

	// sort the edges

	free(edges);
	free(uf);
	free(nodes);
	fclose(fp);
}
