#ifndef SYMBOL_H
#define SYMBOL_H

#define LABEL_LEN 64

typedef struct symbol {
  char label[LABEL_LEN];
  unsigned short address;
} symbol;

extern const symbol default_symbols[];

#endif
