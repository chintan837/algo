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
	int nn;
} node_t;

typedef struct edge {
	node_t *node;
	int cost;
} edge_t;

struct neighlist {
	edge_t *edge;
	nlist_t *next;
};

static void
print_heap(const char *label, node_t **heap, int len) {
	printf("    %s\n", label);
	for (int i = 1; i <= len; i++) {
		node_t *node = heap[i];
		printf("\tIndex: %d, value: %d, node_index: %d, key: %d\n",
				i, node->value, node->index, node->key);
	}
}

static inline void swapp(node_t **p1, node_t **p2) {
	node_t *tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;

	int t = (*p1)->index;
	(*p1)->index = (*p2)->index;
	(*p2)->index = t;
}

static inline void bubble_up(node_t **heap, int child) {
	if (child <= 1)
		return;
	int parent = child/2;
	if (heap[parent]->key > heap[child]->key) {
		swapp(&heap[parent], &heap[child]);
		bubble_up(heap, parent);
	}
}

static int heap_insert(node_t **heap, node_t *node, int len) {
	len++;
	heap[len] = node;
	heap[len]->index = len;

	bubble_up(heap, len);

	return len;
}

static inline void bubble_down(node_t **heap, int parent, int len) {
	for (int child = parent*2; child <= parent*2+1; child++) {
		if (child > len)
			return;
		if (heap[parent]->key > heap[child]->key) {
			swapp(&heap[parent], &heap[child]);
			bubble_down(heap, child, len);
		}
	}
}

static node_t *heap_extract_min(node_t **heap, int *len) {
	if (*len <= 0)
		return NULL;

	swapp(&heap[1], &heap[*len]);
	(*len)--;
	bubble_down(heap, 1, *len);

	return heap[(*len)+1];
}

static void add_neigh(node_t *n1, node_t *n2, int cost) {
	edge_t *newedge = malloc(sizeof(edge_t));
	newedge->node = n2;
	newedge->cost = cost;

	nlist_t *newlistitem = malloc(sizeof(nlist_t));
	newlistitem->edge = newedge;
	newlistitem->next = n1->neigh;
	n1->neigh = newlistitem;
	n1->nn++;
}

int main() {
	//	FILE *fp = fopen("edges.txt", "r");
	FILE *fp = fopen("prim_tc1", "r");
	char *line = NULL;
	size_t len;
	ssize_t read;
	int N = 0, M = 0;
	int n1, n2, cost;

	read = getline(&line, &len, fp);
	sscanf(line, "%d %d", &N, &M);
	printf("N: %d, M: %d\n", N, M);
	node_t **nodes = calloc(N+1, sizeof(node_t *));
	for (int i = 0; i <= N; i++) {
		nodes[i] = malloc (sizeof(node_t));
		nodes[i]->value = i;
		nodes[i]->index = i;
		nodes[i]->key = INT_MAX;
		nodes[i]->neigh = NULL;
		nodes[i]->nn = 0;
	}

	while ((read = getline(&line, &len, fp)) != -1) {
		sscanf(line, "%d %d %d", 	&n1, &n2, &cost);
		add_neigh(nodes[n1], nodes[n2], cost);
		add_neigh(nodes[n2], nodes[n1], cost);
	}

	long int sum = 0;
	int heap_len = N;
	node_t *node;
	nlist_t *current;
	nodes[1]->key = 0;
	print_heap("Current heap", nodes, heap_len);
	while (node = heap_extract_min(nodes, &heap_len)) {
		printf("Extracted node :%d, edge cost: %d\n", node->value, node->key);
		print_heap("After extraction:", nodes, heap_len);
		sum += node->key;
		// node->index = INT_MAX;
		current = node->neigh;
		while(current) {
			edge_t *edge = current->edge;
			if (edge->node->index < heap_len)
				if (edge->node->key > edge->cost) {
					edge->node->key = edge->cost;
					printf("    Updated edge cost for Node %d to %d\n", edge->node->value, edge->node->key);
					// asssuming cost of key only go down, bubbl_up() should take care
					bubble_up(nodes, edge->node->index);
					print_heap("After updatexs:", nodes, heap_len);
				}
				else
					printf("    skipping %d\n", edge->node->value);
			current = current->next;
		}
		print_heap("After updates:", nodes, heap_len);
		printf("--------------------------------\n");
	}
	printf("Total sum: %ld\n", sum);

	fclose(fp);
	return 0;
}
