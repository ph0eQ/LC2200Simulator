/**
*Author: Sean Hoyt
**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef p
#define p
#include "processor.h"
#endif

#include <ncurses.h>
#define TRUE 1
#define FALSE 0


void ifetch1(void);
void ifetch2(void);
void ifetch3(void);
void add_op(int*, int*, int*);

static char* MACRO_NAMES[7] = {"ADD", "NAND", "ADDI", "LW", "SW", "BEQ", "JALR"};
static char* REG_NAMES[16] = { "$ZERO", "$AT", "$V0", "$A0", "$A1", "$A2", "$T0", "$T1", "$T2", "$S0","$S1","$S2", "$K0", "$SP", "$FP", "$RA"};

void print_registers(Processor lc2200){
    //char* MACRO_NAMES[10] = {"ADD", "NAND", "ADDI", "LW", "SW", "BEQ", "JALR"};
   // char* REG_NAMES[16] = { "$ZERO", "$AT", "$V0", "$A0", "$A1", "$A2", "$T0", "$T1", "$T2", "$S0", "$S1","$S2", "$K0", "$SP", "$FP", "$RA"};
    //refresh();
    int i = 0;
    printw("********************************************************************************\n");
    printw("********************************************************************************\n");
    printw("*******************************CURRENT STATUS***********************************\n");
    printw("********************************************************************************\n");
    for(i = 0; i < 16; i ++){
        if(i % 2 == 0){
        printw("%s:\t%d\t",REG_NAMES[i],(int)lc2200.registers[i].format.N.value);
        }else {
            printw("%s:\t%d\n",REG_NAMES[i],(int)lc2200.registers[i].format.N.value);
        }
    }
    printw("PC:%d\t\t IR:", lc2200.PC.format.N.value);
    if(lc2200.IR.mode == 'R'){
        print_register(lc2200.IR, 'R');
    }else if(lc2200.IR.mode == 'I'){
        print_register(lc2200.IR, 'I');
    }else if(lc2200.IR.mode == 'J'){
        print_register(lc2200.IR, 'J');
    }else {
        print_register(lc2200.IR, 'N');
    }
    printw("\n");
    printw("********************************************************************************\n");
    printw("********************************************************************************\n");
    printw("\n");

}

void print_register(Register r1, char currentFormat){
  //  char* MACRO_NAMES[10] = {"ADD", "NAND", "ADDI", "LW", "SW", "BEQ", "JALR"};
    //char* REG_NAMES[16] = { "$ZERO", "$AT", "$V0", "$A0", "$A1", "$A2", "$T0", "$T1", "$T2", "$S0", "$S1","$S2", "$K0", "$SP", "$FP", "$RA"};
   
    int i = 0;
   // for(i = 0; i < 16; i++){
    //    printf("REG_NAMES[%d]: %s\n", i, REG_NAMES[i]);
    //}
    
    if(currentFormat == 'R'){
        printw("%s %s %s %s \n", MACRO_NAMES[(int)r1.format.R.opcode], REG_NAMES[(int)r1.format.R.register_1], REG_NAMES[(int)r1.format.R.register_2],REG_NAMES[(int)(r1.format.R.register_3)]);
    }
     if(currentFormat == 'I'){
        printw("%s %s %s %d \n", MACRO_NAMES[r1.format.I.opcode], REG_NAMES[r1.format.I.register_1], REG_NAMES[r1.format.I.register_2],r1.format.I.imm_value);
    }
    if(currentFormat == 'J'){
        printw("%s %s %s \n", MACRO_NAMES[r1.format.J.opcode], REG_NAMES[r1.format.J.register_1], REG_NAMES[r1.format.J.register_2]);
    }
    if(currentFormat == 'N'){
    printw("%d \n",r1.format.N.value);
    }
} 

instruction build_instruction(char* input){
   // char* MACRO_NAMES[7] = {"ADD", "NAND", "ADDI", "LW", "SW", "BEQ", "JALR"};
//char* REG_NAMES[16] = { "$ZERO", "$AT", "$V0", "$A0", "$A1", "$A2", "$T0", "$T1", "$T2", "$S0", "$S1","$S2", "$K0", "$SP", "$FP", "$FA"};
    char input_clone[50] = {0};
    int reg1 =0;
    int reg2 =0;
    int reg3 =0;
    strcpy(input_clone, input);    
    instruction blank;
    char* opcode = strtok(input_clone," ");
    int opcodeNum = getIndex((char**) MACRO_NAMES, 7, opcode);
    char* arg1 = strtok(NULL, ",");
    char* arg2 = strtok(NULL, ",");
    char* arg3 = strtok(NULL, ";");
   // printf("opcode:%s arg1:%s arg2:%s arg3:%s\n", opcode, arg1, arg2, arg3);
    //strip_char(opcode, ' ');
    strip_char(arg1, ' ');
    strip_char(arg2, ' ');
    strip_char(arg3, ' ');
  
    reg1 = getIndex((char**) REG_NAMES, 16, arg1);
    
    reg2 = getIndex((char**) REG_NAMES, 16, arg2);
    reg3 = getIndex((char**) REG_NAMES, 16, arg3);
    
    
    //printf("Reg1: %d, Reg2: %d, Reg3: %d\n", reg1, reg2, reg3);

    strcpy(blank.name, opcode);
   
    if(strcmp(opcode, "ADD") == 0 ||strcmp(opcode, "NAND") == 0){      
        blank.mode = 'R';
        blank.format_type.R.opcode = opcodeNum;
        blank.format_type.R.register_1 = reg1;
        blank.format_type.R.register_2 = reg2;
        blank.format_type.R.register_3 = reg3;
    }else if(strcmp(opcode, "ADDI") == 0 || strcmp(opcode, "LW") == 0 ||
              strcmp(opcode, "SW") == 0 || strcmp(opcode, "BEQ") == 0) {
        blank.mode = 'I';
        blank.format_type.I.opcode = opcodeNum;
        blank.format_type.I.register_1 = reg1;
        blank.format_type.I.register_2 = reg2;
        blank.format_type.I.imm_value = atoi(arg3);
       // printf("Yay imm value parsed as:%d\n", blank.format_type.I.imm_value);
    }else if(strcmp(opcode, "JALR") == 0){
        blank.mode = 'J';
        blank.format_type.J.opcode = opcodeNum;
        blank.format_type.I.register_1 = reg1;
        blank.format_type.I.register_2 = reg2;
    }else {
       //blank.mode = 'N';
       //blank.format_type.N.value = atoi(arg1);
        
       // printf("ERROR INSTRUCTION: %s IS NOT IN LC2200 ISA", opcode);
    }
    //printf("%s \n", blank.name);
        
   // while(*input != ','){
   //     *p1++ = *input++;       
   // }
    //*p1 = '\0';
    
   // printf("%s %s %s %s\n", opcode, arg1, arg2, arg3);

    return blank;
}
void strip_char(char* name, char toRemove){
    char* copy1;
    char* copy2;
    int hasChar = FALSE;
    int j=0;
    for(j=0; j < strlen(name); j++){
        if(name[j] == toRemove)
            hasChar = TRUE;
    }
    if(hasChar == TRUE){
        copy1 = name;
        copy2 = name;
        for(; *copy1; copy1++){
            if(*copy1 != toRemove){
                 *copy2++ = *copy1;
            }
        }
        *copy2 = '\0';
    }
}
int getIndex(char** names, int length, char *name){
    int i =0;
    int indexOfString = 0;
    for(i=0;i < length;i++){
        if(strcmp(names[i], name) == 0)
            indexOfString = i;     
    }
    return indexOfString;
}

void clear_registers(Register* registers){
    int i =0;
    for(i = 0; i < 16; i++){
        registers[i].format.N.value = 0;
    }
}
