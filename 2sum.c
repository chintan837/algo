/*
 * The goal of this problem is to implement a variant of the 
 * 2-SUM algorithm covered in this week's lectures.
 *
 * The file contains 1 million integers, both positive and negative 
 * (there might be some repetitions!).This is your array of integers, 
 * with the ith row of the file specifying the ith entry of the array.
 *
 * Your task is to compute the number of target values t in the interval 
 * [-10000,10000] (inclusive) such that there are distinct numbers x,y 
 * in the input file that satisfy x+y=t. (NOTE: ensuring distinctness 
 * requires a one-line addition to the algorithm from lecture.)
 *
 * Write your numeric answer (an integer between 0 and 20001) in the space provided.
 *
 * OPTIONAL CHALLENGE: If this problem is too easy for you, try implementing 
 * your own hash table for it. For example, you could compare performance 
 * under the chaining and open addressing approaches to resolving collisions.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct bst {
	int data;
	struct bst *left;
	struct bst *right;
};

struct bst *bst_insert(int data, struct bst *root) {
	if (root == NULL) {
		struct bst *newnode = malloc(sizeof(struct bst));

		newnode->data = data;
		newnode->left = NULL;
		newnode->right = NULL;
		return newnode;
	}

	if (data < root->data)
		root->left = bst_insert(data, root->left);
	else
		root->right = bst_insert(data, root->right);
	
	return root;
}

int bst_search(int data, struct bst *root) {
	if (root == NULL)
		return 0;

	if (data == root->data)
		return 1;

	if (data < root->data) {
		return bst_search(data, root->left);
	}
	else
		return bst_search(data, root->right);
}

void bst_destroy(struct bst *root) {
	if (root == NULL)
		return;

	if (root->left)
		bst_destroy(root->left);
	if (root->right)
		bst_destroy(root->right);

	free(root);
}

int main(int argc, char *argv[]) {
	for (int i = 0; i < argc; i++)
		printf("%s ", argv[i]);

	FILE *fp;
	char *line;
	size_t read;
	ssize_t len;
	long int num = 0;
	int count = 0;
	struct bst *btree = NULL;
	fp = fopen("algo1-programming_prob-2sum.txt", "r");

	while((len = getline(&line, &read, fp)) != -1) {
		sscanf(line, "%ld\n", &num);
		btree = bst_insert(num, btree);
		count++;
	}

	printf("\n# of objects n: %d\n", count);

	while ((scanf("%ld", &num) == 1)) {
		printf("Enter number to search: (any other key to quit)");
		if (bst_search(num, btree))
			printf("%ld found\n", num);
		else
			printf("%ld not found\n", num);
	}

	bst_destroy(btree);
	fclose (fp);
	return 0;
}
