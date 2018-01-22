#include <stdint.h>
#include <stdio.h>
#include "redcode.h"

#define CORE_COUNT 256
#define DEBUG_MODE 1

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
    c->cells[x].instruction = 0x31111111;
  }
  return c;
}

void exec(struct core *c) {

  int pc = 0;
  uint8_t *instr;
  uint8_t *instr_p;
  struct cell src_cell;
  struct cell dest_cell;
  uint8_t src;
  uint8_t dest;

  while (pc < 256) {

    instr = parse_instruction(c->cells[pc].instruction);

    switch (instr[MODE1]) {
      case IMMEDIATE:
        src = instr[R0];
      break;
      case RELATIVE:
        src = pc + instr[R0];
      break;
      case INDIRECT:
        src_cell = c->cells[pc + instr[R0]];
        instr_p = parse_instruction(src_cell.instruction);
        src = instr_p[R1];
      break;
    }

   switch(instr[MODE2]) {
      case IMMEDIATE:
        dest = instr[R0];
      break;
      case RELATIVE:
        dest = pc + instr[R0];
      break;
      case INDIRECT:
        dest_cell = c->cells[pc + instr[R0]];
        instr_p = parse_instruction(dest_cell.instruction);
        dest = instr_p[R1];
      break;     
   }

//    printf("DEBUG LINE: %d %d %d %d\r\n", instr[0], instr[1], instr[2], instr[3]);

    switch(instr[0]) {
      case DAT:
        if (DEBUG_MODE)
          printf("(%d) NOOP\r\n", pc);
        pc++;
      break;
      case MOV:
        if (DEBUG_MODE)
          printf("(%d) MOV %d, %d\r\n", pc, src, dest);
        c->cells[src] = c->cells[dest];
        pc++;
      break;
      default:
        printf("Error: unknown opcode %d", instr[0]);
        exit(1);
      break;
    }

  }

}

uint8_t *parse_instruction(uint32_t instr) {

  /* 
    according to the redcode spec
    instruction - first 4 bits
    addressing mode for first operand - next 2 bits
    addressing mode for second operand - next 2 bits
    first operand itself - next 2 bits
    second operand itself - next 2 bits

    the masks here are designed to extract out the bits specified
  */

  uint32_t instruction_mask = 0b11110000000000000000000000000000;
  uint32_t addressing1_mask = 0b00001100000000000000000000000000;
  uint32_t addressing2_mask = 0b00000011000000000000000000000000;
  uint32_t operand1_mask =    0b00000000111111111111000000000000;
  uint32_t operand2_mask =    0b00000000000000000000111111111111;

  static uint8_t instructions[5];
  instructions[0] = instr & instruction_mask >> 28;
  instructions[1] = instr & addressing1_mask << 26;
  instructions[2] = instr & addressing2_mask << 24;
  instructions[3] = instr & operand1_mask << 12;
  instructions[4] = instr & operand2_mask << 12;
  printf("%d", instructions[0]);
  return instructions;

}

void main() {

  struct core c;
  core_initialize(&c);
  print_core(c);
  exec(&c);

}
