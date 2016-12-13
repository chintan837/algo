/*
 The compiler scans the expression either from left to right or from right to left.
 Consider the below expression: a op1 b op2 c op3 d
 If op1 = +, op2 = *, op3 = +
 The compiler first scans the expression to evaluate the expression b * c, 
 then again scan the expression to add a to it. The result is then added to d after another scan.
 The repeated scanning makes it very in-efficient. 
 It is better to convert the expression to postfix(or prefix) form before evaluation.
 The corresponding expression in postfix form is: abc*d++. 
 The postfix expressions can be evaluated easily using a stack. 
 We will cover postfix expression evaluation in a separate post.

eg: a+b*(c^d-e)^(f+g*h)-i
output: abcd^e-fgh*+^*+i-
*/

#include <stdio.h>
#include <stdlib.h>

struct Stack {
	int top;
	unsigned int size;
	char *arr;
};

struct Stack *CreateStack(int len, int size) {
	struct Stack *stack = (struct Stack *)malloc(sizeof (struct Stack));

	stack->top = -1;
	stack->size = len;
	stack->arr = calloc(len, size);

	return stack;
}

int push(struct Stack *s, char ch) {
	if (s->top >= (int)s->size) {
		printf("Stack full top: %d size: %u\n", s->top, s->size);
		return -1;
	}
	s->top++;
	s->arr[s->top] = ch;
	return 0;
}

int isEmpty(struct Stack *s) {
	return (s->top < 0) ? 1:0;
}

char pop(struct Stack *s) {
	char ch;
	if (isEmpty(s)) {
		return 0;
	}
	
	ch = s->arr[s->top];
	s->top--;
	return ch;
}

char peek(struct Stack *s) {
	char ch;
	if (isEmpty(s))
		return 0;
	else 
		return s->arr[s->top];
}

int isOperand(char ch) {
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return 1;
	return 0;
}

/* check if operator and return precedence */
int isOperator(char ch) {
	switch (ch) {
		case '+':
		case '-':
			return 1;
			break;
		case '*':
		case '/':
			return 2;
			break;
		case '^':
			return 3;
			break;
		case '(':
		case ')':
			return 4;
			break;
		default:
			return -1;
	}
}

int main() {
	struct Stack *s = CreateStack(100, sizeof(char));

	char *ip = "a+b*(c^d-e)^(f+g*h)-i";
	int i = 0;
	int p = 0;
	char ch;

	/*
	  //unit test stack 
	push(s, 'a');
	push(s, 'b');
	push(s, 'c');
	push(s, 'd');

	while (!isEmpty(s)) {
		printf("%c", pop(s));
	} printf("\n");
	*/
	while (ip[i] != '\0') {
		if (isOperand(ip[i])) {
			printf("%c", ip[i]);
		} else if((p = isOperator(ip[i])) != -1) {
			if (isEmpty(s) || ip[i] == '(')
				push(s, ip[i]);
			else {
				if (ip[i] == ')') {
					while ((ch = pop(s)) != '(')
						printf("%c", ch);
				} else {
					while (p <= isOperator(peek(s))) {
						printf("%c", pop(s));
					}
					push(s, ip[i]);
				}
			}
		} else {
			printf("\nSomething went wrong\n");
		}
		i++;
	} printf("\n");
}
