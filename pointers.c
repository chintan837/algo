#include <stdio.h>
#include <stdlib.h>

struct list {
	int value;
	struct list *next;
};

static inline void
swapp(struct list **p1, struct list **p2) {
	struct list *tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;

	return;
}

int main(void) {

	printf("sizeof(int): %lu\n", sizeof(int));
	printf("sizeof(struct list): %lu\n", sizeof(struct list));
	printf("sizeof(struct list *): %lu\n", sizeof(struct list *));
	printf("sizeof(struct list **): %lu\n", sizeof(struct list **));

	struct list array[8];
	struct list *arrayp[8];
	for (int i = 0; i < 8; i++) {
		array[i].value = i;
		array[i].next = NULL;
		arrayp[i] = &array[i];
		printf("array[%d]: Value: %d Addres: %p\n", i, array[i].value, arrayp[i]);
	}

	swapp(&arrayp[2], &arrayp[3]);

	for (int i = 0; i < 8; i++) {
		array[i].value = i;
		array[i].next = NULL;
		printf("array[%d]: Value: %d Addres: %p Value at Pointer: %d\n", i, array[i].value, &array[i], arrayp[i]->value);
	}

	return 0;
}
