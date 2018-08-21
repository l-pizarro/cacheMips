#include "functions.h"
#include "queue.h"
#include "stack.h"

int searchFor(int address, int** cache, int blocks, int associativity) {
  int location;
  int set;
  if (associativity == 1) {
    location =((address/8)%blocks);
    if (cache[location][0] != -1) {
      if (cache[location][0]/8 == address/8) {
        return 1;
      }
    }
  }
  else if (associativity < blocks){
    set = (address/8)%associativity;
    for (int i = 0; i < blocks/associativity; i++) {
      if (cache[i][set] != -1) {
        if (cache[i][set]/8 == address/8) {
          return 1;
        }
      }
    }
  }
  else {
    for (int i = 0; i < blocks; i++) {
      if (cache[0][i] != -1) {
        if (cache[0][i]/8 == address/8) {
          return 1;
        }
      }
    }
  }
  return 0;
}

void getAdresses(char* fileName, int** addresses, int* len) {
  char  line[11];
  FILE* file;
  file = fopen(fileName, "r");

  if (file){
    while (fgets(line, 11, file)) {
      (*addresses) = realloc((*addresses), (*len) * sizeof(int));
      (*addresses)[(*len) - 1] = atoi(line);
      (*len) ++;
    }
    (*len) --;
    fclose(file);
  }
  else {
    printf("  > The '%s' file isn't there!!\n", fileName);
  }
}

void cacheGenerator(int associativity, int blocks, int*** cache) {
  (*cache) = (int**)calloc((blocks/associativity),sizeof(int*));
  for (int i = 0; i < blocks/associativity; i++) {
    (*cache)[i] = (int*)calloc(associativity, sizeof(int));
    for (int j = 0; j < associativity; j++) {
      (*cache)[i][j] = -1;
    }
  }
}

void fifo(int address, int*** cache, int blocks, int associativity, Queue* queue) {
  int i;
  if (associativity == 1) {
    for (i = 0; i < blocks; i++) {
      if ((*cache)[i][0] == queue->head->value) {
        (*cache)[i][0] = address;
        deQueue(queue, &i);
        break;
      }
    }
  }
  else if (associativity < blocks) {
    int j;
    int set = (address/8)%associativity;
    int replaced = 0;
    Node* actual = queue->head;
    for (i = 0; i < queue->size; i++) {
      for (j = 0; j < blocks/associativity; j++) {
        if ((*cache)[j][set] == actual->value) {
          (*cache)[j][set] = address;
          removeFromQueue(queue, actual->value);
          replaced = 1;
          break;
        }
      }
      if (replaced) {
        break;
      }
      actual = actual->next;
    }
  }
  else {
    for (i = 0; i < blocks; i++) {
      if ((*cache)[0][i] == queue->head->value) {
        (*cache)[0][i] = address;
        deQueue(queue, &i);
        break;
      }
    }
  }
}

void lifo(int address, int*** cache, int blocks, int associativity, Stack* stack) {
  int i;
  if (associativity == 1) {
    for (i = 0; i < blocks; i++) {
      if ((*cache)[i][0] == stack->head->value) {
        (*cache)[i][0] = address;
        pop(stack, &i);
        break;
      }
    }
  }
  else if (associativity < blocks) {
    int j;
    int set = (address/8)%associativity;
    int replaced = 0;
    Node* actual = stack->head;
    for (i = 0; i < stack->size; i++) {
      for (j = 0; j < blocks/associativity; j++) {
        if ((*cache)[j][set] == actual->value) {
          (*cache)[j][set] = address;
          removeFromStack(stack, actual->value);
          replaced = 1;
          break;
        }
      }
      if (replaced) {
        break;
      }
      actual = actual->next;
    }
  }
  else {
    for (i = 0; i < blocks; i++) {
      if ((*cache)[0][i] == stack->head->value) {
        (*cache)[0][i] = address;
        pop(stack, &i);
        break;
      }
    }
  }
}

void updateReplacementData(int address, Queue* queue, Stack* stack, int policy) {
  switch (policy) {
    case 1:
    enQueue(queue, address);
    break;
    case 2:
    push(stack, address);
    break;
    case 3:
    enQueueExclusive(queue, address);
    break;
    case 4:
    pushExclusive(stack, address);
    break;
  }
}

