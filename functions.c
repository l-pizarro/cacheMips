#include "functions.h"
#include "queue.h"

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
  else {
    set = (address/8)%associativity;
    for (int i = 0; i < blocks/associativity; i++) {
      if (cache[i][set] != -1) {
        if (cache[i][set]/8 == address/8) {
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

void cacheGenerator(int ways, int blocks, int*** cache) {
  (*cache) = (int**)calloc((blocks/ways),sizeof(int*));
  for (int i = 0; i < blocks/ways; i++) {
    (*cache)[i] = (int*)calloc(ways, sizeof(int));
    for (int j = 0; j < ways; j++) {
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
  else {
    int j;
    int set = (address/8)%associativity;
    int replaced = 0;
    Node* actual = queue->head;
    for (i = 0; i < queue->size; i++) {
      for (j = 0; j < blocks/associativity; j++) {
        if ((*cache)[j][set] == actual->value) {
          (*cache)[j][set] = address;
          removeValue(queue, actual->value);
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
}

void updateReplacementData(int address, Queue* queue, int policy) {
  switch (policy) {
    case 1:
    enQueue(queue, address);
  }
}

void replacementStorageGenerator(Queue** queue, int policy) {
  switch (policy) {
    case 1:
    *(queue) = createQueue();
    break;
    case 2:
    break;
    case 3:
    break;
    case 4:
    break;
  }
}

void insert(int address, int*** cache, int blocks, int associativity, int* replace) {
  if (associativity == 1) {
    (*cache)[(address/8)%blocks][0] = address;
  }
  else {
    int emptyBlocks = 0;
    int set = (address/8)%associativity;
    for (int i = 0; i < blocks/associativity; i++) {
      if ((*cache)[i][set] == -1) {
        emptyBlocks ++;
      }
    }
    if (emptyBlocks) {
      for (int i = 0; i < blocks/associativity; i++) {
        if ((*cache)[i][set] == -1) {
          (*cache)[i][set] = address;
          break;
        }
      }
    }
    else {
      (*replace) = 1;
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

void getBestConfiguration(int** addresses, int len, int capacity, int wordsPerBlock) {
  int blocks = capacity/(wordsPerBlock*4);
  int replace;
  int** cache;
  Queue* queue = NULL;
  /* Associativities */
  for (int i = 1; i < 3; i = i*2) {
    printf("Associativity: %d\n", i);
    /* Replacement Policies */
    for (int j = 1; j < 2; j++) {
      printf("Policy: %d\n", j);
      cacheGenerator(i, blocks, &cache);
      replacementStorageGenerator(&queue, j);
      /* Addresses*/
      for (int k = 0; k < len; k++) {
        printf("Addres: %d\n", (*addresses)[k]);
        replace = 0;
        if (!searchFor((*addresses)[k], cache, blocks, i)) {
          printf("  > Miss\n");
          insert((*addresses)[k], &cache, blocks, i, &replace);
          printf("  > Insert ready\n");
          updateReplacementData((*addresses)[k], queue, j);
          printf("  > Updated Queue\n");
          if (replace) {
            switch (j) {
              case 1:
              fifo((*addresses)[k], &cache, blocks, i, queue);
              break;
              case 2:
              break;
              case 3:
              break;
              case 4:
              break;
            }
          }
        }
        else {
          printf("  > Hit\n");
        }
      }
      freeCache(&cache, blocks/i);
      freeQueue(queue);
    }
    printf("\n");
  }
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
