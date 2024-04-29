#ifndef PARSER_H
#define PARSER_H

#include "symbols.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ERR 0b11111111

typedef enum { A, C } c_type;

typedef struct key_val {
  char *value;
  unsigned short data;
} key_val;

typedef struct c_table {
  int comp_len;
  key_val table[];
} c_table;

typedef struct instruction {
  c_type type;
  unsigned short literal : 15;
  unsigned short comp : 7;
  unsigned short dest : 3;
  unsigned short jump : 3;
} instruction;

instruction *parse_instruction(char *line, unsigned short *comp,
                               unsigned char *dest, unsigned char *jump,
                               unsigned char *a_val);
unsigned short get_value(c_table *ct, char *val);
void check_c_type(char *line, unsigned short *comp, unsigned char *dest,
                  unsigned char *jump, unsigned char *a_val);
bool is_instruction(char *line);
char *trim_whitespace(char *line);
char *format_line(char *line);

#endif