void replacementStorageGenerator(Queue** queue, Stack** stack, int policy) {
  switch (policy) {
    case 1:
    (*queue) = createQueue();
    break;
    case 2:
    (*stack) = createStack();
    break;
    case 3:
    (*queue) = createQueue();
    break;
    case 4:
    (*stack) = createStack();
    break;
  }
}

void insert(int address, int*** cache, int blocks, int associativity, int* replace) {
  int i;
  if (associativity == 1) {
    (*cache)[(address/8)%blocks][0] = address;
  }
  else if (associativity < blocks) {
    int set = (address/8)%associativity;
    for (i = 0; i < blocks/associativity; i++) {
      if ((*cache)[i][set] == -1) {
        (*cache)[i][set] = address;
        (*replace) = 0;
        break;
      }
    }
  }
  else {
    for (i = 0; i < blocks; i++) {
      if ((*cache)[0][i] == -1) {
        (*cache)[0][i] = address;
        (*replace) = 0;
        break;
      }
    }
  }
}

void freeCache(int*** cache, int lines) {
  for (int i = 0; i < lines; i++) {
    free((*cache)[i]);
  }
  free(*cache);
  *cache = NULL;
}

void saveCacheState(int*** destiny, int** origin, int blocks, int associativity) {
  int i,j;
  cacheGenerator(associativity, blocks, destiny);
  for (i = 0; i < blocks/associativity; i++) {
    for (j = 0; j < associativity; j++) {
      (*destiny)[i][j] = origin[i][j];
    }
  }
}

void getBestConfiguration(int** addresses, int len, int capacity, int wordsPerBlock) {
  int blocks = capacity/(wordsPerBlock*4);
  int misses;
  int replace;
  int** cache;
  int** bestCache;
  int bestAssociativity;
  int bestHitAmounth;
  int bestPolicy;
  Queue* queue = NULL;
  Stack* stack = NULL;
  /* Associativities */
  printf("=================================\n");
  bestAssociativity = 0;
  bestHitAmounth = 0;
  bestPolicy = 0;
  for (int i = 1; i < blocks+1; i = i*2) {
    /* Replacement Policies */
    printf("Associativity: %d\n\n", i);
    for (int j = 1; j < 5; j++) {
      cacheGenerator(i, blocks, &cache);
      replacementStorageGenerator(&queue, &stack, j);
      misses = 0;
      /* Addresses*/
      for (int k = 0; k < len; k++) {
        replace = 1;
        if (j > 2) {
          updateReplacementData((*addresses)[k], queue, stack, j);
        }
        if (!searchFor((*addresses)[k], cache, blocks, i)) {
          misses ++;
          insert((*addresses)[k], &cache, blocks, i, &replace);
          if (j < 3) {
            updateReplacementData((*addresses)[k], queue, stack, j);
          }
          if (replace) {
            switch (j) {
              case 1:
              fifo((*addresses)[k], &cache, blocks, i, queue);
              break;
              case 2:
              lifo((*addresses)[k], &cache, blocks, i, stack);
              break;
              case 3:
              fifo((*addresses)[k], &cache, blocks, i, queue);
              break;
              case 4:
              lifo((*addresses)[k], &cache, blocks, i, stack);
              break;
            }
          }
        }
      }
      if (len - misses > bestHitAmounth) {
        bestHitAmounth = len - misses;
        bestAssociativity = i;
        bestPolicy = j;
        saveCacheState(&bestCache, cache, blocks, i);
      }
      printf("Policy:        %d\n", j);
      printf("Hits:          %d\n", len - misses);
      printf("Misses:        %d\n", misses);
      printf("\n");
      freeCache(&cache, blocks/i);
      freeQueue(queue);
    }
    printf("=================================\n");
  }
  printf("Best Associativity: %d\n", bestAssociativity);
  printf("Best Policy: %d\n", bestPolicy);
  printf("Hits: %d\n", bestHitAmounth);

}

void init(int argc, char* const argv[]) {
  int len = 1;
  int* addresses = (int*)calloc(1,sizeof(int));
  int operation = 0;
  int capacity = 0;
  int wordsPerBlock = 0;
  while ((operation = getopt(argc, argv, "n:m:p:")) != -1) {
    switch (operation) {
      case 'n':
      getAdresses(optarg, &addresses, &len);
      break;
      case 'm':
      capacity = atoi(optarg);
      break;
      case 'p':
      wordsPerBlock = atoi(optarg);
      break;
    }
  }
  getBestConfiguration(&addresses, len, capacity, wordsPerBlock);
}
