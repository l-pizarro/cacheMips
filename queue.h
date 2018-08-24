#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "node.h"

// Queue Structure

typedef struct Queue {
  Node *head;
  Node *tail;
  int size;
} Queue;

Queue* createQueue();
void enQueue(Queue* queue, int value);
void deQueue(Queue* queue, int* head);
void removeFromQueue(Queue* queue, int value);
void enQueueExclusive(Queue* queue, int value);
void freeQueue(Queue* queue);
