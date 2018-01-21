#include <stdint.h>
#include <stdio.h>

#define CORE_COUNT 256
#define DEBUG_MODE 1

struct cell {
  uint8_t owner;
  uint32_t instruction;
};

struct core {
  struct cell cells[CORE_COUNT];
};


void print_core(struct core c) {
  int x = 0;
  printf("Core Debugger:\r\n");
  for (x=0; x<CORE_COUNT; x++) {
    printf("[%d] ", c.cells[x].owner);
  }
}

struct core * core_initialize(struct core *c) {
  int x = 0;
  for (x=0; x<CORE_COUNT; x++) {
    c->cells[x].owner = 0;
    c->cells[x].instruction = 0;
  }
  return c;
}

void exec(struct core *c) {

  int pc = 0;

  while (pc < 256) {

    switch(c->cells[pc].instruction) {
      case 0:
        if (DEBUG_MODE)
          printf("NOOP\r\n");
      break;
      case 1:
      break;
    }

    pc++;

  }

}

uint8_t instr * process_instruction(uint32_t instr) {

  uint8_t instr[4];  

  printf("%d", instr);

}

void main() {

  struct core c;
  core_initialize(&c);
  print_core(c);
  exec(&c);

}
