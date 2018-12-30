#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INFINITY "\u221E"

struct Node;

struct EdgeList {
    struct Node *node;
    int length;
    int plength;
    struct EdgeList *next;
};

struct Node {
    int label;
    int bellman_weight;
    int dijkstra_key;
    int dijkstra_seen;
    struct EdgeList *ingress;
    struct EdgeList *egress;
};

int min(int a, int b) {return (a < b? a: b);}

void listAdd(struct EdgeList **nl, struct Node* node, int length) {
    struct EdgeList *newElem = malloc(sizeof(struct EdgeList));

    newElem->node = node;
    newElem->length = length;
    newElem->plength = 0;
    newElem->next = NULL;
    if (nl == NULL) {
       *nl = newElem;
    } else {
        newElem->next = *nl;
        *nl = newElem;
    }
}

struct Node *newNode(int label) {
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->label = label;
    newNode->bellman_weight = 0;
    newNode->ingress = NULL;
    newNode->egress = NULL;

    return newNode;
}

void addEdge(struct Node **nodes, int src, int dst, int length) {
    listAdd (&nodes[src]->egress, nodes[dst], length);
    listAdd (&nodes[dst]->ingress, nodes[src], length);
}

void print_graph(struct Node **nodes, int N) {
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
}

struct Node **parse_file(FILE *fp, int *n) {
    char *line;
    size_t len = 0;
    ssize_t read;
    int N = 0, M = 0;

    read = getline(&line, &len, fp);
    if (read < 0) {
        printf("file seems to be empty");
        exit(1);
    }
    sscanf(line, "%d %d\n", &N, &M);

    struct Node **nodes = calloc (N+1, sizeof(struct Node));
    for (int i = 1; i <= N; i++) {
        nodes[i] = newNode(i);
    }
    while ((read = getline(&line, &len, fp)) != -1) {
        int src = 0, dst = 0, length = 0;
        sscanf(line, "%d %d %d\n", &src, &dst, &length);
        addEdge(nodes, src, dst, length);
    }
    *n = N;
    return nodes;
}

int bellmanford(struct Node **nodes, int N, int src, int **A) {
    int stop_early = 0;
    int min_length = INT_MAX;
    int i;

    i = 0;
    for (int n = 1; n < N+1; n++) {
        A[i][n] = INT_MAX;
    }
    A[i][src] = 0;

    i = 1;
    for (int n = 1; n <= N; n++) {
        A[i][n] = 0;
    }
    A[i][src] = 0;

    for (i = 2; i < N; i++) {
        stop_early = 1;
        for (int n = 1; n <= N; n++) {
            struct EdgeList *current = nodes[n]->ingress;
            int min_weight = INT_MAX;
            while (current) {
                int current_weight = A[i-1][current->node->label];
                if (current_weight != INT_MAX)
                    current_weight += current->length;
                if (current_weight < min_weight)
                    min_weight = current_weight;

                current = current->next;
            }
            A[i][n] = min(A[i-1][n], min_weight);
            if (A[i][n] < A[i-1][n])
                stop_early = 0;
        }
        if (stop_early) {
            printf("stopping early\n");
            printf("i: %d\n", i);
            break;
        }
        if (i == N) {
            // we are here, and stop_early did not kick in, -ve edge
            printf("NULL\n");
            exit (0);
        }
    }

    return i;
}

struct heap {
    int max_len;
    int length;
    void **ptr;
};

struct heap *heap_init(int len) {
    struct heap *heap = calloc(1, sizeof(struct heap));

    heap->max_len = len;
    heap->length = 0;
    heap->ptr = calloc(heap->max_len, sizeof(void *));
    return heap;
}

void heap_insert(void *node, struct heap *heap) {
    heap->ptr[heap->length] = node;
}

void *heap_extract_min(struct heap *heap) {

    return NULL;
}

void dijkstras(struct Node **nodes, int src, int **A, int N) {
    //init keys
    for (int i = 1; i <= N; i++) {
        nodes[i]->dijkstra_key = INT_MAX;
        nodes[i]->dijkstra_seen = 0;
    }
    nodes[src]->dijkstra_key = 0;

    struct heap *heap = heap_init(N);

    //insert all nodes into heap, src at min
    for (int i = 1; i <= N; i++) {
        heap_insert(nodes[i], heap);
    }
    //extract min
    struct Node *node;
    while ((node = heap_extract_min(heap))) {

    //go over all of its edges and update keys (delete node from the middle of heap &
    //reinsert it with new key)
    //
    }
    //get the distance of all nodes from source in A
    //
}

int main(int argc, char **argv) {
    int N = 0, M = 0;
    int min_length = INT_MAX;

    if (argc != 2) {
        printf("Provide file name\n");
        return (1);
    }
    char *filename = argv[1];;

    // FILE *fp = fopen("g1.txt", "r");
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("fopen");
        return (1);
    }
    struct Node **nodes = parse_file(fp, &N);

    // verify addEdge()
    // print_graph(nodes, N);
    int **A = calloc(N+1, sizeof(int *));
    for (int i = 0; i < N+1; i++) {
        A[i] = calloc(N+1, sizeof(int));
    }

    printf("calculating new weights\n");
    // add a dummy node in nodes at pos 0
    nodes[0] = newNode(0);
    nodes[0]->egress = NULL;
    int index = bellmanford(nodes, N, 0, A);

    for (int i = 1; i <= N; i++) {
        nodes[i]->bellman_weight = A[index][i];
        printf("%d| node %d new label for dijkstras %d\n", index, nodes[i]->label, nodes[i]->bellman_weight);
    }

    for (int i = 1; i <= N; i++) {
        struct EdgeList *current = nodes[i]->egress;
        while (current) {
            current->plength = current->length + nodes[i]->bellman_weight - current->node->bellman_weight;
            printf("Edge (%d, %d), length: %d, plength: %d\n", nodes[i]->label, current->node->label, current->length, current->plength);
            current = current->next;
        }
    }

    for (int i = 1; i <= N; i++) {
        dijkstras(nodes, i, A, N);
    }

    for (int i = 0; i <= N; i++) {
        free(nodes[i]);
        free(A[i]);
    }
    free (A);
    free(nodes);
    fclose(fp);
}
