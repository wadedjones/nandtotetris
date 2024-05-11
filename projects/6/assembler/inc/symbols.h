#ifndef SYMBOLS_H
#define SYMBOLS_H

#define NUM_DEFAULT_SYMBOLS 23
#define INIT_TABLE_SIZE 100

// symbol not found error
#define SNF 0xffff
#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

/* struct for symbols and variables in .asm file */
typedef struct symbol {
  char *key;
  unsigned short addr;
} symbol;

/* a "hash" table to hold all variables and symbols found in .asm file */
typedef struct symbol_table {
  int table_len;
  int total_symbols;
  symbol *symbols;
} symbol_table;

/* holds the initial 23 symbols allowed in the hack assembly language spec */
extern symbol default_symbols[];

/* initializes symbol table with default symbols, allocates space for 100 total
 * symbols */
void symbol_table_init(symbol_table *st, symbol *default_symbols);

/* frees all the allocated symbols and the table itself */
void symbol_table_free(symbol_table *st);

/* increases size of symbol table x2 and copies over the current symbols */
void symbol_table_expand(symbol_table *st);

/* removes all non alpha chars from symbol string */
void symbol_parse(char *line, symbol_table *st);

/* adds symbol to symbol table
 * expands table if total symbols exceeds half the capacity
 * returns the key (*line) */
char *symbol_add(symbol_table *st, char *line, unsigned short *addr);

/* replaces symbols with corresponding address */
void symbol_replace(symbol_table *st, char *line);

/* looks up symbol in symbol table
 * returns the address if found
 * returns SNF if not found */
unsigned short symbol_find(symbol_table *st, char *key);

/* simple utility function to print all symbols in symbol table */
void symbol_print(symbol_table *st);

#endif
