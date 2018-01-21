#include <stdint.h>
#include <stdio.h>
#include "redcode.h"

#define CORE_COUNT 256
#define DEBUG_MODE 0

struct cell {
  uint8_t owner;
  uint32_t instruction;
};

struct core {
  struct cell cells[CORE_COUNT];
};

uint8_t *parse_instruction(uint32_t instr);

/* print the core to the screen, for debug purposes */

void print_core(struct core c) {
  int x = 0;
  printf("Core Debugger:\r\n");
  for (x=0; x<CORE_COUNT; x++) {
    if ((x % 16) == 0)
      printf("\r\n");
    printf("[%d] ", c.cells[x].owner);
  }
  printf("\r\n");
}

/* initialize the core and set all instructions to zero (NOOP), owned by nobody */
struct core * core_initialize(struct core *c) {
  int x = 0;
  for (x=0; x<CORE_COUNT; x++) {
    c->cells[x].owner = 0;
    c->cells[x].instruction = 0x5114;
  }
  return c;
}

void exec(struct core *c) {

  int pc = 0;
  uint8_t *instr;

  while (pc < 256) {

    instr = parse_instruction(c->cells[pc].instruction);

    printf("%d\r\n", instr[0]);

    switch(c->cells[pc].instruction) {
      case DAT:
        if (DEBUG_MODE)
          printf("(%d) NOOP\r\n", pc);
        pc++;
      break;
      case MOV:
        if (DEBUG_MODE)
          printf("(%d) MOV r%d, r%d\r\n", pc, pc, pc);
      break;
    }

    pc++;

  }

}

uint8_t *parse_instruction(uint32_t instr) {

  static uint8_t instructions[4];
  instructions[0] = instr ^ 0x1110;
  return instructions;

}

void main() {

  struct core c;
  core_initialize(&c);
  print_core(c);
  exec(&c);

}
