#include "functions.h"

int searchFor(int address, int** cache, int blocks, int associativity) {
  for (int i = 0; i < blocks/associativity; i++) {
    for (int j = 0; j < associativity; j++) {
      if ()
    }
  }
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
  }
}

void replace(int address, int** cache, int blocks, int associativity) {


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
  int** cache;
  for (int i = 1; i < blocks+1; i = i*2) {
    for (int j = 0; j < 4; j++) {
      cacheGenerator(i, blocks, &cache);
      for (int k = 0; k < len; k++) {
        if (searchFor((*addresses)[k], cache, blocks, i)) {

        }
        else {

        }
      }
      freeCache(&cache, blocks/i);
    }
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
