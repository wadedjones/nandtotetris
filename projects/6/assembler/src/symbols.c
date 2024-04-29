#include "../inc/symbols.h"
#include "../inc/parser.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

void symbol_table_init(symbol_table *st) {
  st->symbols = calloc(INIT_TABLE_SIZE, sizeof(symbol));
  st->table_len = INIT_TABLE_SIZE;
  st->total_symbols = NUM_DEFAULT_SYMBOLS;

  for (int i = 0; i < st->total_symbols; i++) {
    strcpy(st->symbols[i].var, default_symbols[i].var);
    st->symbols[i].addr = default_symbols[i].addr;
  }
}

void symbol_table_resize(symbol_table *st) {
  symbol *vals = st->symbols;
  size_t total_symbols_old = st->total_symbols;

  st->table_len = st->table_len * 2 + 1;
  st->symbols = calloc(st->table_len, sizeof(symbol));
  st->total_symbols = 0;

  for (size_t i = 0; i < total_symbols_old; i++) {
    st->symbols[i] = vals[i];
  }
}

void symbol_parse(char *line, symbol_table *st) {
  static unsigned short address = 0;

  if (is_instruction(line)) {
    address++;
    return;
  }

  line = format_line(line);

  if (line[0] == '(') {
    line++;
    char *end = strchr(line, ')');
    *end = 0;
    symbol_add(st, line, &address);
  }
}

void symbol_add(symbol_table *st, char *line, unsigned short *address) {

  for (int i = 0; i < st->total_symbols; i++) {
    if (strcmp(st->symbols[i].var, line) == 0) {
      return;
    }
  }
  st->symbols[st->total_symbols - 1].addr = *address;
  strcpy(st->symbols[st->total_symbols - 1].var, line);
  st->total_symbols++;

  /* resize symbol table (doesn't seem to work yet) */
  // if (st->total_symbols + 1 == st->table_len) {
  //   symbol_table_resize(st);
  // }
}

void symbol_replace(symbol_table *st, char *line) {
  static unsigned short var_address = 16;
  line = format_line(line);
  unsigned short address;

  if (line[0] == '@' && !(line[1] <= '9' && line[1] >= '0')) {
    address = symbol_find(st, line + 1);
    if (address == SNF) {
      address = var_address;
      symbol_add(st, line + 1, &address);
      var_address++;
    }
    sprintf(line + 1, "%d", address);
  }
}

unsigned short symbol_find(symbol_table *st, char *line) {

  for (int i = 0; i < st->total_symbols; i++) {
    if ((strcmp(st->symbols[i].var, line)) == 0) {
      return st->symbols[i].addr;
    }
  }
  return SNF;
}

void symbol_print(symbol_table *st) {
  for (int i = 0; i < st->total_symbols; i++) {
    printf("var: %s, addr: %d\n", st->symbols[i].var, st->symbols[i].addr);
  }
  printf("\nTotal Symbols: %d\n", st->total_symbols);
}

const symbol default_symbols[] = {
    {"SP", 0},   {"LCL", 1},         {"ARG", 2},     {"THIS", 3}, {"THAT", 4},
    {"R0", 0},   {"R1", 1},          {"R2", 2},      {"R3", 3},   {"R4", 4},
    {"R5", 5},   {"R6", 6},          {"R7", 7},      {"R8", 8},   {"R9", 9},
    {"R10", 10}, {"R11", 11},        {"R12", 12},    {"R13", 13}, {"R14", 14},
    {"R15", 15}, {"SCREEN", 0x4000}, {"KBD", 0x6000}};
