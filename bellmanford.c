#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INFINITY "\u221E"

struct Node;

struct EdgeList {
    struct Node *node;
    int length;
    struct EdgeList *next;
};

struct Node {
    int label;
    struct EdgeList *ingress;
    struct EdgeList *egress;
};

int min(int a, int b) {return (a < b? a: b);}

void listAdd(struct EdgeList **nl, struct Node* node, int length) {
    struct EdgeList *newElem = malloc(sizeof(struct EdgeList));

    newElem->node = node;
    newElem->length = length;
    newElem->next = NULL;
    if (nl == NULL) {
       *nl = newElem;
       return;
    } else {
        newElem->next = *nl;
        *nl = newElem;
    }
}

struct Node *newNode(int label) {
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->label = label;
    newNode->ingress = NULL;
    newNode->egress = NULL;

    return newNode;
}

void addEdge(struct Node **nodes, int src, int dst, int length) {
    listAdd (&nodes[src]->egress, nodes[dst], length);
    listAdd (&nodes[dst]->ingress, nodes[src], length);
}

int main(void) {
    int N = 0, M = 0;
    // FILE *fp = fopen("g1.txt", "r");
    FILE *fp = fopen("bm-tc1", "r");
    char *line;
    size_t len = 0;
    ssize_t read;
	read = getline(&line, &len, fp);
    if (read < 0)
        printf("file seems to be empty");
    sscanf(line, "%d %d\n", &N, &M);
    printf("N: %d, M: %d\n", N, M);

    struct Node **nodes = calloc (N+1, sizeof(struct Node));
    for (int i = 1; i <= N; i++) {
        nodes[i] = newNode(i);
    }
    while ((read = getline(&line, &len, fp)) != -1) {
        int src = 0, dst = 0, length = 0;
        sscanf(line, "%d %d %d\n", &src, &dst, &length);
        printf("src: %d, dst: %d, length: %d\n", src, dst, length);
        addEdge(nodes, src, dst, length);
    }

    for (int i = 1; i <= N; i++) {
        struct Node *node = nodes[i];
        printf("Node: %d\n", node->label);
        printf("Ingress:\t");
        struct EdgeList *nl;
        nl = node->ingress;
        while (nl) {
            printf("%d ", nl->node->label);
            nl = nl->next;
        }
        printf("\nEgress: \t");
        nl = node->egress;
        while (nl) {
            printf("%d ", nl->node->label);
            nl = nl->next;
        }
        printf("\n");
    }

    int **A = calloc(N+1, sizeof(int *));
    for (int i = 0; i < N+1; i++) {
        A[i] = calloc(N+1, sizeof(int));
    }

    int src = 1;
    int i = 0;
    for (int n = 1; n < N+1; n++) {
        A[i][n] = INT_MAX;
    }
    A[i][src] = 0;
    printf("A[%d][N]:\n", i);
    for (int n = 1; n < N+1; n++) {
        printf("%d ", A[i][n]);
    }
    printf("\n");

    for (i = 1; i < N; i++) {
        printf("A[%d][N]:\n", i);
        for (int n = 1; n <= N; n++) {
            struct EdgeList *current = nodes[n]->ingress;
            int min_weight = INT_MAX;
            printf("Node: %d ", n);
            while (current) {
                printf("neighbor: %d weight: %d\n", current->node->label, current->length);
                int current_weight = A[i-i][current->node->label];
                printf("current_weight: %d\n", current_weight);
                if (current_weight != INT_MAX) 
                    current_weight += current->length;
                if (current_weight < min_weight) 
                    min_weight = current_weight;

                current = current->next;
            }
            printf("Comparing: %d and %d\n", A[i-1][n], min_weight);
            A[i][n] = min(A[i-1][n], min_weight);
            printf("got: %d\n", A[i][n]);
        }
        printf("\n");
    }

    printf("A[%d][N]:\n", i-1);
    for (int n = 1; n <= N; n++) {
        printf("%d ", A[i-1][n]);
    }
    printf("\n");

    for (int i = 0; i < N+1; i++) {
        free(A[i]);
    }
    free (A); 

    free(nodes);
    fclose(fp);
}
