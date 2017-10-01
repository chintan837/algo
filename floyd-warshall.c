#include <stdio.h>
#include <stdlib.h>

struct node;
struct nodelist;

struct node {
	int data;
	struct nodelist *out;
};

struct nodelist {
	struct node *node;
	struct nodelist *next;
};




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
	while((readlen = getline(&line, &readcapp, fp)) > 0) {
		int a, b, weight;
		sscanf(line, "%d %d %d", &a, &b, &weight);
		printf("%d %d %d\n", a, b, weight);
	}
	printf("%d %d\n", N, M);

	free(line);
	fclose(fp);
}
