#include "queue.h"

Queue* createQueue() {
  Queue* q = (Queue*)calloc(1,sizeof(Queue));
  q->head = NULL;
  q->size = 0;
  return q;
}

void enQueue(Queue* queue, int value) {
  Node* n = (Node*)calloc(1,sizeof(Node));
  n->value = value;
  n->next = NULL;
  Node* actual = queue->head;
  if (actual == NULL) {
    queue->head = n;
  }
  else {
    while (actual->next != NULL) {
      actual = actual->next;
    }
    actual->next = n;
  }
  queue->size ++;
}

void deQueue(Queue* queue, int* head) {
  int temp = queue->head->value;
  queue->head = queue->head->next;
  (*head) = temp;
  queue->size --;
}

void removeValue(Queue* queue, int value) {
  int removed;
  if (queue->head->value == value) {
    deQueue(queue, &removed);
  }
  else {
    Node* prev = queue->head;
    Node* actual = queue->head->next;
    while (actual!= NULL) {
      if (actual->value == value) {
        Node* temp = actual;
        prev->next = actual->next;
        free(temp);
      }
      prev = actual;
      actual = actual->next;
    }
    queue->size --;
  }
}

void freeQueue(Queue* queue) {

}
