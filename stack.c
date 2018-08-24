#include "stack.h"

// Stack implementation

Stack* createStack() {
  Stack* s = (Stack*)calloc(1,sizeof(Stack));
  s->head = NULL;
  s->size = 0;
  return s;
}

void push(Stack* stack, int value) {
  Node* n = (Node*)calloc(1,sizeof(Node));
  n->value = value;
  n->next = stack->head;
  stack->head = n;
  stack->size ++;
}

void pop(Stack* stack, int* head) {
  (*head) = stack->head->value;
  stack->head = stack->head->next;
  stack->size --;
}

void removeFromStack(Stack* stack, int value) {
  int removed;
  if (stack->head->value == value) {
    pop(stack, &removed);
  }
  else {
    Node* prev = stack->head;
    Node* actual = stack->head->next;
    while (actual!= NULL) {
      if (actual->value == value) {
        Node* temp = actual;
        prev->next = actual->next;
        free(temp);
      }
      prev = actual;
      actual = actual->next;
    }
    stack->size --;
  }
}

void pushExclusive(Stack* stack, int value) {
  Node* actual = stack->head;
  while (actual != NULL) {
    if (actual->value == value) {
      removeFromStack(stack, value);
      break;
    }
    actual = actual->next;
  }
  push(stack, value);
}

void freeStack(Stack* stack) {
  if (stack->head!= NULL) {
    Node* temp = stack->head;
    stack->head = stack->head->next;
    free(temp);
    return freeStack(stack);
  }
}
