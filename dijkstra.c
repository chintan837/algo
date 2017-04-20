#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

#define FINAL

struct node {
	int value;
	int distance;
	int seen;
	struct edgelist *edges;
};

struct edge {
	struct node *node;
	int len;
};

struct edgelist {
	struct edge *edge;
	struct edgelist *next;
};

struct node *nodes;

void swapp(struct edge **a, struct edge **b) {
	struct edge *tmp = *a;
	*a = *b;
	*b = tmp;
}

void bubble_down(struct edge **heap, int len, int parent) {
	for (int child = parent * 2; child <= (parent*2+1); child++) {
		if (child > len)
			return;

		if (heap[child]->len < heap[parent]->len) {
			swapp(&heap[child], &heap[parent]);
			bubble_down(heap, len, child);
		}
	}
}

struct edge *get_min(struct edge **heap, int *len) {
	if (*len < 1) 
		return NULL;
	struct edge *c = heap[1];
	
	swapp(&heap[1], &heap[*len]);
	--*len;

	bubble_down(heap, *len, 1);

	return c;
}

void bubble_up(struct edge **heap, int heap_len, int child) {
	if (child <= 1) 
		return;

	int parent = child/2;

	//	printf("%s - %d[%d](parent) and %d[%d](child)\n", __func__, heap[parent]->len, parent, heap[child]->len, child);
	if (heap[parent]->len > heap[child]->len) {
		swapp(&heap[child], &heap[parent]);
		//	printf("swapped\n");
		bubble_up(heap, heap_len, parent);
	}
}

int heap_add(struct edge *edge, int distance, struct edge **heap, int heap_len) {
	heap_len++;
	//	printf("Adding edge %d with weight %d+%d at index %d\n", edge->node->value, edge->len, distance, heap_len);
	edge->len += distance;
	heap[heap_len] = edge;

	/* buble up */
	bubble_up(heap, heap_len, heap_len);

	return heap_len;
}

int node_add(struct node *node, struct edge **heap, int heap_len) {
	struct edgelist *current = node->edges;
	//	printf("Adding node %d to {Found nodes}\n", node->value);
	while (current) {
		if (current->edge->node->distance == INT_MAX)
			heap_len = heap_add(current->edge, node->distance, heap, heap_len);
		current = current->next;
#ifndef FINAL 
		printf("heap: %d\n", heap_len);
		for (int i = 1; i <= heap_len; i++) {
			printf("\t%d[%d]\n", heap[i]->node->value, heap[i]->len);
		}
#endif
	}

	return heap_len;
}

void addedge(int s, int t, int len) {
	struct node *source = &nodes[s];
	struct node *target = &nodes[t];

	struct edge *newedge = malloc(sizeof(struct edge));
	newedge->node = target;
	newedge->len = len;

	struct edgelist *newedgelist = malloc(sizeof(struct edgelist));
	newedgelist->edge = newedge;
	newedgelist->next = source->edges;
	source->edges = newedgelist;
}

void print_graph(struct node *nodes) {
	for (int i = 1; i <= 200; i++) {
		printf("%d", nodes[i].value);
		struct edgelist *current = nodes[i].edges;
		while (current) {
			printf("\t%d (%d)\n", current->edge->node->value, current->edge->len);
			current = current->next;
		}
	}
}

int main(int argc, char *argv[]) {
	for (int i = 0; i < argc; i++) {
		printf("%s\n", argv[i]);
	}

	FILE *fp = fopen("dijkstraData.txt","r");
	char *line;
	size_t len = 0;
	ssize_t read;
	char *ptr;
	char *token;
	int s = 0, t = 0, w = 0;
	int M = 0;

	nodes = calloc(200+1, sizeof(struct node));
	for (int i = 1; i <= 200; i++) {
		nodes[i].value = i;
		nodes[i].distance = INT_MAX; /*distance from node 1 */
		nodes[i].seen = 0;
		nodes[i].edges = NULL;
	}

	while ((read = getline(&line, &len, fp)) != -1) {
		token = strtok(line, "\t");
		s = atoi(token);
		int flag = 1;
		while (token = strtok(NULL, ",\t\n\r")){
			if (flag) {
				t = atoi(token);
				flag = 0;
			} else {
				w = atoi(token);
				flag = 1;
				addedge(s, t, w);
				M++;
			}
		}
	}
	fclose(fp);
	free(line);

	//	print_graph(nodes);

	/* Dijkstra on node 1 */
	printf("Number of edges: %d\n", M);	
	struct edge **heap = calloc(M+1, sizeof(struct edge *));
	int heap_len = 0;

	nodes[1].distance = 0;
	heap_len = node_add(&nodes[1], heap, heap_len);
	int answer[201];

	struct edge *c; 
	while ((c = get_min(heap, &heap_len))) {
		if (c->node->seen)
			continue;
		c->node->distance = c->len;
		//	printf("Retrieved edge: %d %d %d\n", c->node->value, c->len, c->node->distance);
		c->node->seen = 1;
		answer[c->node->value] = c->len;
		heap_len = node_add(c->node, heap, heap_len);
	}

	for (int i = 1; i <= 200; i++) {
		switch (i) {
			case 7:
			case 37:
			case 59:
			case 82:
			case 99:
			case 115:
			case 133:
			case 165:
			case 188:
			case 197:
				printf("%d,", answer[i]);
			default:
				continue;
		}
		printf("\n");
	}

	for (int i = 1; i <= 200; i++) {
		struct edgelist *current = nodes[i].edges;
		struct edgelist *prev;
		while (current) {
			free(current->edge);
			prev = current;
			current = current->next;
			free(prev);
		}
	}
	free(nodes);
	free(heap);
}
