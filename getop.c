#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  int operation;
  while ((operation = getopt(argc, argv, "n:m:p:")) != -1) {
    switch (operation) {
      case 'n':
      printf("> n detected -> %s\n", optarg);
      case 'm':
      printf("> m detected -> %s\n", optarg);
      case 'p':
      printf("> p detected -> %s\n", optarg);
      break;
    }
    break;
  }
  return 0;
}
