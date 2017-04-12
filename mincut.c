#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

struct edgelist;

struct node {
	int value;
	struct edgelist *neigh;	// pointer to head of list of edges 
};

struct edge {
	struct node *a;
	struct node *b;
	int refcnt;
};

struct edgelist {
	struct edge *edge;
	struct edgelist *next;
};

struct node *initnnodes(int N) {
	struct node *nodes = calloc (N+1, sizeof(struct node));
	for (int i = 1; i <= N; i++) {
		nodes[i].value = i;
		nodes[i].neigh = NULL;
	}

	return nodes;
}

void freennodes(struct node *nodes) {
	free(nodes);
}

void listadd(struct edge *node, struct edgelist **head) {
	struct edgelist *newedge = malloc(sizeof(struct edgelist));

	node->refcnt++;
	newedge->edge = node;
	newedge->next = *head;
	*head = newedge;

	return;
}

struct edge *createedge(int a, int b, struct node *nodes) {
	struct node *A = &nodes[a];
	struct node *B = &nodes[b];

	struct edge *newedge = malloc (sizeof (struct edge));
	newedge->a = A;
	newedge->b = B;
	newedge->refcnt = 0;

	return newedge;
}

void deleteedge(struct edge *edge) {
	edge->refcnt--;
	if (edge->refcnt == 0)
		free(edge);
}

void printlist(char *tag, struct edgelist *edges) {
	printf("%s:\n", tag);
	while (edges) {
		printf("\t%d--%d\n", edges->edge->a->value, edges->edge->b->value);
		edges = edges->next;
	}
}

struct edge *pickedge(struct edgelist *edges, int t) {
	int count  = 0;
	while (edges && count < t) {
		edges = edges->next;
		count++;
	}
	return edges->edge;
}

int purgelist(struct edgelist **list) {
	int ret = 0;
	struct edgelist *current = *list;

	while (current && (current->edge->a->value == current->edge->b->value)) {
		deleteedge(current->edge);
		*list = current->next;
		free(current);
		ret++;
		current = *list;
	}
	struct edgelist *prev = current;
	while (current) {
		if  (current->edge->a->value == current->edge->b->value) {
			prev->next = current->next;
			deleteedge(current->edge);
			free(current);
			ret++;
			current = prev->next;
		} else {
			prev = current;
			current = current->next;
		}
	}

	return ret;
}

void randomedge(struct edge *edge) {
	if (rand()%2) {
		struct node *tmp = edge->a;
		edge->a = edge->b;
		edge->b = tmp;
	}
}

void sanity() {
	int n = 4;
	int m = 0;
	struct edgelist *edges = NULL;
	struct edge *edge;
	struct node *nodes = initnnodes(n);

	edge = createedge(1, 2, nodes);
	m++;
	listadd(edge, &edges);
	edge = createedge(1, 3, nodes);
	m++;
	listadd(edge, &edges);
	edge = createedge(2, 2, nodes);
	m++;
	listadd(edge, &edges);
	edge = createedge(2, 3, nodes);
	m++;
	listadd(edge, &edges);
	edge = createedge(3, 3, nodes);
	m++;
	listadd(edge, &edges);
	edge = createedge(4, 4, nodes);
	m++;
	listadd(edge, &edges);

	printlist("Test print", edges);
	
	int t = rand()%m;
	t = 4;
	printf("Picking edge %d of %d\n", t, m);
	edge = pickedge(edges, t);
	printf("Edge: %d -- %d\n", edge->a->value, edge->b->value);
	purgelist(&edges);
	printlist("after purge", edges);

	freennodes(nodes);

	exit(EXIT_SUCCESS);
}


int addneigh(int a, int b, struct node *nodes, struct edgelist **edges) {
	if (a > b)
		return 0;

	struct edge *edge;
	
	edge = createedge(a, b, nodes);
	listadd(edge, edges);
	listadd(edge, &(nodes[a].neigh));
	listadd(edge, &(nodes[b].neigh));

	return 1;
}

void killvictim(struct node *victim, struct node *target) {
	struct edgelist *current = victim->neigh;
	struct edgelist *del;

	while (current) {
		if (current->edge->a == victim) {
			current->edge->a = target;
		} else {
			current->edge->b = target;
		}
		del = current;
		current = current->next;
		listadd(del->edge, &(target->neigh));
		deleteedge(del->edge);
		free(del);
	}
	victim->neigh = NULL;
}

void reduceedge(struct edge *edge) {
	struct node *victim = edge->a;
	struct node *target = edge->b;

	killvictim(victim, target);
	purgelist(&(target->neigh));
}

int mincut(int N, FILE *fp) {
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	int M = 0;

	struct node *nodes = initnnodes(N);
	struct edgelist *edges = NULL;
	struct edge *edge = NULL;

	rewind(fp);

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
			M += addneigh(a, b, nodes, &edges);
		}
	}
	free(line);

	int n = N;
	int m = M;
	int ans = 0;
	while (n > 2) {
		int t = rand()%m;
		edge = pickedge(edges, t);
		randomedge(edge);
		reduceedge(edge);
		m -= purgelist(&edges);
		n--;
	}
	edge = pickedge(edges, 0);
	reduceedge(edge);
	purgelist(&edges);

	freennodes(nodes);

	return m;
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
	//	srand(0);

	//	sanity();

	fp = fopen("kargerMinCut.txt", "r");
	//	fp = fopen("karger_test1.txt", "r");
	//	fp = fopen("karger_test0.txt", "r");
	if (fp == NULL)
		exit(EXIT_FAILURE);

	while ((read = getline(&line, &len, fp)) != -1) {
		N++;
	}

	int minans = INT_MAX;
	for (int i = 0; i < N; i++) {
		int ans = mincut(N, fp);
		if (minans > ans)
			minans = ans;
	}


	fclose (fp);

	printf("mincut: %d\n", minans);


	return 0;
}
