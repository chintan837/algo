#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct edgelist;

struct node {
	int value;
	struct edgelist *neigh;	// pointer to head of list of edges 
}*Nodes;

struct edge {
	struct node *a;
	struct node *b;
	struct edgelist *pos;
};

struct edgelist {
	struct edge *edge;
	struct edgelist *next;
	struct edgelist *prev;
};

struct edgelist *Edges = NULL;

int addneigh(int a, int b) {
	if (a > b)
		return 0;

	//	printf("Added edge %d -- %d\n", a, b);

	struct node *A = &Nodes[a];
	struct node *B = &Nodes[b];
	struct edge *newedge = malloc (sizeof (struct edge));
	newedge->a = A;
	newedge->b = B;

	struct edgelist *newedgelist;
	newedgelist = malloc (sizeof(struct edgelist));
	newedge->pos = newedgelist;
	newedgelist->edge = newedge;
	newedgelist->next = Edges;
	Edges = newedgelist;

	newedgelist = malloc (sizeof(struct edgelist));
	newedgelist->edge = newedge;
	newedgelist->next = A->neigh;
	A->neigh = newedgelist;
	
	newedgelist = malloc (sizeof(struct edgelist));
	newedgelist->edge = newedge;
	newedgelist->next = B->neigh;
	B->neigh = newedgelist;
	return 1;
}

int purgelist(struct edgelist **list) {
	int ret = 0;
	struct edgelist *curr;
	struct edgelist *prev;
	
	curr = *list;
	prev = NULL;
	while ((curr = *list) && (curr->edge->a == curr->edge->b)) {
		printf("examing edge %d--%d\n", curr->edge->a->value, curr->edge->b->value);
		prev = curr;
		*list = (*list)->next;
		free(prev);
		ret++;
	}
	while (curr != NULL) {
		printf("examing edge %d--%d\n", curr->edge->a->value, curr->edge->b->value);
		prev = curr;
		prev = curr;
		curr = curr->next;
		if (prev->edge->a == prev->edge->b) {
			free(prev);
			ret++;
		}
	}

	return ret;
}

int deleteedge(struct edge *edge, int coin) {
	int ret = 0;
	if (coin) {
		struct node *tmp = edge->a;
		edge->a = edge->b;
		edge->b = tmp;
	}

	struct edgelist *curr;
	struct edgelist *prev;

	curr = edge->a->neigh;
	prev = NULL;
	while (curr != NULL) {
		if (curr->edge->a == edge->a) {
			curr->edge->a = edge->b;
		} else {
			curr->edge->b = edge->b;
		}
		prev = curr;
		curr = curr->next;
		free(prev);
	}
	edge->a->neigh = NULL;

	ret = purgelist(&(edge->b->neigh));
	
	return ret;
}

int main(void) {

	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	int N = 0;
	int M = 0;
	time_t t;
	srand(time(&t));

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
		Nodes[i].neigh = NULL;
	}

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
			M += addneigh(a, b);
		}
	}
	free(line);
	printf("Number of edges: %d\n", M);

	int n = N;
	int m = M;
	while (n > 2) {
		int target = rand()%m;
		int coin = rand()%2;

		printf("picked %2d of %2d, coin %d\n", target, m, coin);

		int count = 0;
		struct edgelist *current = Edges;
		while (count < target) {
			count++;
			current = current->next;
		}
		m -= deleteedge(current->edge, coin);
		printf("Remaining edges = %d\n", m);
		n--;
	}

	printf("-- Remaining edges = %d --\n", m);

	free(Nodes);
	fclose (fp);

	return 0;
}
