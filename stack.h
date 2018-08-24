#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "node.h"

// Stack structure

typedef struct Stack {
  Node *head;
  int size;
} Stack;

Stack* createStack();
void push(Stack* stack, int value);
void pop(Stack* stack, int* head);
void removeFromStack(Stack* stack, int value);
void pushExclusive(Stack* stack, int value);
void freeStack(Stack* stack);
