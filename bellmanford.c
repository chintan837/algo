#include <stdio.h>
#include <stdlib.h>

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
    FILE *fp = fopen("g1.txt", "r");
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
        printf("src: %d, dst: %d\n", src, dst);
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
        getchar();
    }

    free(nodes);
    fclose(fp);
}
