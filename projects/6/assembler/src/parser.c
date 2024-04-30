#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/parser.h"

c_table c_comp = {28,
                  {
                      {"0", 42},   {"1", 63},   {"-1", 58},  {"D", 12},
                      {"A", 48},   {"!D", 13},  {"!A", 49},  {"-D", 15},
                      {"-A", 51},  {"D+1", 31}, {"A+1", 55}, {"D-1", 14},
                      {"A-1", 50}, {"D+A", 2},  {"D-A", 19}, {"A-D", 7},
                      {"D&A", 0},  {"D|A", 21}, {"M", 48},   {"!M", 49},
                      {"-M", 51},  {"M+1", 55}, {"M-1", 50}, {"D+M", 2},
                      {"D-M", 19}, {"M-D", 7},  {"D&M", 0},  {"D|M", 21},
                  }};

c_table c_dest = {8,
                  {
                      {"null", 0},
                      {"M", 1},
                      {"D", 2},
                      {"MD", 3},
                      {"A", 4},
                      {"AM", 5},
                      {"AD", 6},
                      {"AMD", 7},
                  }};

c_table c_jump = {8,
                  {
                      {"null", 0},
                      {"JGT", 1},
                      {"JEQ", 2},
                      {"JGE", 3},
                      {"JLT", 4},
                      {"JNE", 5},
                      {"JLE", 6},
                      {"JMP", 7},
                  }};

instruction *parse_instruction(char *line) {

  line = format_line(line);

  if (strlen(line) == 0) {
    return NULL;
  }

  if (line[0] == '(') {
    return NULL;
  }

  if (line[0] == '@') {
    int val;
    if (sscanf(line, "@%d", &val) == 0) {
      fprintf(stderr, "invalid instruction\n");
      exit(EXIT_FAILURE);
    }
    instruction *result = malloc(sizeof(instruction));
    result->type = A;
    result->literal = val;
    return result;
  } else {
    unsigned short comp;
    unsigned char dest;
    unsigned char jump;
    unsigned char a_val;
    check_c_type(line, &comp, &dest, &jump, &a_val);

    instruction *result = malloc(sizeof(instruction));
    result->type = C;
    result->comp = comp;
    result->comp |= a_val << 6;
    result->dest = dest;
    result->jump = jump;

    return result;
  }

  return NULL;
}

void check_c_type(char *line, unsigned short *comp, unsigned char *dest,
                  unsigned char *jump, unsigned char *a_val) {
  *comp = 0;
  *dest = 0;
  *jump = 0;

  char *cpos = strchr(line, '=');
  char *jpos = strchr(line, ';');

  if (jpos != NULL) {
    *jpos = '\0';
    jpos++;
    jpos = trim_whitespace(jpos);
    *jump = get_value(&c_jump, jpos);
  } else {
    *jump = 0;
  }

  if (cpos != NULL) {
    *cpos = '\0';
    cpos++;

    cpos = trim_whitespace(cpos);
    line = trim_whitespace(line);

    char *a_val_check = strchr(cpos, 'M');
    if (a_val_check != NULL) {
      *a_val = 1;
    } else {
      *a_val = 0;
    }

    *comp = get_value(&c_comp, cpos);
    *dest = get_value(&c_dest, line);
  } else {
    *a_val = 0;
    *dest = 0;
    line = trim_whitespace(line);
    *comp = get_value(&c_comp, line);
  }
}

unsigned short get_value(c_table *ct, char *val) {
  for (int i = 0; i < ct->comp_len; i++) {
    if (strcmp(ct->table[i].value, val) == 0) {
      return ct->table[i].data;
    }
  }
  return ERR;
}

bool is_instruction(char *line) {
  line = format_line(line);

  if (line[0] == '@') {
    return true;
  } else {
    unsigned short comp;
    unsigned char dest;
    unsigned char jump;
    unsigned char a_val;

    check_c_type(line, &comp, &dest, &jump, &a_val);

    if (comp != ERR) {
      return true;
    }
  }

  return false;
}

char *format_line(char *line) {
  line = trim_whitespace(line);

  char *comment;
  comment = strstr(line, "//");

  if (comment == 0) {
    return line;
  } else {
    *comment = '\0';
  }

  line = trim_whitespace(line);

  return line;
}

char *trim_whitespace(char *line) {
  char *end;

  while (isspace(*line))
    line++;

  if (*line == '\0')
    return line;

  end = line + strlen(line) - 1;
  while (end > line && isspace(*end))
    end--;

  *(end + 1) = '\0';

  return line;
}
