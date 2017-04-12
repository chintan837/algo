#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
	int value;
	struct edgelist;
}

struct edgelist {
	struct node *node;
	int len;
}

addedge(int s, int t, int len) {

}

int main(int argc, char *argv[]) {
	for (int i = 0; i < argc; i++) {
		printf("%s\n", argv[i]);
	}

	FILE *fp = fopen("dijkstraData.txt","r");
	char *line;
	size_t len = 0;
	ssize_t read;
	char *ptr;
	char *token;
	int s = 0, t = 0;

	while ((read = getline(&line, &len, fp)) != -1) {
		token = strtok(line, "\t");
		s = atoi(token);
		int flag = 1;
		while (token = strtok(NULL, ",\t\n")){
			if (flag) {
				t = atoi(token);
				flag = 0;
			} else {
				len = atoi(token);
				flag = 1;
				addedge(s, t, len);
			}
		}
	}



	fclose(fp);
	free(line);
}
