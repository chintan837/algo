#include <stdio.h>
#include <stdlib.h>

struct node {
	int val;
	float prob;
};

struct node nodes[] = 	{
							{1, 0.2},
							{2, 0.05},
							{3, 0.17},
							{4, 0.1},
							{5, 0.2},
							{6, 0.03},
							{7, 0.25},
							//	{1, 0.05},
							//	{2, 0.4},
							//	{3, 0.08},
							//	{4, 0.04},
							//	{5, 0.1},
							//	{6, 0.1},
							//	{7, 0.23},
						};

int main(void) {
	float A[7][7];
	for (int j = 0; j < 7; j++) {
		for (int k = 0; k < 7; k++) {
			A[j][k] = 0;
		}
	}

	for (int S = 0; S <= 0; S++) {
		for (int i = 0; i < 7; i++) {
			A[i][i+S] = nodes[i].prob;
		}
	}
	for (int S = 1; S < 7; S++) {
		for (int i = 0; i < 7-S; i++) {
			float a = 0;
			float min = 0;
			float tmp = 0;
			int r = 0;
			for (r = i; r <= i+S; r++) {
				a += nodes[r].prob;
			}
			min = a + A[i+1][i+S];
			for (r = i+1; r < i+S; r++) {
				tmp = a + A[i][r-1] + A[r+1][i+S];
				if (tmp < min)
					min = tmp;
			}
			tmp = a + A[i][r-1];
			if (tmp < min)
				min = tmp;

			printf("S: %d i: %d min: %.2f\t", S, i, min);
			A[i][i+S] = min;
		}
		printf("\n");
	}

	return 0;
}
