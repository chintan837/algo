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

struct bst *_bst_insert(struct bst *data, struct bst *root) {
	if (root == NULL)
		return data;

	if (root->data > data->data) {
		root->left = _bst_insert(data, root->left);
		return root->left;
	}
	else {
		root->right = _bst_insert(data, root->right);
		return root->right;
	}
}

struct bst *bst_insert(int data, struct bst *root) {
	struct bst *newnode = malloc(sizeof(struct bst));

	newnode->data = data;
	newnode->left = NULL;
	newnode->right = NULL;

	return _bst_insert(newnode, root);
}

int bst_search(int data) {
	
	return 0;
}

int main(int argc, char *argv[]) {
	for (int i = 0; i < argc; i++)
		printf("%s ", argv[i]);

	FILE *fp;
	char *line;
	size_t read;
	ssize_t len;
	int num = 0;
	int count = 0;
	struct bst *btree = NULL;
	fp = fopen("algo1-programming_prob-2sum.txt", "r");

	while((len = getline(&line, &read, fp)) != -1) {
		sscanf(line, "%d\n", &num);
		btree = bst_insert(num, btree);
		count++;
	}

	printf("\n# of objects n: %d\n", count);

	fclose (fp);
	return 0;
}
