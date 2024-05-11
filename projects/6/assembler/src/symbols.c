#include "../inc/symbols.h"
#include "../inc/parser.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static uint64_t hash_key(const char *key) {
  uint64_t hash = FNV_OFFSET;
  for (const char *p = key; *p; p++) {
    hash ^= (uint64_t)(unsigned char)(*p);
    hash *= FNV_PRIME;
  }
  return hash;
}

void symbol_table_init(symbol_table *st, symbol *default_symbols) {
  st->symbols = calloc(INIT_TABLE_SIZE, sizeof(symbol));
  st->table_len = INIT_TABLE_SIZE;
  st->total_symbols = NUM_DEFAULT_SYMBOLS;

  for (int i = 0; i < NUM_DEFAULT_SYMBOLS; i++) {
    symbol_add(st, default_symbols[i].key, &default_symbols[i].addr);
  }
}

void symbol_table_free(symbol_table *st) {
  for (int i = 0; i < st->table_len; i++) {
    free((void *)st->symbols[i].key);
  }
  free(st->symbols);
  // free(st);
}

char *symbol_add(symbol_table *st, char *line, unsigned short *addr) {
  uint64_t hash = hash_key(line);
  size_t index = (size_t)(hash & (uint64_t)(st->table_len - 1));

  if (st->total_symbols >= st->table_len / 2) {
    symbol_table_expand(st);
  }

  while (st->symbols[index].key != NULL) {
    if (strcmp(line, st->symbols[index].key) == 0) {
      return line;
    }
    index++;
    if (index >= (size_t)st->table_len) {
      index = 0;
    }
  }
  line = strdup(line);
  st->symbols[index].key = (char *)line;
  st->symbols[index].addr = *addr;
  st->total_symbols++;
  return st->symbols[index].key;
}

void symbol_table_expand(symbol_table *st) {
  size_t new_len = st->table_len * 2;
  symbol *old_symbols = st->symbols;

  st->table_len = new_len;
  st->symbols = calloc(st->table_len, sizeof(symbol));
  st->total_symbols = 0;

  for (size_t i = 0; i < (size_t)st->table_len / 2; i++) {
    if (old_symbols[i].key != NULL) {
      symbol_add(st, old_symbols[i].key, &old_symbols[i].addr);
    }
  }
  free(old_symbols);
}

unsigned short symbol_find(symbol_table *st, char *key) {
  uint64_t hash = hash_key(key);
  size_t index = (size_t)(hash & (uint64_t)(st->table_len - 1));

  while (st->symbols[index].key != NULL) {
    if (strcmp(key, st->symbols[index].key) == 0) {
      return st->symbols[index].addr;
    }
    index++;
    if (index >= (size_t)st->table_len) {
      index = 0;
    }
  }
  return SNF;
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

void symbol_replace(symbol_table *st, char *line) {
  static unsigned short key_address = 16;
  line = format_line(line);
  unsigned short address;

  if (line[0] == '@' && !(line[1] <= '9' && line[1] >= '0')) {
    address = symbol_find(st, line + 1);
    if (address == SNF) {
      address = key_address;
      symbol_add(st, line + 1, &address);
      key_address++;
    }
    sprintf(line + 1, "%d", address);
  }
}

void symbol_print(symbol_table *st) {
  for (int i = 0; i < st->table_len; i++) {
    if (st->symbols[i].key != NULL) {
      printf("i: %d, key: %s, addr: %d\n", i, st->symbols[i].key,
             st->symbols[i].addr);
    }
  }
}

symbol default_symbols[] = {
    {"SP", 0},   {"LCL", 1},         {"ARG", 2},     {"THIS", 3}, {"THAT", 4},
    {"R0", 0},   {"R1", 1},          {"R2", 2},      {"R3", 3},   {"R4", 4},
    {"R5", 5},   {"R6", 6},          {"R7", 7},      {"R8", 8},   {"R9", 9},
    {"R10", 10}, {"R11", 11},        {"R12", 12},    {"R13", 13}, {"R14", 14},
    {"R15", 15}, {"SCREEN", 0x4000}, {"KBD", 0x6000}};
