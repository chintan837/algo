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

int main() {
	
}
