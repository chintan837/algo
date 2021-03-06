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

typedef struct item {
	long value;
	long weight;
}item_t;

static long 
max (long n1, long n2) {
	if (n1 > n2)
		return n1;
	else
		return n2;
}

int main(void) {
	FILE *fp = fopen("knapsack1.txt", "r");
	if (!fp)
		perror("fopen");
	int W = 0, N = 0;
	fscanf(fp, "%d %d\n", &W, &N);
	printf("knapsack_size: %d number_of_items: %d\n", W, N);
	item_t *items = calloc(N+1, sizeof(item_t));
	int i = 0, j = 0;

	i = 1;
	while ((fscanf(fp, "%ld %ld\n", &(items+i)->value, &(items+i)->weight)) != EOF) {
		printf("v%d: %ld, w%d: %ld\n", i, (items+i)->value, i, (items+i)->weight);
		i++;
	}

	long **A = (long **)calloc(N, sizeof (long *));
	for (i = 0; i < N+1; i++)
		A[i] = calloc(W+1, sizeof (long));

	for (j = 0; j <= W; j++)
		A[0][j] = 0;

	for (i = 1; i <= N; i++)
		for (j = 0; j <= W; j++) {
		 	long index = j - ((items+i)->weight);
			if (index < 0) {
				A[i][j] = A[i-1][j];
			} else { 
				A[i][j] = max(A[i-1][j], A[i-1][index]+(items+i)->value);
			}
		}

	printf("value of knapsack: %ld\n", A[N][W]);

	for (i = 0; i < N; i++)
		free(A[i]);
	free(A);
	free(items);
	fclose(fp);
	return 0;
}
