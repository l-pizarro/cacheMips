#pragma once
#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
  int value;
  struct Node * next;
} Node;

typedef struct Queue {
  Node *head;
  Node *tail;
  int size;
} Queue;

Queue* createQueue();
void enQueue(Queue* queue, int value);
void deQueue(Queue* queue, int* head);
void removeValue(Queue* queue, int value);
void freeQueue(Queue* queue);
