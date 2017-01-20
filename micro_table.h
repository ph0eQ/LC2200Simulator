/**
*Author: Sean Hoyt
**/
#include "processor.h"

typedef enum MICRO_STATES{ADD1, ADD2, ADD3, NAND1, NAND2, NAND3, ADDI1, ADDI2, ADDI3,LW1, LW2, LW3,LW4,SW1, SW2, SW3, SW4, BEQ1, BEQ2, BEQ3, BEQ4, BEQ5, BEQ6,JALR1, JALR2, DONE} MICRO_STATES;


typedef void (*func)(int*, int*, int);
typedef struct micro{
    MICRO_STATES next;
    func micro_op;
}micro;
typedef struct MAR {
    instruction mem[1000];
    int size;
    int start;
    int last_index;
}MAR;
void add1(int*, int*, int);
void add2(int*, int*, int);
void add3(int*, int*, int);
void nand1(int*, int*, int);
void nand2(int*, int*, int);
void nand3(int*, int*, int);
void addi1(int*, int*, int);
void addi2(int*, int*, int);
void addi3(int*, int*, int);
void lw1(int*, int*, int);
void lw2(int*, int*, int);
void lw3(int*, int*, int);
void lw4(int*, int*, int);
void sw1(int*, int*, int);
void sw2(int*, int*, int);
void sw3(int*, int*, int);
void sw4(int*, int*, int);
void beq1(int*, int*, int);
void beq2(int*, int*, int);
void beq3(int*, int*, int);
void beq4(int*, int*, int);
void beq5(int*, int*, int);
void beq6(int*, int*, int);
void jalr1(int*, int*, int);
void jalr2(int*, int*, int);

