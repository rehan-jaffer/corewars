/* Instruction Set */

#define DAT 0
#define MOV 1
#define ADD 2
#define SUB 3
#define MUL 4
#define DIV 5
#define MOD 6
#define JMP 7
#define JMZ 8
#define JMN 9
#define DJN 10
#define SPL 11
#define CMP 12
#define SEQ 13
#define SNE 14
#define SLT 15
#define LDP 16
#define STP 17
#define NOP 18

/* Addressing modes */
#define IMMEDIATE 0
#define RELATIVE 1
#define INDIRECT 2

/* instruction elements */
#define OP 0
#define MODE1 1
#define MODE2 2
#define R0 3
#define R1 4
