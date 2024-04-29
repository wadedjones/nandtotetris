#include "../inc/assembler.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *create_outfile(char *filename);

int main(int argc, char **argv) {

  if (argc != 2) {
    fprintf(stderr, "usage: %s <filename>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  char *filename = argv[1];
  char *outfile = create_outfile(filename);

  FILE *fp_in = fopen(filename, "r");
  FILE *fp_out = fopen(outfile, "w");

  assemble(fp_in, fp_out);

  free(outfile);
  fclose(fp_in);
  fclose(fp_out);

  return 0;
}

char *create_outfile(char *filename) {
  char *new_file = malloc(sizeof(filename));
  strcpy(new_file, filename);
  char *end = strstr(new_file, "asm");
  if (end == NULL) {
    fprintf(stderr, "invalid file type: %s\n", filename);
    free(new_file);
    exit(EXIT_FAILURE);
  }
  *end = 0;
  strcat(new_file, "hack");
  return new_file;
}
