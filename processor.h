/**
*Author: Sean Hoyt
**/
#include <stdlib.h>
#include <stdio.h>

typedef enum MACRO_STATE{ADD, NAND, ADDI, LW, SW, BEQ, JALR} MACRO_STATE;
typedef enum REGS {$ZERO, $AT, $V0, $A0, $A1, $A2, $T0, $T1, $T2, $S0, $S1, $S2, $K0, $SP, $FP, $RA} REGS;

void strip_char(char* name, char toRemove);
int getIndex(char** names, int length, char *name);
typedef struct r_type{
    //MACRO_STATE NAME;
    unsigned int opcode:4;
    unsigned int register_1:4;
    unsigned int register_2:4;
    unsigned int register_3:4;
    unsigned int garbage:16;
    
} r_type;
typedef struct i_type{
    //MACRO_STATE NAME;
    unsigned int opcode:4;
    unsigned int register_1:4;
    unsigned int register_2:4;
    int imm_value:20;
} i_type;
typedef struct j_type{
    //MACRO_STATE NAME;
    unsigned int opcode:4;
    unsigned int register_1:4;
    unsigned int register_2:4;
    unsigned int imm_value:20;
} j_type;
typedef struct no_type{
    int value;
} no_type;
typedef union instruction_format {
    r_type R;
    i_type I;
    j_type J;
    no_type N;
} instruction_format;

typedef struct Register{
    char mode;
    instruction_format format;
} Register;

typedef struct Processor{
    Register PC;
    Register IR;
    Register registers[16];
} Processor;
void print_register(Register r1, char currentFormat);
typedef struct instruction{
    char name[10];
    char mode;
    instruction_format format_type;
} instruction;
instruction build_instruction(char* input); 
void print_registers(Processor lc2200);
void clear_registers(Register* registers);

