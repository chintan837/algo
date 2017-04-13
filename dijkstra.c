#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

struct node {
	int value;
	int distance;
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

int heap_add(struct edge *edge, int distance, struct edge **heap, int heap_len) {
	printf("Adding edge %d with weight %d+%d\n", edge->node->value, edge->len, distance);
	
	edge->len += distance;
	heap[heap_len] = edge;

	/* buble up */

	return ++heap_len;
}

int node_add(struct node *node, struct edge **heap, int heap_len) {
	struct edgelist *current = node->edges;
	printf("Adding node %d to {Found nodes}\n", node->value);
	while (current) {
		heap_len = heap_add(current->edge, node->distance, heap, heap_len);

		current = current->next;
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
		nodes[i].distance = INT_MAX;
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
	struct edge **heap = calloc(M, sizeof(struct edge *));
	int heap_len = 0;

	nodes[1].distance = 0;
	heap_len = node_add(&nodes[1], heap, heap_len);

	printf("%d nodes added\n", heap_len);

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

}
