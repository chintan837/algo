#include <stdio.h>
#include <stdlib.h>

struct node;
struct nodelist;

struct node {
	int label;
	struct nodelist *out;
};

struct nodelist {
	struct node *node;
	struct nodelist *next;
};

struct edge {
    int source;
    int dest;
    int weight;
};

void addedge (int a, int b, int weight, struct edge **edges, struct node *nodes) {

}

int main(void) {
	FILE *fp = fopen("g1.txt", "r");
	if (fp == NULL) {
		perror("fopen");
		return -1;
	}

	char *line = NULL;
	size_t readcapp = 0;
	ssize_t readlen = 0;
	readlen = getline(&line, &readcapp, fp);
	if (readlen <= 0 ) {
		printf("file empty!\n");
		return -1;
	}
	int N, M;
	sscanf(line, "%d %d", &N, &M);
    struct edge *edges = calloc (M+1, sizeof(struct edge));
	struct node *nodes = calloc (N+1, sizeof(struct node));
    for (int i = 1; i < N+1; i++) {
        nodes[i].label = i;
        nodes[i].out = NULL;
    }

    while((readlen = getline(&line, &readcapp, fp)) > 0) {
		int a, b, weight;
		sscanf(line, "%d %d %d", &a, &b, &weight);
        addedge(a, b, weight, &edges, &nodes);
	}
	printf("%d %d\n", N, M);

    int **A = malloc();
    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                
            }
        }
    }

	free(edges);
	free(nodes);
	free(line);
	fclose(fp);
}
