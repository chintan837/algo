#include <stdio.h>
#include <stdlib.h>

int main () {

	char *keys[] = {
					"abc",
					"def",
					"ghi",
					"jkl",
					"mno",
					"pqrs",
					"tuv",
					"wxyz"
					"+",
					".",
				};

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			printf("%c(%p) ", keys[i][j], &keys[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	int m = 1024;
	int n = 3;

	int data[m][n];

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			printf("%p ", &data[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 3; i++) {
			printf("%p ", &data[i][j]);
		}
		printf("\n");
	}
}
