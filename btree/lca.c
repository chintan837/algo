#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};
struct Stack {
    struct TreeNode *n;
    struct Stack *next;
};

struct Stack *pushStack(struct Stack **s, struct TreeNode *n) {
    struct Stack *newNode = (struct Stack *) malloc(sizeof(struct Stack));

    newNode->n = n;
    newNode->next = *s;
	*s = newNode;

    return newNode;
}

struct TreeNode *popStack(struct Stack **s) {
    if (s == NULL)
        return NULL;
    struct Stack *node = *s;
    struct TreeNode *n = node->n;
    
    *s = (*s)->next;
    free(node);
    printf("popping %d from stack\n", n->val);
    return n;
}

int findNode(struct TreeNode *root, struct TreeNode *p, struct Stack **s) {
    if (root == NULL) {
        return 0;
    }
    if (root == p) {
        pushStack(s, root);
        return 1;
    }
    int foundLeft = findNode(root->left, p, s);
    int foundRight = findNode(root->right, p, s);
	
    if (foundLeft || foundRight) {
        pushStack(s, root);
        return 1;
    } else {
        return 0;
    }
}

struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {
    struct Stack *pStack = NULL, *qStack = NULL;
    struct TreeNode *ret = NULL;
    struct Stack *currentP = NULL;
    struct Stack *currentQ = NULL;
/*    
    // stack test;
    struct TreeNode n1, n2, n3;
    n1.val = 1;
    n2.val = 2;
    n3.val = 3;
    
    pStack = pushStack(pStack, &n1);
    pStack = pushStack(pStack, &n2);
    pStack = pushStack(pStack, &n3);
    
    current = pStack;
    while (current) {
        printf("%d ", current->n->val);
        current = current->next;
    }
    printf("\n");
    popStack(&pStack);
    current = pStack;
    while (current) {
        printf("%d ", current->n->val);
        current = current->next;
    }
    printf("\n");    
*/    
    if (!findNode(root, p, &pStack)) {
        printf("Node p %d not found\n", p->val);
        return NULL;
    }
    if (!findNode(root, q, &qStack)) {
        printf("Node q %d not found\n", q->val);
        return NULL;
    }
    

    currentP = pStack;
    currentQ = qStack;
    while (currentP && currentQ) {
		if (currentP->n->val == currentQ->n->val)
			ret = currentP->n;
        currentP = currentP->next;
        currentQ = currentQ->next;
    }
    
    // get LCA from stacks
    return ret;
}

struct TreeNode* newNode (int val) {
	struct TreeNode *newNode = malloc(sizeof(struct TreeNode));

	newNode->val = val;
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

int main() {

	struct TreeNode *root;
/*	
	// tc 1 [1 2 NULL]
	root = newNode(1);
	root->left = newNode(2);
*/

/*
	// tc 2
	root = newNode(3);
	root->left = newNode(5);
	root->right = newNode(1);
	root->left->left = newNode(6);
	root->left->right = newNode(2);
	root->right->left = newNode(0);
	root->right->right = newNode(8);
	root->left->right->left = newNode(7);
	root->left->right->right = newNode(4);
*/
	root = newNode(37);
	root->left = newNode(-34);
	root->right = newNode(-48);
	root->left->right = newNode(-100);
	root->right->left = newNode(-100);
	root->right->right = newNode(48);
	root->right->right->left = newNode(-54);
	root->right->right->left->left = newNode(-71);
	root->right->right->left->right = newNode(-22);
	root->right->right->left->right->right = newNode(8);

	struct TreeNode *ans;
	ans = lowestCommonAncestor(root, root->left->right, root->right->left);


	printf("lca: %d\n", ans->val);
}



