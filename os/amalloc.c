#include <stdio.h>
#include <stdlib.h>

void *amalloc(int size);  // Return integer aligned pointer
void afree(void *ptr);

void *amalloc(int size) {
	void *ptr = malloc(size + sizeof(int)*2);
  	printf("Got %p\n", ptr);
	
	int s = sizeof (int) - ((long) ptr & (sizeof(int) - 1));
	printf("offset: %d\n", s);

	ptr += s;
	*(int *) ptr = s;

	ptr += sizeof(int);

	return ptr;
}

void afree(void *ptr) {
	ptr -= sizeof(int);
	int s = *(int *)ptr;

	printf("offset: %d\n", s);
  	ptr -= s;

	printf("Freeing %p\n", ptr);
	free(ptr);
}

int main(void) {
	void *ptr = amalloc(3);
  
  	afree(ptr);
}
