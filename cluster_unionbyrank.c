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
typedef struct nodelist nodelist_t;
typedef struct edge edge_t;

struct node {
	int label;
	int rank;
	node_t *leader;
};

struct nodelist {
	node_t *node;
	nodelist_t *next;
};

struct edge {
	node_t *n1;
	node_t *n2;
	int cost;
};

typedef unsigned int unionfind_t;

static int 
compar(const void *p1, const void *p2) {
	edge_t *e1 = (edge_t *)p1;
	edge_t *e2 = (edge_t *)p2;

	return (e1->cost - e2->cost);
}

static node_t *
uf_find(node_t *n) {
	if (n == n->leader)
		return n;
	return (uf_find(n->leader));
}

static int
uf_union(node_t *n1, node_t *n2) {
	node_t *l1 = uf_find(n1);
	node_t *l2 = uf_find(n2);

	if (l1 == l2)
		return 0;
	else {
		if (l1->rank > l2->rank) {
			l2->leader = l1;
		} else if (l2->rank > l1->rank) {
			l1->leader = l2;
		} else {
			l1->leader = l2;
			l2->rank++;
		}

		return 1;
	}
}

int main(void) {
	FILE *fp = fopen("clustering1.txt", "r");
#define TARGETK 4
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
		nodes[i].rank = 0;
		nodes[i].leader = &nodes[i];
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
	M = count;	
	// sort the edges
	// TODO: try it yourself
	qsort(edges, M, sizeof(edge_t), compar);

	for (int i = 0; i < M; i++) {
		//	printf("%d %d %d\n", edges[i].n1->label, edges[i].n2->label, edges[i].cost);
	}
	
	int k = N;
	int i = 0;
	int cost;
	while ((k >= TARGETK) && (i < M)) {
		if (uf_union(edges[i].n1, edges[i].n2)) {
			k--;
			cost = edges[i].cost;
		} 
		i++;
	}
	for (int x = 1; x <= N; x++) {
		//	printf("Node: %d(%d) - Leader: %d (%d)\n", nodes[x].label, nodes[x].rank, nodes[x].leader->label, nodes[x].leader->rank);
	}
	printf("Answer: %d\n", cost);
	
	free(edges);
	free(uf);
	free(nodes);
	fclose(fp);
}
