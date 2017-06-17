/*
PROBLEM 1:
In this programming problem and the next you'll code up the knapsack algorithm from lecture.

Let's start with a warm-up. Download the text file below.

This file describes a knapsack instance, and it has the following format:

[knapsack_size][number_of_items]

[value_1] [weight_1]

[value_2] [weight_2]

...

For example, the third line of the file is "50074 659", indicating that the second item has 
value 50074 and size 659, respectively.

You can assume that all numbers are positive. You should assume that item weights and the 
knapsack capacity are integers.

In the box below, type in the value of the optimal solution.

ADVICE: If you're not getting the correct answer, try debugging your algorithm using some 
small test cases. And then post them to the discussion forum!

PROBLEM 2:
This problem also asks you to solve a knapsack instance, but a much bigger one.

Download the text file below.

This file describes a knapsack instance, and it has the following format:

[knapsack_size][number_of_items]

[value_1] [weight_1]

[value_2] [weight_2]

...

For example, the third line of the file is "50074 834558", indicating that the second item 
has value 50074 and size 834558, respectively. As before, you should assume that item weights 
and the knapsack capacity are integers.

This instance is so big that the straightforward iterative implemetation uses an infeasible 
amount of time and space. So you will have to be creative to compute an optimal solution. 
One idea is to go back to a recursive implementation, solving subproblems --- and, of course, 
caching the results to avoid redundant work --- only on an "as needed" basis. Also, be sure 
to think about appropriate data structures for storing and looking up solutions to subproblems.

In the box below, type in the value of the optimal solution.

ADVICE: If you're not getting the correct answer, try debugging your algorithm using some 
small test cases. And then post them to the discussion forum!
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct item item_t;
typedef struct itemlist list_t;

struct item {
	long value;
	long weight;
	size_t sub_problem_size;
};

struct itemlist {
	item_t *item;
	list_t *next;
};

typedef struct btree {
	long weight;
	size_t index;
	struct btree *left;
	struct btree *right;
}btree_t;

static long 
max(long n1, long n2) {
	if (n1 > n2)
		return n1;
	else
		return n2;
}

static int
btree_find(btree_t *root, long weight) {
	if (root == NULL)
		return -1;

	if (root->weight == weight)
		return root->index;

	if (weight < root->weight)
		return btree_find(root->left, weight);
	else
		return btree_find(root->right, weight);
}

static void
btree_print_inorder(btree_t *root) {
	if (root == NULL)
		return;
	btree_print_inorder(root->left);
	printf("%ld[%ld] ", root->weight, root->index);
	btree_print_inorder(root->right);
}

static int
btree_insert(btree_t **root, long weight, size_t index) {
	if (*root == NULL) {
		btree_t *treenode = malloc(sizeof (btree_t));
		treenode->weight = weight;
		treenode->index = index;
		treenode->left = NULL;
		treenode->right = NULL;

		*root = treenode;

		printf("\tAdded %ld, index %zu\n", weight, index);
		return 1;
	}

	btree_t *current = *root;

	if (current->weight == weight)
		return 0;

	if (weight < current->weight)
		return btree_insert(&(current->left), weight, index);
	else
		return btree_insert(&(current->right), weight, index);
}

int compar(const void *p1, const void *p2) {
	item_t *i1 = (item_t *)p1;
	item_t *i2 = (item_t *)p2;

	return (i1->weight - i2->weight);
}

int main(void) {
	int i = 0, j = 0;
	FILE *fp = fopen("knapsack2.txt", "r");
	if (!fp)
		perror("fopen");
	int W = 0, N = 0;
	fscanf(fp, "%d %d\n", &W, &N);
	printf("knapsack_size: %d number_of_items: %d\n", W, N);
	item_t *items = calloc(N+1, sizeof(item_t));
	size_t max_weights = N;
	long *weights = calloc(max_weights, sizeof(long));
	size_t num_weights;
	btree_t *weights_tree = NULL;

	i = 1;
	while ((fscanf(fp, "%ld %ld\n", &(items+i)->value, &(items+i)->weight)) != EOF) {
		i++;
	}

	qsort(items+1, N, sizeof(item_t), compar);
	//	N = 3;
	//	W = 30;
	printf("W: %d\n", W);
	for (i = 1; i <= N; i++)
		printf("v%d: %ld, w%d: %ld\n", i, (items+i)->value, i, (items+i)->weight);

	item_t *item = items+N;
	item_t *prev = NULL;

	num_weights = 0;
	if (btree_insert(&weights_tree, W, num_weights)) {
		weights[num_weights] = W;
		num_weights++;	
	}
	
	long weight = 0;
	for (i = N; i > 1; i--) {
		item = items+i;
		item->sub_problem_size = num_weights;
		printf("Calculated for v%d: %ld, w%d: %ld, sub_problem_size: %zu\n", 
			i, item->value, i, item->weight, item->sub_problem_size);
		for (int j = 0; j < item->sub_problem_size; j++) {
			printf("(%ld - %ld = %ld)", weights[j], item->weight, weights[j]-item->weight);
		}
		printf("\n");
		for (int j = 0; j < item->sub_problem_size; j++) {
			weight = weights[j]-item->weight;
			if (weight <= 0)
				continue;
			printf("calculated: %ld\n", weight);
			if (btree_insert(&weights_tree, weight, num_weights)) {
				weights[num_weights] = weight;
				//	printf("\tAdded %ld, index %d\n", weight, item->sub_problem_size);
				num_weights++;
				if (num_weights >= max_weights) {
					max_weights *= 2;
					weights = realloc(weights, max_weights * sizeof(long));
				}
			}
		}
	}
	// i is 1, the last element to be considered, for num_weights problems
	item = items+i;
	item->sub_problem_size = num_weights;
	printf("Calculate for v%d: %ld, w%d: %ld, sub_problem_size: %zu\n", i, item->value, i, item->weight, item->sub_problem_size);
	
	item_t *prev_problem = calloc(num_weights, sizeof(item_t));
	printf("item %d: sub_problem_size: %zu\n", 1, item->sub_problem_size);
	
	for (int j = 0; j < item->sub_problem_size; j++) {
		prev_problem[j].weight = weights[j]; 
		if (weights[j] < item->weight)
			prev_problem[j].value = 0;
		else
			prev_problem[j].value = item->value;
	}

#if 0
	btree_print_inorder(weights_tree);
	printf("\n");
	for (i = 1; i <= N; i++) {
		item = items+i;
		printf("item %d: sub_problem_size: %d\n", i, (items+i)->sub_problem_size);
		for (int j = 0; j < item->sub_problem_size; j++) {
			printf("%ld[%d] ", weights[j], j);
		}
		printf("\n\n");
	}
#endif
	// initialize value of n1 with 0 if weight < w1 else v1
	for (i = 2; i <= N; i++) {
		printf("item %d: sub_problem_size: %zu\n", i, (items+i)->sub_problem_size);
		item = items+i;
		item_t *sub_problem = calloc(item->sub_problem_size, sizeof(item_t));
		for (int j = 0; j < item->sub_problem_size; j++) {
			sub_problem[j].weight = weights[j];
			
			long val1 = prev_problem[j].value;
			long val2;
			if (weights[j] <= item->weight)
				sub_problem[j].value = val1;
			else {
				int index = btree_find(weights_tree, weights[j]-item->weight);
				if (index < 0) {
					printf("Alert: This should never happen\n");
					printf("Could not find weight %ld[%d]-%ld(%ld)=%ld\n", weights[j], j, item->weight, item->value, weights[j]-item->weight);
					sub_problem[j].value = val1;
				} else {
					val2 = prev_problem[index].value + item->value;
					sub_problem[j].value = max(val1, val2);
				}
			}
		}

		free(prev_problem);
		prev_problem = sub_problem;
	}

	printf("sub_prob_size: %zu\n", item->sub_problem_size);
	printf("Answer: %ld\n", prev_problem[0].value);

#if 0
	for (i = 0; i < num_weights; i++) {
		printf("%8ld ", weights[i]);
		if ((i+1)%9 == 0)
			printf("\n");
	}
#endif
	free(prev_problem);
	free(weights);
	free(items);
	fclose(fp);
	return 0;
}
