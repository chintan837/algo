#include <stdio.h>
#include <stdlib.h>

struct alphabet {
	int seen;
	int index;
	int length;
};

struct alphabet *a;
struct alphabet l;

int getCurrentLongest(char *s, int index, int len) {
	if (s[index] == '\0') {
		return 0;
	}
	
	int curr = s[index] - 'a';
	
	if (a[curr].seen == 0) {
		a[curr].seen = 1;
		return getCurrentLongest(s, index+1, len+1);
	}
	if (a[curr].seen == 1) {
		return len;
	}

	return 0;
}

int lengthOfLongestSubstring(char* s) {
	int len = 0;

	int index = 0;
	while ((len = getCurrentLongest(s, index, 0)) != 0) {
		if (len > l.length) {
			l.length = len;
			l.index = index;
		}
		for (int i = index; i <= len; i++)
			printf("%c", s[i]);
		printf("\n");
		index += len;
	}

	return len;
}

int main() {
	char *s = "abcabcbb";
	a = calloc(26, sizeof (struct alphabet));
	l.index = 0;
	l.length = 0;

	printf("leng of longest substring: %d\n", lengthOfLongestSubstring(s));

	free(a);
	return 0;
}
