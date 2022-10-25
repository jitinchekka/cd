// Author: Jitin (CS20B1075)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
// Implement stack using array
struct stack
{
	int top;
	int capacity;
	char *array;
};
struct stack *createStack(int capacity)
{
	struct stack *s = (struct stack *)malloc(sizeof(struct stack));
	s->capacity = capacity;
	s->top = -1;
	s->array = (char *)malloc(s->capacity * sizeof(char));
	return s;
}
int isFull(struct stack *s)
{
	return s->top == s->capacity - 1;
}
int isEmpty(struct stack *s)
{
	return s->top == -1;
}
void push(struct stack *s, int item)
{
	if (isFull(s))
		return;
	s->array[++s->top] = item;
}
char pop(struct stack *s)
{
	if (isEmpty(s))
		return 0;
	return s->array[s->top--];
}
char peek(struct stack *s)
{
	if (isEmpty(s))
		return 0;
	return s->array[s->top];
}
void display(struct stack *s)
{
	int i;
	if (isEmpty(s))
	{
		printf("Stack is empty\n");
		return;
	}
	for (i = s->top; i >= 0; i--)
		printf("%c ", s->array[i]);
	printf("\n");
}
// End of stack implementation

// Convert infix to prefix
int precedence(char ch)
{
	if (ch == '+' || ch == '-')
		return 1;
	if (ch == '*' || ch == '/')
		return 2;
	return 0;
}
int isOperator(char ch)
{
	return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}
int isOperand(char ch)
{
	return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}
// int isalnum(char ch)
// {
// 	return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9');
// }

void infixToPrefix(char *infix, int n)
{
	char prefix[n];
	int ptr = 0;
	struct stack *s = createStack(strlen(infix));
	int i = 0;
	while (infix[i] != '\0')
	{
		if (infix[i] == '(')
			push(s, infix[i]);
		else if (infix[i] == ')')
		{
			while (peek(s) != '(')
				prefix[ptr++] = pop(s);
			// printf("%c", pop(s));
			pop(s);
		}
		else if (isalnum(infix[i]))
			prefix[ptr++] = infix[i];
		// printf("%c", infix[i]);
		else
		{
			while (!isEmpty(s) && precedence(infix[i]) <= precedence(peek(s)))
				// printf("%c", pop(s));
				prefix[ptr++] = pop(s);
			push(s, infix[i]);
		}
		i++;
	}
	while (!isEmpty(s))
		prefix[ptr++] = pop(s);
	printf("Prefix expression: ");
	for (i = n - 1; i >= 0; i--)
		printf("%c", prefix[i]);
	printf("\n");
}

void main()
{
	char infix[100];
	printf("Enter infix expression: ");
	scanf("%s", infix);
	// reverse the string and change ( to ) and vice versa
	int i = 0, j = strlen(infix) - 1;
	while (i < j)
	{
		char temp = infix[i];
		if (infix[i] == '(')
			infix[i] = ')';
		else if (infix[i] == ')')
			infix[i] = '(';
		infix[i] = infix[j];
		infix[j] = temp;
		i++;
		j--;
	}
	// printf("\nPrefix expression: ");
	infixToPrefix(infix, strlen(infix));
}