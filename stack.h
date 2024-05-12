#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include"global.h"

void PairInit(Pair *p)
{
	p->x=-1;
	p->y=-1;
}

void StackInit(Stack *s)
{
	s->top = -1;
	//doesnt matter
	PairInit(&s->List[0]);
}

int isFull(Stack *s)
{
	if (s->top == MAX_SIZE - 1)
		return 1;
	else
		return 0;
}

int isEmpty(Stack *s)
{
	if (s->top == -1)
		return 1;
	else
		return 0;
}

void push(Stack *s, int x, int y)
{
	if (isFull(s))
	{
		printf("Stack overflow\n");
		return;
	}
	s->top++;
	s->List[s->top].x = x;
	s->List[s->top].y = y;
}

void pop(Stack *s)
{
	if (isEmpty(s))
	{
		printf("Stack underflow\n");
		return;
	}
	s->top--;
}

Pair front(Stack *s)
{
	if (isEmpty(s))
	{
		printf("Stack is empty\n");
		exit(EXIT_FAILURE);
	}
	return s->List[s->top]; // Return the top element of the stack
}

void clear(Stack *s)
{
	s->top = -1; // Reset the top index to indicate an empty stack
}

#endif