#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *next;
};

void printlist(struct node *head) {
	while (head) {
		printf("%d ", head->data);
		head = head->next;
	}
	printf("\n");
}

struct node *append(struct node *head, int data) {
	struct node *current;
	struct node *newnode = calloc(1, sizeof(struct node));
	newnode->data = data;
	newnode->next = NULL;

	if (head == NULL) {
		return newnode;
	}

	current = head;

	while(current->next)
		current = current->next;

	current->next = newnode;

	return head;
}

struct node *MergeLists1(struct node *headA, struct node *headB) {
    struct node *current, *head;
    struct node *currentA, *currentB;
    
    if (headA == NULL) {
        return headB;
    } else if (headB == NULL) {
        return headA;
    }
    
    if (headA->data > headB->data) {
        current = headB;
        headB = headB->next;
    } else {
        current = headA;
        headA = headA->next;
    }
    head = current;
    
    while (1) {
        if (headA == NULL) {
            current->next = headB;
            break;
        }
        if (headB == NULL) {
            current->next = headA;
            break;
        }
        if (headA->data > headB->data) {
            current->next = headB;
            headB = headB->next;
            current = current->next;
        } else {
            current->next = headA;
            headA = headA->next;
            current = current->next;
        }
    }
    
    return head;
}


struct node *MergeLists(struct node *headA, struct node *headB) {
	if (headA == NULL) {
		return headB;
	}
	if (headB == NULL) {
		return headA;
	}

	if (headA->data < headB->data) {
		headA->next = MergeLists(headA->next, headB);
		return headA;
	}
	else {
		headB->next = MergeLists(headA, headB->next);
		return headB;
	}
}

int main() {
	struct node *headA = NULL;
	struct node *headB = NULL;

	printf("linked list header\n");

	headA = append(headA, 3);
	headA = append(headA, 5);
	headA = append(headA, 8);
	headA = append(headA, 12);

	headB = append(headB, 1);
	headB = append(headB, 2);
	headB = append(headB, 6);

	//struct node *head = MergeLists1(headA, headB);
	struct node *head = MergeLists(headA, headB);
	printlist(head);

	return 0;
}
