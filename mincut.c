#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct node {
	int value;
	struct node *next;
	struct node *prev;
	// list of edges
}

struct edge {
	struct node *a;
	struct node *b;
	struct edge *next;
	struct edge *prev;
}


int main(void) {
	FILE *fp = fopen("karger_test1.txt", "r");
	

	fclose (fp);

	printf("mincut\n");
	return 0;
}
