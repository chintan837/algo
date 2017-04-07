#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define	CHUNKSIZE	1024		

struct node {
	int value;
	int seen;
	int valid;
	struct nodelist *out;
	struct nodelist *in;
};

struct nodelist  {
	struct node *node;
	struct nodelist *next;
};

struct node **nodes;

struct node *getnode(int x) {
	if (x > CHUNKSIZE*CHUNKSIZE) {
		printf("input node greater than allocated chunks\n");
		exit(EXIT_FAILURE);
	}

	int x_high = x / CHUNKSIZE;
	int x_low = x % CHUNKSIZE;

	return &nodes[x_high][x_low];
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
	while (*neigh) {
		current = *neigh;
		*neigh = (*neigh)->next;
		free(current);
	}
}

void addneighbor(struct node *a, struct node *b) {
	a->valid = 1;
	b->valid = 1;

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

	nodes = calloc(CHUNKSIZE, sizeof(struct node *));
	if (nodes == NULL) {
		printf("calloc faled %d\n", __LINE__);
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < CHUNKSIZE; i++) {
		nodes[i] = calloc(CHUNKSIZE, sizeof(struct node));
		if (nodes == NULL) {
			printf("calloc faled %d\n", __LINE__);
			exit(EXIT_FAILURE);
		}
		for (int j = 0; j < CHUNKSIZE; j++) {
			nodes[i][j].value = i*CHUNKSIZE+j;
			nodes[i][j].seen = 0;
			nodes[i][j].valid = 0;
			nodes[i][j].out = NULL;
			nodes[i][j].in = NULL;
		}
	}

	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	fp = fopen("SCC.txt", "r");
	perror("fopen");

	//	while ((read = getline(&line, &len, fp)) != -1) {
	int a = 0, b = 0;
	while (fscanf(fp, "%d %d\n", &a, &b) != EOF) {
		addneighbor(getnode(a), getnode(b));
	}
	printf("Done adding edges\n");
	fclose (fp);

	// GREV
	struct nodelist *allnodes;
	for (int i = 0; i < CHUNKSIZE; i++) {
		for (int j = 0; j < CHUNKSIZE; j++) {
			struct node *node = &nodes[i][j];
			if (node->valid)
				dfs_rev(node, &allnodes);
		}	
	}
	printf("DFS_rev completed\n");

	struct nodelist *current = allnodes;
	int count = 0;
	while (current) {
		count = dfs(current->node, current->node->value);
		printf("SCC size: %d\n", count);
		current = current->next;
	}
	printf("DFS completed\n");
	
	for (int i = 0; i < CHUNKSIZE; i++) {
		for (int j = 0; j < CHUNKSIZE; j++) {
			deletelist(&(nodes[i][j].out));
			deletelist(&(nodes[i][j].in));
		}	
		free(nodes[i]);
	}	
	free(nodes);

	return 0;
}
