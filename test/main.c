#include "queue.h"

int main(int argc, char const *argv[]) {
  Queue* q = createQueue();
  printf("Empty queue:\n");
  printf("  head: %p\n", q->head);
  printf("  tail: %p\n", q->tail);
  printf("\n");
  printf("Adding 3, 4 ,5\n");
  enQueue(q, 3);
  enQueue(q, 4);
  enQueue(q, 5);
  enQueue(q, 6);
  printf("\nsize: %d\n",q->size);
  removeValue(q, 6);
  removeValue(q, 4);
  printf("Items:\n");
  int head;
  while (q->head != NULL) {
    printf("%d\n", q->head->value);
    deQueue(q, &head);
  }
  return 0;
}
