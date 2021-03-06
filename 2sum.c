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
#include <assert.h>

#define P1 -10000
#define P2	10000

#define T11 3
#define T12 10

#define T21 0
#define T22 4

struct bst {
	long int data;
	struct bst *left;
	struct bst *right;
};

int bst_height(struct bst *root) {
	int ret = 0;
	if (root == NULL)
		return ret;

	int lheight = bst_height(root->left);
	int rheight = bst_height(root->right);

	(lheight > rheight)? (ret = lheight): (ret = rheight);
	return ret+1;
}

struct bst *bst_insert(long int data, struct bst *root) {
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

int bst_search(long int data, struct bst *root) {
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

static int compare(const void *p1, const void *p2)
{
	long int left = *(const	long int *)p1;
	long int right = *(const long int *)p2;

	return ((left > right) - (left < right));
}

int b_search(long int target, long int* array, int l, int r) {
	if (l > r)
		return 0;

	int m = l + (r-l)/2;
	//	printf("Finding %ld in range [%d, %d, %d]\n", target, l, m, r);
	if (l == r) {
		if (target == array[l]) 
			return 1;
		else {
			return 0;
		}
	}

	if (target < array[m]) {
		//	printf("%ld < %ld[%d], going left\n", target, array[m], m);
		return b_search(target, array, l, m-1);
	}
	else if (target > array[m]) {
		//	printf("%ld > %ld[%d], going right\n", target, array[m], m);
		return b_search(target, array, m+1, r); 
	} else {
		return 1;
	}
}

int main(int argc, char *argv[]) {
	for (int i = 0; i < argc; i++)
		printf("%s ", argv[i]);

	FILE *fp;
	char *line = NULL;
	size_t read = 0;
	ssize_t len = -1;
	long int num = 0;
	long int array[1000000];
	int count = 0;
	int N = 0;
	struct bst *btree = NULL;
	fp = fopen("algo1-programming_prob-2sum.txt", "r");
	// fclose(fp);
	// fp = fopen("2sum_2.test", "r");

	while((len = getline(&line, &read, fp)) != -1) {
		sscanf(line, "%ld\n", &num);
		array[N] = num;
		btree = bst_insert(num, btree);
		N++;
	}

	printf("\n# of objects n: %d\n", N);
	int height = bst_height(btree);
	printf("Height of the btree: %d\n", height);

#if 0	
	/* sanity of search data structrue */
	qsort(array, N, sizeof(long int), compare);
	printf("sorting complete\n");
	for (int i = 0; i < N; i++) {
		asser(b_search(array[i], array, 0, N-1));
	}
#endif 
	for (int i = 0; i < N; i++) {
		assert(bst_search(array[i], btree));
	}
	printf("sanity complete\n");
#if 0
	while ((scanf("%ld", &num) == 1)) {
		printf("Enter number to search (any other key to quit): ");
		if (b_search(num, array, 0, N-1))
			printf("%ld found\n", num);
		else
			printf("%ld not found\n", num);
	}
#endif

	count = 0;
	long int x, y;
	for (int t = P1; t <= P2; t++) {
		for (int i = 0; i < N; i++) {
			x = array[i];
			y = t - x;
			if (x == y) {
				//	printf("x: %ld, y: %ld, continuing\n", x, y);
				continue;
			}
			if (bst_search(y, btree)) {
			//	if (b_search(y, array, 0, N-1)) {
				printf("Found sum t: %d with x: %ld and y:%ld\n", t, x, y);
				count++;
				break;
			} else {
				//	printf("did not find y: %ld for x: %ld and t:%d\n", y, x, t);
			}
		}
	}
	printf("Number of unique t's: %d\n", count);

	bst_destroy(btree);
	free(line);
	fclose (fp);
	return 0;
}
