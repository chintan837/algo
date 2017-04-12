#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define	CHUNKSIZE	1024		

struct node {
	int value;
	int seen;
	struct nodelist *out;
	struct nodelist *in;
};

struct nodelist  {
	struct node *node;
	struct nodelist *next;
};

struct node **nodes;

struct node *getnode(int x) {
	if (x < 1 || x > 875714)
		printf("why are we running getnode on %d", x);
	if (x > CHUNKSIZE*CHUNKSIZE) {
		printf("input node greater than allocated chunks\n");
		exit(EXIT_FAILURE);
	}
	if (nodes[x] == NULL) {
		nodes[x] = malloc(sizeof (struct node));
		if (nodes[x] == NULL) {
			printf("Cannot allocate memory\n");
			exit(EXIT_FAILURE);
		}
		nodes[x]->value = x;
		nodes[x]->seen = 0;
		nodes[x]->in = NULL;
		nodes[x]->out = NULL;
	}

	return nodes[x];
}

int sanity() {

	return 0;
}

void addnode(struct node *node, struct nodelist **list) {
	struct nodelist *newnode = malloc(sizeof(struct nodelist));
	newnode->node = node;
	newnode->next = *list;
	*list = newnode;
	return;
}

void deletelist(struct nodelist **neigh) {
	struct nodelist *current;
	struct nodelist *prev;
	while (*neigh) {
		current = *neigh;
		*neigh = (*neigh)->next;
		free(current);
	}
}

void addneighbor(struct node *a, struct node *b) {
	addnode(b, &(a->out));
	addnode(a, &(b->in));
}

void dfs_rev(struct node *node, struct nodelist **allnodes) {
	if (node->seen)
		return;
	node->seen = 1;

	struct nodelist *current = node->in;
	while (current) {
		dfs_rev(current->node, allnodes);
		current = current->next;
	}

	addnode(node, allnodes);
}

int dfs(struct node *node, int leader) {
	if (node == NULL) {
		printf("invalid node pointer\n");
		exit(EXIT_FAILURE);
	}
	if (node->seen == 0)
		return 0;
	node->seen = 0;
	int count = 1;

	struct nodelist *current = node->out;
	while (current) {
		count += dfs(current->node, leader);
		current = current->next;
	}

	return count;
}

int main (int argc, char **argv) {
	for (int i = 0; i < argc; i++) {
		printf("%s\n", argv[i]);
	}

	nodes = calloc(1024*1024, sizeof(struct node *));
	if (nodes == NULL) {
		printf("calloc faled %d\n", __LINE__);
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < 1024*1024; i++)
		nodes[i] = NULL;

	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	fp = fopen("SCC.txt", "r");
	//	fp = fopen("scc_1.txt", "r");
	perror("fopen");

	//	while ((read = getline(&line, &len, fp)) != -1) {
	int a = 0, b = 0;
	while (fscanf(fp, "%d %d\n", &a, &b) != EOF) {
		addneighbor(getnode(a), getnode(b));
	}
	printf("Done adding edges\n");
	fclose (fp);

	// GREV
	struct nodelist *allnodes = NULL;
	for (int i = 1; i < CHUNKSIZE*CHUNKSIZE; i++) {
		struct node *node = nodes[i];
		if (node)
			dfs_rev(node, &allnodes);
	}
	printf("DFS_rev completed\n");

	struct nodelist *current = allnodes;
	int count = 0;

	int maxes[6] = {0, 0, 0, 0, 0, 0};

	while (current) {
		count = dfs(current->node, current->node->value);
		maxes[5] = count;
		for (int x = 4, y = 5; x >= 0; x--, y--) {
			if (maxes[y] > maxes[x]) {
				int tmp = maxes[y];
				maxes[y] = maxes[x];
				maxes[x] = tmp;
			} else
				break;
		}
		current = current->next;
	}

	for (int x = 0; x < 5; x++) {
		printf("%d, ", maxes[x]);
	}
	printf("\n");
	printf("DFS completed\n");
	
	deletelist(&allnodes);
	for (int i = 0; i < 1024*1024; i++) {
		if (nodes[i]) {
			deletelist(&(nodes[i]->out));
			deletelist(&(nodes[i]->in));
			free(nodes[i]);
		}
	}
	free(nodes);

	return 0;
}
