#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 100

int main(int argc, char **argv) {

  if (argc != 3) {
    fprintf(stderr, "usage: %s <filename1> <filename2>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  FILE *fp_test;
  FILE *fp_orig;

  int line = 0;
  int total_misses = 0;

  fp_test = fopen(argv[1], "rb");
  fp_orig = fopen(argv[2], "rb");

  char buf_test[MAX_LINE];
  char buf_orig[MAX_LINE];

  while (!feof(fp_test)) {
    fgets(buf_test, MAX_LINE, fp_test);
    fgets(buf_orig, MAX_LINE, fp_orig);

    if ((strcmp(buf_test, buf_orig)) != 0) {
      fprintf(stderr, "line: %d\n\n\t%s\n\t%s\n", line, buf_test, buf_orig);
      // exit(EXIT_FAILURE);
      total_misses++;
    }
    line++;
  }
  printf("total misses: %d\n", total_misses);

  printf("Test successful\n");

  fclose(fp_test);
  fclose(fp_orig);

  return 0;
}
