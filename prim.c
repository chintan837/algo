/*
   In this programming problem you'll code up Prim's minimum spanning tree algorithm

   This file describes an undirected graph with integer edge costs. It has the format

   [number_of_nodes] [number_of_edges]

   [one_node_of_edge_1] [other_node_of_edge_1] [edge_1_cost]

   [one_node_of_edge_2] [other_node_of_edge_2] [edge_2_cost]

   ...

   For example, the third line of the file is "2 3 -8874", indicating that there is 
   an edge connecting vertex #2 and vertex #3 that has cost -8874.

   You should NOT assume that edge costs are positive, nor should you assume that 
   they are distinct.

   Your task is to run Prim's minimum spanning tree algorithm on this graph. You 
   should report the overall cost of a minimum spanning tree --- an integer, which 
   may or may not be negative --- in the box below.

   IMPLEMENTATION NOTES: This graph is small enough that the straightforward O(mn) 
   time implementation of Prim's algorithm should work fine. OPTIONAL: For those 
   of you seeking an additional challenge, try implementing a heap-based version. 
   The simpler approach, which should already give you a healthy speed-up, is to 
   maintain relevant edges in a heap (with keys = edge costs). The superior approach 
   stores the unprocessed vertices in the heap, as described in lecture. Note this 
   requires a heap that supports deletions, and you'll probably need to maintain 
   some kind of mapping between vertices and their positions in the heap.
   */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct neighlist nlist_t;

typedef struct node {
	int value;
	int index;
	int key;
	nlist_t *neigh;
} node_t;

typedef struct edge {
	node_t *node;
	int cost;
} edge_t;

struct neighlist {
	edge_t *edge;
	nlist_t *next;
};

static inline void bubble_up() {

}

static void heap_insert() {

}

static inline void bubble_down() {

}

static node_t *heap_extract_min() {

}

static void add_neigh(node_t *n1, node_t *n2, int cost) {
	edge_t *newedge = malloc(sizeof(edge_t));
	newedge->node = n2;
	newedge->cost = cost;

	nlist_t *newlistitem = malloc(sizeof(nlist_t));
	newlistitem->edge = newedge;
	newlistitem->next = n1->neigh;
	n1->neigh = newlistitem;
}

int main() {
	FILE *fp = fopen("edges.txt", "r");
	char *line = NULL;
	size_t len;
	ssize_t read;
	int N = 0, M = 0;
	int n1, n2, cost;

	read = getline(&line, &len, fp);
	sscanf(line, "%d %d", &N, &M);
	printf("N: %d, M: %d\n", N, M);
	node_t *nodes = calloc(N+1, sizeof(node_t));
	for (int i = 0; i <= N; i++) {
		nodes[i].value = i;
		nodes[i].index = i;
		nodes[i].key = INT_MAX;
		nodes[i].neigh = NULL;
	}

	while ((read = getline(&line, &len, fp)) != -1) {
		sscanf(line, "%d %d %d", 	&n1, &n2, &cost);
		add_neigh(&nodes[n1], &nodes[n2], cost);
		add_neigh(&nodes[n2], &nodes[n1], cost);
	}

	long int sum = 0;
	nodes[1].key = 



	fclose(fp);
	return 0;
}
