#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <math.h>

int searchFor(int address, int** cache, int blocks, int associativity);
void init(int argc, char* const []);
void replace();
void freeCache(int*** cache, int lines);
void getAdresses(char* fileName, int** addresses, int* len);
void cacheGenerator();
void getBestConfiguration(int** addresses, int len, int capacity, int wordsPerBlock);
