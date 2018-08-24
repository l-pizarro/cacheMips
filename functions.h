#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "queue.h"
#include "stack.h"

// Functions to obtain the best cache configuration (Headers)

int searchFor(int address, int** cache, int blocks, int associativity);
void init(int argc, char* const []);
void fifo(int address, int*** cache, int blocks, int associativity, Queue* queue);
void lifo(int address, int*** cache, int blocks, int associativity, Stack* stack);
void insert(int address, int*** cache, int blocks, int associativity, int* replace);
void freeCache(int*** cache, int lines);
void getAdresses(char* fileName, int** addresses, int* len);
void cacheGenerator(int associativity, int blocks, int*** cache);
void getBestConfiguration(int** addresses, int len, int capacity, int wordsPerBlock);
