#include <stdint.h>

#define CORE_SIZE 4096
#define CORE_WIDTH 64

struct core {
  uint32_t cells[CORE_SIZE];
  uint32_t p1_start;
  uint32_t p2_start;
};

struct program {
  uint32_t instructions[24];
};

void exec_core(struct core *c, struct program p1, struct program p2);

int main() {

  struct core c;
  struct program p1;
  struct program p2;
  initialize_core(&c);
  p1.instructions[0] = 3;
  p1.instructions[1] = 1;
  p1.instructions[2] = 1;
  p1.instructions[3] = 1;
  exec_core(&c, p1, p2);

}

int initialize_core(struct core *c) {

  int x = 0;

  for(x=0;x<CORE_SIZE;x++) {
    c->cells[x] = 0;
  }

  return 0;

}

void exec_core(struct core *c, struct program p1, struct program p2) {

  uint32_t p1_loc = 1;
  uint32_t p2_loc = 2;
  memcpy(&c->cells[p1_loc], &p1.instructions, sizeof(p1.instructions));
  memcpy(&c->cells[p2_loc], &p2.instructions, sizeof(p2.instructions));
  c->p1_start = p1_loc;
  c->p2_start = p2_loc;
  print_core(c);
  return 0;

}

void print_core(struct core *c) {

  int x = 0;
  for (x=0;x<CORE_SIZE;x++) {

    printf("%d ", c->cells[x]);
    if (x % CORE_WIDTH == 0)
      printf("\r\n");

  }

  return;

}
