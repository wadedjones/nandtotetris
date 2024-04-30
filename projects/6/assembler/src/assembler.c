#include "../inc/assembler.h"
#include "../inc/parser.h"
#include "../inc/symbols.h"
#include <stdio.h>
#include <string.h>

char buf[BUFSIZE];

void assemble(FILE *fp_in, FILE *fp_out) {
  instruction *result = malloc(sizeof(instruction));
  symbol_table st;
  symbol_table_init(&st);

  while (fgets(buf, BUFSIZE, fp_in) != NULL) {
    buf[strcspn(buf, "\n")] = 0;
    symbol_parse(buf, &st);
  }

  rewind(fp_in);

  while (fgets(buf, BUFSIZE, fp_in)) {
    buf[strcspn(buf, "\n")] = 0;
    symbol_replace(&st, buf);
    if ((result = parse_instruction(buf)) == NULL) {
      continue;
    }

    convert_bytes(result, fp_out);
  }

  free(result);
  free(st.symbols);
}

void convert_bytes(instruction *inst, FILE *fp_out) {
  char result_str[18];
  if (inst->type == A) {
    sprintf(result_str, PATTERN, BTB(inst->literal));
    fputs(result_str, fp_out);
  }
  if (inst->type == C) {
    unsigned short result = 0;
    char result_str[18];
    result |= 0b111 << 13;
    result |= inst->comp << 6;
    result |= inst->dest << 3;
    result |= inst->jump;
    sprintf(result_str, PATTERN, BTB(result));
    fputs(result_str, fp_out);
  }
}
