#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static inline int min(int a, int b) { return (a < b? a : b); }
static inline int sum(int a, int b) {
    if (a == INT_MAX)
        return a;
    if (b == INT_MAX)
        return b;
    return (a + b);
}

int main(int argc, char **argv) {
    int N = 0, M = 0;

    if (argc != 2) {
        printf("Provide file name\n");
        return (1);
    }
    char *filename = argv[1];;

	FILE *fp = fopen(filename, "r");
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
	sscanf(line, "%d %d", &N, &M);

    printf("alloc\n");
    int ***A = (int ***) malloc((N+1) * sizeof(int **));
    for (int i = 0; i < N+1 ; i++) {
        A[i] = (int **) malloc((N+1) * sizeof(int *));
        for (int j = 0; j < N+1 ; j++) {
            A[i][j] = (int *) malloc((N+1) * sizeof(int));
            for (int k = 0; k < N+1; k++) {
                if (i == j) 
                    A[i][j][k] = 0; //path to self is 0
                else
                    A[i][j][k] = INT_MAX;
                }
        }
    }

    printf("init\n");
    int i = 0, j = 0, k = 0;
    for (i = 1; i <= N; i++) {
        for (j = 1; j <= N; j++) {
            if (i == j) 
                A[i][j][k] = 0; //path to self is 0
            else
                A[i][j][k] = INT_MAX;
        }
    }
    printf("read file\n");
    while((readlen = getline(&line, &readcapp, fp)) > 0) {
		int a, b, weight;
		sscanf(line, "%d %d %d", &a, &b, &weight);
        A[a][b][k] = weight; // should take care of dupliates here
	}

    printf("calulating min paths\n");
    for (k = 1; k <= N; k++) {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                A[i][j][k] = min(A[i][j][k-1], sum(A[i][k][k-1], A[k][j][k-1]));
            }
        }
    }
    printf("detect negative cycle\n");
    for (int i = 1; i <= N; i++) {
        if (A[i][i][N] < 0) {
            printf("NULL\n");
            exit(1);
        }
    }
    printf("find out min\n");
    int min_weight = INT_MAX;
    k = N;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if ((A[i][j][k]) < min_weight)
                min_weight = A[i][j][k];
        }
    }

    printf("min-weight: %d\n", min_weight);

    printf("freeing...\n");
    for (int i = 0; i < N+1 ; i++) {
        for (int j = 0; j < N+1 ; j++) {
            free(A[i][j]);
        }
        free(A[i]);
    }
    free(A);
	free(line);
	fclose(fp);
}
