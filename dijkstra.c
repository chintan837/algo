#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
		printf("%d\n", s);
		while (token = strtok(NULL, ",")){
			//	t = atoi(token);
			printf("\t%s", token);
			token = strtok(NULL, "\t\n");
			//	len = atoi(token);
			printf(" (%s)\n", token);
		}
	}

	fclose(fp);
	free(line);
}
