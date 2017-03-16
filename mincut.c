#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct edge;

struct node {
	int value;
	// list of edges
	struct edge *edgelist;	// pointer to head of list of nodes
}*Nodes;

struct edge {
	struct node *a;
	struct node *b;
	struct edge *next;
	struct edge *prev;
};

int addedge(int a, int b, struct edge **Edges) {
	if (a > b)
		return 0;

	struct node *A = &Nodes[a];
	struct node *B = &Nodes[b];
	struct edge *newedge = malloc(sizeof(struct edge));
	newedge->a = A;
	newedge->b = B;
	newedge->next = *Edges;
	newedge->prev = NULL;
	if (*Edges)
		(*Edges)->prev = newedge;
	*Edges = newedge;	
//	printf("Added edge %d -- %d\n", a, b);

	return 1;
}

int main(void) {

	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	int N = 0;
	int M = 0;

	printf("mincut\n");
	//	fp = fopen("kargerMinCut.txt", "r");
	fp = fopen("karger_test1.txt", "r");
	if (fp == NULL)
		exit(EXIT_FAILURE);

	while ((read = getline(&line, &len, fp)) != -1) {
		N++;
	}
	printf("%d elements\n", N);

	rewind(fp);

	Nodes = calloc (N+1, sizeof(struct node));
	for (int i = 1; i <= N; i++) {
		Nodes[i].value = i;
		Nodes[i].edgelist = NULL;
	}
	struct edge *Edges = NULL;

	while ((read = getline(&line, &len, fp)) != -1) {
		char *pch;
		int a, b;
		pch = strtok(line, " \t\n");
		a = atoi(pch);
//		printf("Node: %d\n", a);
		pch = strtok(NULL, " \t\n");
		while (pch != NULL) {
			b = atoi(pch);
			pch = strtok(NULL, " \t\n");
//			printf("\tNieghbor: %d\n", b);
			M += addedge(a, b, &Edges);
		}
	}
	free(line);
	printf("Number of edges: %d\n", M);

	struct edge *current = Edges;
	while (current) {
		printf("Edge %d -- %d\n", current->a->value, current->b->value);
		current = current->next;
	}

	free(Nodes);
	fclose (fp);

	return 0;
}
