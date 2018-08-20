#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <math.h>

int searchFor(int address, int** cache, int blocks, int associativity);
void init(int argc, char* const []);
void fifo();
void insert(int address, int*** cache, int blocks, int associativity, int* replace);
void freeCache(int*** cache, int lines);
void getAdresses(char* fileName, int** addresses, int* len);
void cacheGenerator(int ways, int blocks, int*** cache);
void getBestConfiguration(int** addresses, int len, int capacity, int wordsPerBlock);
