#ifndef SYMBOLS_H
#define SYMBOLS_H

#define NUM_DEFAULT_SYMBOLS 23
#define INIT_TABLE_SIZE 100

// symbol not found error
#define SNF 0xffff

typedef struct symbol {
  char var[64];
  unsigned short addr;
} symbol;

typedef struct symbol_table {
  int table_len;
  int total_symbols;
  symbol *symbols;
} symbol_table;

extern const symbol default_symbols[];

void symbol_table_init(symbol_table *st);
void symbol_table_resize(symbol_table *st);
void symbol_parse(char *line, symbol_table *st);
void symbol_add(symbol_table *st, char *line, unsigned short *address);
void symbol_replace(symbol_table *st, char *line);
unsigned short symbol_find(symbol_table *st, char *line);
void symbol_print(symbol_table *st);

#endif
