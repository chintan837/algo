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

typedef struct item item_t;
typedef struct itemlist list_t;

struct item {
	long value;
	long weight;
	item_t *array;
	int list_size;
};

struct itemlist {
	item_t *item;
	list_t *next;
};

typedef struct btree {
	item_t *item;
	struct btree *left;
	struct btree *right;
}btree_t;

static long 
max (long n1, long n2) {
	if (n1 > n2)
		return n1;
	else
		return n2;
}

static size_t count = 0;

static void
list_print(list_t *head) {
	while (head) {
		printf("\t%ld \n", head->item->weight);
		head = head->next;
	}
}

static size_t
list_count(list_t *head) {
	size_t count = 0;
	while (head) {
		count++;
		head = head->next;
	}
	return count;
}

static inline list_t *
create_list_item(long weight) {
	item_t *i = malloc(sizeof(item_t));
	i->value = 0;
	i->weight = weight;
	i->array = NULL;
	i->list_size = 0;

	list_t *l = malloc(sizeof(list_t));
	l->item = i;
	l->next = NULL;

	return l;
}

static int 
list_add(list_t **head, long weight) {
	if (weight <= 0)
		return 0;

	if (*head == NULL) {
		*head = create_list_item(weight);
		return 1;
	}
	list_t *current = *head;
	while (current) {
		if (current->item->weight == weight)
			return 0;
		if (current->next == NULL)
			break;
		current = current->next;
	}

	current->next = create_list_item(weight);
	return 1;
}


static btree_t *
btree_insert(btree_t *root, item_t *item) {
	if (root == NULL) {
		btree_t *treenode = malloc(sizeof (btree_t));
		treenode->item = item;
		treenode->left = NULL;
		treenode->right = NULL;

		return treenode;
	}

	if (item->weight < root->item->weight)
		root->left = btree_insert(root->left, item);
	else
		root->right = btree_insert(root->right, item);

	return NULL;
}

static int
btree_find(btree_t *root, long weight, long *val) {
	if (root == NULL)
		return 0;

	if (root->item->weight == weight) {
		*val = root->item->value;
		return 1;
	}
	if (root->item->weight < weight)
		return btree_find(root->left, weight, val);
	else
		return btree_find(root->right, weight, val);
}

int compar(const void *p1, const void *p2) {
	item_t *i1 = (item_t *)p1;
	item_t *i2 = (item_t *)p2;

	return (i1->weight - i2->weight);
}

static long
max_value(item_t *items, int n, int w, btree_t **calculated_items) {
	count++;
	if (n <= 0) {
		return 0;
	}
	if (w <= 0)
		return 0;

	// This is where you need some form of caching mechanism
	// if you have already seen this n and w pair, retrieve results
	// else calculate and cache results for future use
	btree_t *root = calculated_items[n];
	long val = 0;
	long val1 = 0;
	long val2 = 0;
	if (btree_find(root, w, &val))
		return val;
	item_t *newitem;

	// not included
	val1 = max_value(items, n-1, w, calculated_items);
	newitem = malloc(sizeof (item_t));
	newitem->weight = w;
	newitem->value = val1;
	root = btree_insert(root, newitem);

	//included
	long weight = w-(items+n)->weight;
	if (weight < 0)
		return val1;
	val2 = max_value(items, n-1, weight, calculated_items) + (items+n)->value;
	newitem = malloc(sizeof (item_t));
	newitem->weight = weight;
	newitem->value = val2;
	root = btree_insert(root, newitem);

	if (val1 > val2)
		return val1;
	else
		return val2;
}

int main(void) {
	int i = 0, j = 0;
	FILE *fp = fopen("knapsack_big.txt", "r");
	if (!fp)
		perror("fopen");
	int W = 0, N = 0;
	fscanf(fp, "%d %d\n", &W, &N);
	printf("knapsack_size: %d number_of_items: %d\n", W, N);
	item_t *items = calloc(N+1, sizeof(item_t));
	
	i = 1;
	while ((fscanf(fp, "%ld %ld\n", &(items+i)->value, &(items+i)->weight)) != EOF) {
		//	printf("v%d: %ld, w%d: %ld\n", i, (items+i)->value, i, (items+i)->weight);
		(items+i)->list_size = 0;
		(items+i)->array = NULL;
		i++;
	}

	qsort(items+1, N, sizeof(item_t), compar);
	//	for (i = 1; i <= N; i++)
	//		printf("v%d: %ld, w%d: %ld\n", i, (items+i)->value, i, (items+i)->weight);

	count = 0;
	item_t *item = items+N;
	item_t *prev = NULL;
	list_t *list = NULL;

	item->list_size += list_add(&list, W);
	item->list_size += list_add(&list, W-item->weight);
	for (i = N-1; i > 0; i--) {
		item = items+i;
		prev = items+i+1;
		// convert prev list to array
		prev->array = calloc(prev->list_size, sizeof(item_t));
		int index = 0;
		while (list) {
			list_t *del = list;
			prev->array[index].weight = list->item->weight;
			index++;
			list = list->next;
			free(del);
		}
		list = NULL;

		//scan over above array and add teh elems to a list

		item_t *array = prev->array;
		for (index = 0; index < prev->list_size; index++) {
			item->list_size += list_add(&list, array[index].weight);
			item->list_size += list_add(&list, array[index].weight - item->weight);
		}
		printf("Calculate for v%d: %ld, w%d: %ld, count: %d\n", i, item->value, i, item->weight, item->list_size);
	}

//	for (i = N; i > 0; i--) 
	//	printf("Calculate for v%d: %ld, w%d: %ld, count: %ld\n", i, (items+i)->value, i, (items+i)->weight, list_count((items+i)->list));

	free(items);
	fclose(fp);
	return 0;
}
