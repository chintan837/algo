#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodelist;

struct node {
	int label;
	int seen;
	int leader;
	struct nodelist *out;
	struct nodelist *in;
};

struct nodelist {
	struct node *node;
	struct nodelist *next;
};

void top5(int *largest, int n) {
	int tmp;
	for (int i = 0; i < 5; i++) {
		if (n > largest[i]) {
			tmp = largest[i];
			largest[i] = n;
			top5(largest, tmp);
			break;
		}
	}
}

void addneigh(struct node **nArray, int a, int b) {
	struct node *node = nArray[a];
	struct node *neigh = nArray[b];

	struct nodelist *outlist = malloc(sizeof(struct nodelist));
	outlist->node = neigh;
	outlist->next = node->out;
	node->out = outlist;
	
	struct nodelist *inlist = malloc(sizeof(struct nodelist));
	inlist->node = node;
	inlist->next = neigh->in;
	neigh->in = inlist;
}

struct nodelist *stack = NULL;

void push(struct node *node) {
	struct nodelist *newnode = malloc(sizeof(struct nodelist));
	newnode->node = node;
	newnode->next = stack;
	stack = newnode;
}

struct node *pop() {
	if (stack == NULL) 
		return NULL;
	struct nodelist *oldnode = stack;
	struct node *node = oldnode->node;

	stack = stack->next;

	free(oldnode);
	return node;
}

void dfs_rev(struct node *node) {
	if (node->seen)
		return;

	node->seen = 1;
	//	printf("going over list of in for node %d\n", node->label);
	struct nodelist *current = node->in;
	while (current) {
		dfs_rev(current->node);
		current = current->next;
	}
	//	printf("adding node %d on stack\n", node->label);
	push(node);
}

int dfs(struct node *node, int leader) {
	int size = 1;
	if (node->seen >= 2)
		return 0;
	node->leader = leader;
	node->seen++;

	struct nodelist *current = node->out;
	while(current) {
		size += dfs(current->node, leader);
		current = current->next;
	}
	return size;
}

int main() {
	printf("SCC\n");

	FILE *fp = fopen("SCC.txt", "r");
	
	char *line = NULL;
	size_t linecap = 0;
	ssize_t linelen;
	int a, b;
	while ((linelen = getline(&line, &linecap, fp)) > 0) {
		sscanf(line, "%d %d\n", &a, &b);
	}
	// max nodes is now in a;
	// create a nodes in an array
	//	printf("Max nodes: %d\n", a);
	int N = a;
	struct node **nArray = calloc(N+1, sizeof(struct node));
	for (int i = 1; i < N+1; i++) {
		struct node *newnode = malloc(sizeof(struct node));
		newnode->label = i;
		newnode->seen = 0;
		newnode->leader = 0;
		newnode->out = NULL;
		newnode->in = NULL;
		nArray[i] = newnode;
	}

	rewind(fp);
	while ((linelen = getline(&line, &linecap, fp)) > 0) {
		sscanf(line, "%d %d\n", &a, &b);
		addneigh(nArray, a, b);
	}
	free(line);

	// finishing times;
	//	t = 0;
	//keep track of finishing times using stack

	printf("starting dfs on rev G\n");
	for (int i = 1; i < N+1; i++) {
		struct node *node = nArray[i];
		if (node->seen)
			continue;
		/* run dfs on the node if not seen */
		//	printf("running dfs on node %d\n", node->label);
		dfs_rev(node);
	}

	printf("Starting dfs on the stack\n");
	struct node *node;
	int *largest = calloc(5, sizeof(int));
	int size = 0;
	while((node = pop())) {
		if (node->seen >= 2)
			continue;
		size = dfs(node, node->label);
		top5(largest, size);
		//	printf("found an SCC with leader %d size %d\n", node->label, size);
	}

	for (int i = 0; i < 5; i++) {
		printf("%d,", largest[i]);
	}
	printf("\n");

	for (int i = 1; i < N+1; i++) {
		free(nArray[i]);
	}
	free(largest);
	fclose (fp);

	return 0;
}
