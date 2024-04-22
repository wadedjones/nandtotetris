#include "parser.h"
#include <stdbool.h>
#include <stdio.h>

int main(void) {
  char line[] = "D;JGT";

  unsigned short *comp = malloc(sizeof(comp));
  unsigned char *dest = malloc(sizeof(dest));
  unsigned char *jump = malloc(sizeof(jump));
  unsigned char *a_val = malloc(sizeof(a_val));

  instruction *result = parse_instruction(line, comp, dest, jump, a_val);

  convert_bytes(result);

  return 0;
}
