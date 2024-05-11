#ifndef PARSER_H
#define PARSER_H

#include "symbols.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ERR 0xFF

/* A instruction or C instruction */
typedef enum { A, C } c_type;

/* value - name of symbol or variable
 * data - address of symbol or variable */
typedef struct key_val {
  char *value;
  unsigned short data;
} key_val;

/* table to hold initial values of C instructions */
typedef struct c_table {
  int comp_len;
  key_val table[];
} c_table;

/*  000|0 |0000 00|00 0|000
 *     |  |       |    |
 *  C/A|A?| comp  |dst |jmp */
typedef struct instruction {
  c_type type;
  unsigned short literal : 15;
  unsigned short comp : 7;
  unsigned short dest : 3;
  unsigned short jump : 3;
} instruction;

/* strips line to relevant string
 * returns type instruction if not NULL */
instruction *parse_instruction(char *line);

/* checks relevant table (comp, dst, or jmp) for address info */
unsigned short get_value(c_table *ct, char *val);

/* assigns each value (comp, dest, jump) to type instruction */
void check_c_type(char *line, unsigned short *comp, unsigned char *dest,
                  unsigned char *jump, unsigned char *a_val);

/* checks for valid instruction */
bool is_instruction(char *line);

/* trims just whitespace at beginning and end of string
 * returns the string */
char *trim_whitespace(char *line);

/* uses trim_whitespace and then removes any comments
 * returns the string */
char *format_line(char *line);

#endif
