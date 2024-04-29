#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "parser.h"
#include <stdio.h>

#define BUFSIZE 100
/* clang-format off */
#define PATTERN "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n"
#define BTB(byte)  \
  ((byte) & 0x8000 ? '1' : '0'), \
  ((byte) & 0x4000 ? '1' : '0'), \
  ((byte) & 0x2000 ? '1' : '0'), \
  ((byte) & 0x1000 ? '1' : '0'), \
  ((byte) & 0x800 ? '1' : '0'), \
  ((byte) & 0x400 ? '1' : '0'), \
  ((byte) & 0x200 ? '1' : '0'), \
  ((byte) & 0x100 ? '1' : '0'), \
  ((byte) & 0x80 ? '1' : '0'), \
  ((byte) & 0x40 ? '1' : '0'), \
  ((byte) & 0x20 ? '1' : '0'), \
  ((byte) & 0x10 ? '1' : '0'), \
  ((byte) & 0x08 ? '1' : '0'), \
  ((byte) & 0x04 ? '1' : '0'), \
  ((byte) & 0x02 ? '1' : '0'), \
  ((byte) & 0x01 ? '1' : '0')

void assemble(FILE *fp_in, FILE *fp_out);
void convert_bytes(instruction *inst, FILE *fp_out);

#endif
