/**
*Author: Sean Hoyt
**/

#include <stdlib.h>
#include <stdio.h>
//#include "processor.h"
#include "micro_table.h"
#include <ncurses.h>
#include <string.h> 
//TO DO:
// Finish micro table, make function for loading all instructions into mar
void print_bin(int val, int width);
char *my_itoa(int val, int base,int width);
void add_to_MAR(MAR *mar, char *input[]);
int get_size(char *input[]);
void print_MAR(MAR mar);
                                  //add1        //add2          //add3
static   micro micro_table[7][3] = { {{ADD2, add1}, {ADD3, add2}, {DONE, add3}},
                                 //nand1        //nand2          //nand3
                                {{NAND2, nand1}, {NAND3, nand2}, {DONE, nand3}},
                                //addi1        //addi2          //addi3
                                {{ADDI2, addi1}, {ADDI3, addi2}, {DONE, addi3}},
                                //lw1
			                    {{LW2, lw1}, {LW3,lw2}, {DONE, lw3}},
			                    //sw1
			                   {{SW2, sw1}, {SW3, sw2}, {DONE, sw3}},
			                //beq1
			     		     {{BEQ2, beq1}, {DONE, beq2}},
		                    //jalr1
		                       {{JALR2, jalr1}, {DONE, jalr2}},
                              };
                              
void exec_processor(char** queue);
void load_and_run();
//int main(void){
    //static char* queue[] ={"ADD $T1, $T2, $T0;","ADD $S2, $SP, $RA;","ADD $AT, $A2, $FP;","ADD $V0, $K0, $FP;", "ADDI $AT, $T1, 100;","SW $AT, $ZERO, 0;", "LW $V0, $ZERO, 0};" ,"BEQ $S0, $V0, 55;"};
    // exec_processor((char**)queue);
  //  return 0;
        //}
//}
int main(void){
   FILE *input = fopen("input.txt", "r");
   char token[11];
   static char * strings[100];
   int k = 0, index = 0, j = 1; 
   while (!feof(input)) {   
      char temp[31] = {0};
      while (k < 4) {  
         fscanf(input, "%10s", token);      
         strcat(temp, token); 
         strcat(temp, " ");
         k++;
      }  

      if (j < 14) {
         strings[index] = malloc(31);
         strcpy(strings[index], temp);
      }  
      
      memset(temp,0,30);
      k = 0;
      j++;
      index++;
   }
  exec_processor(strings);
   fclose(input);
   return 0;
 }               

void exec_processor(char** queue){

    initscr();
        //scrollok(stdscr, TRUE);
       // scroll(stdscr);
       // idlok(stdscr, TRUE);


    int imm = 0;
    int A = 0;
    int B = 0;
    Processor lc2200;
    lc2200.PC.format.N.value = 0;
    //char* queue1[] ={"ADD $T1, $T2, $T0;","ADD $S2, $SP, $RA;","ADD $AT, $A2, $FP;","ADD $V0, $K0, $FP;", "ADDI $AT, $T1, 100;","SW $AT, $ZERO, 19;", "LW $V0, $ZERO, 0};" ,"BEQ $S0, $V0, 55;"};
    
    MAR magmar;
    magmar.size = 1000;
    add_to_MAR(&magmar, queue); 

    clear_registers(lc2200.registers);
    int* Rx;
    int* Ry;
    int* Rz;
    int i  = 0;
    
   //for(i=0; i < 16; i++){
    //   lc2200.registers[i].format.N.value = rand() % 54;
   // }
    lc2200.IR.format.N.value =0;
   // print_registers(lc2200);
    
    MICRO_STATES state = 0;

    //test of add macro state
    for(i=0; i < 50;i++){
        //lc2200.IR.format.R = op_queue[i].format_type.R;
       // if(i == 0){
       //magmar.start = magmar.mem[i].format_type.N.value;
       // i++;
      //  }
        lc2200.IR.format =magmar.mem[i].format_type;
        lc2200.IR.mode = magmar.mem[i].mode;
         ++lc2200.PC.format.N.value;
        A=0;
        B=0;
        state =0;
        if(magmar.mem[i].mode == 'R'){
           Rx = &lc2200.registers[magmar.mem[i].format_type.R.register_1].format.N.value;
            Ry = &lc2200.registers[magmar.mem[i].format_type.R.register_2].format.N.value;
            Rz = &lc2200.registers[magmar.mem[i].format_type.R.register_3].format.N.value;
            micro_table[magmar.mem[i].format_type.R.opcode][0].micro_op(&A, Ry, 0);
            //state = micro_table[magmar.mem[i].format_type.R.opcode][state].next;
            micro_table[magmar.mem[i].format_type.R.opcode][1].micro_op(&B, Rz, 0);
          //  state = micro_table[magmar.mem[i].format_type.R.opcode][state].next;
            micro_table[magmar.mem[i].format_type.R.opcode][2].micro_op(Rx, &A, B);         
            print_registers(lc2200);
            refresh();
            mvprintw(0,0,"Press any key to continue\n");
           refresh();
            getch();
            state = 0;          
        }else if(magmar.mem[i].mode == 'I'){
               if(magmar.mem[i].format_type.I.opcode == ADDI){
                
                    Rx = &lc2200.registers[magmar.mem[i].format_type.I.register_1].format.N.value;
                    Ry = &lc2200.registers[magmar.mem[i].format_type.I.register_2].format.N.value;
                    imm = magmar.mem[i].format_type.I.imm_value;
                    micro_table[magmar.mem[i].format_type.I.opcode][0].micro_op(&A, Rx, 0);
                    micro_table[magmar.mem[i].format_type.I.opcode][1].micro_op(&B, Ry, imm);
                    micro_table[magmar.mem[i].format_type.I.opcode][2].micro_op(Rx, &A, B);
                    print_registers(lc2200);
                    refresh();  
                    mvprintw(0,0,"Press any key to continue\n");
                    getch();
                }else if(magmar.mem[i].format_type.I.opcode == LW 
                                    || magmar.mem[i].format_type.I.opcode == SW){
              
                    Rx = &lc2200.registers[magmar.mem[i].format_type.I.register_1].format.N.value;
                    Ry = &lc2200.registers[magmar.mem[i].format_type.I.register_2].format.N.value;
                    imm = magmar.mem[i].format_type.I.imm_value;
                    micro_table[magmar.mem[i].format_type.I.opcode][0].micro_op(&A, Ry, 0);
                    micro_table[magmar.mem[i].format_type.I.opcode][1].micro_op(&B, 0, imm);
                    Ry = &magmar.mem[A+B].format_type.N.value;
                    micro_table[magmar.mem[i].format_type.I.opcode][2].micro_op(Rx, Ry, 0);
                    print_registers(lc2200);
                    refresh();
                    mvprintw(0,0,"Press any key to continue");
                    getch();       
                }else {
             
                    Rx = &lc2200.registers[magmar.mem[i].format_type.I.register_1].format.N.value;
                    Ry = &lc2200.registers[magmar.mem[i].format_type.I.register_2].format.N.value;
                    imm = magmar.mem[i].format_type.I.imm_value;
                    micro_table[magmar.mem[i].format_type.I.opcode][0].micro_op(&A, Rx, 0);
                    micro_table[magmar.mem[i].format_type.I.opcode][1].micro_op(&B, Ry, imm);
                    if((A - B) == 0){
                        lc2200.PC.format.N.value += imm;
                        i+= imm;
                    }
                    print_registers(lc2200);
                    refresh();
                    mvprintw(0,0,"Press any key to continue");
                    getch();       
                
                }
          }else if(magmar.mem[i].mode == 'J'){
                    Rx = &lc2200.registers[magmar.mem[i].format_type.I.register_1].format.N.value;
                    Ry = &lc2200.registers[magmar.mem[i].format_type.I.register_2].format.N.value;
                    Rz = &lc2200.PC.format.N.value;
                    imm = magmar.mem[i].format_type.I.imm_value;
                    micro_table[magmar.mem[i].format_type.I.opcode][0].micro_op(Rz, Ry, 0);
                    micro_table[magmar.mem[i].format_type.I.opcode][1].micro_op(Rz, Rx, 0);
                    i = *Rz;
                    print_registers(lc2200);
                    refresh();
                   mvprintw(1,0,"\n Press any key to continue\n");
                   getch();     
          
         }
     }
    //int_registers(lc2200);
    refresh();
    getch();
    endwin();
        print_MAR(magmar);       
} 

      
void add1(int* A, int* regY, int imm_value){
    *A = *regY;
    //printf("END of ADD1\n");
}
void add2(int* B, int* regZ, int imm_value){
    *B = *regZ;
   // printf("END of ADD2\n");
}
void add3(int* regX, int* A, int sum){
    *regX = *A + sum;
   // printf("END of ADD3\n");
}
void nand1(int* A, int* regY, int imm_value){
    *A = *regY;
    //printf("END of NAND1\n");
}
void nand2(int* B, int* regZ, int imm_value){
    *B = *regZ;
    //printf("END of NAND2\n");
}
void nand3(int* regX, int* A, int sum){
    *regX = ~((*A & sum));
   // printf("END of NAND3\n");
}
void addi1(int* A, int* regY, int imm_value){
    *A = *regY;
}
void addi2(int* B, int* regZ, int imm_value){  
    *B = *regZ +imm_value;
}
void addi3(int* regY, int* A, int sum){
    *regY = sum;
}
void lw1(int* A, int* regY, int imm_value){
    *A = *regY;
}
void lw2(int* B, int* regY, int imm_value){  
    *B = imm_value;
}
void lw3(int* regX, int* regY, int sum){
    *regX =  *regY;
}
void sw1(int* A, int* regY, int imm_value){
    *A = *regY;
}
void sw2(int* B, int* regY, int imm_value){  
    *B = imm_value;
}
void sw3(int* regX, int* regY, int sum){
    *regY =  *regX;
}
void beq1(int* A, int* regX, int imm_value){
    *A = *regX;
    //printf("END of ADD1\n");
}
void beq2(int* B, int* regY, int imm_value){
    *B = *regY;
   // printf("END of ADD2\n");
}
void jalr1(int* regZ, int* regY, int imm_value){
    *regY = *regZ;
    //printf("END of ADD1\n");
}
void jalr2(int* regZ, int* regX, int imm_value){
    *regZ = *regX;
   // printf("END of ADD2\n");
}
void print_bin(int val,int width){
    char *bin;
    bin = my_itoa(val,2,width);
    if(width == 5){
       printf("%4s", bin);
     }else if(width == 33){
        printf("%32s", bin);
     }else if(width == 17){
        printf("%16s", bin);
     }else {
        printf("%20s", bin);
     }
 }
char* my_itoa(int val, int base,int width){
    static char buf_s[5] = {0};
    static char buf_l[21] ={0};
    static char buf_m[17] = {0};
    static char buf_x[33] = {0};
    char *select;
    int i =0;
    if(width == 5){
        select = buf_s;
        i = 4;
    }else if (width == 33){
        select = buf_x;
        i = 32;
    }else if(width == 17){
        select = buf_m;
        i = 16;   
    }else {
        select = buf_l;
        i = 20;
    } 
    for(; val >=0 && i; --i, val /= base){ 
             select[i] = "0123456789abcdef"[val % base];      
    }
    return &select[i+1];
    
}
int get_size(char *input[]){
    int i=0;
    while(input[i] != NULL){
        i++;
    }
    return i;
}
void add_to_MAR(MAR *mar, char *input[]){
    int size = get_size(input);
    int i=0;
    for(i=0; i < size; i++){
        mar->mem[i] = build_instruction(input[i]);
    }
}
void print_MAR(MAR mar){
    int i =0;

    printf("ADDRESS\tOP  R1  R2  R3  IMM_VAL <-- instruction\n");
    printf("       \t(Value) <--------------------------Data\n");
    for(i=0; i < 100; i++){
            printf("%d\t", i+mar.start);
        if(mar.mem[i].mode != 'N'){
            if(mar.mem[i].format_type.R.opcode == 0){
                printf("%.4s","0000");
            }else{
                print_bin(mar.mem[i].format_type.R.opcode, 5);
                //printf("\t");
            }
            if(mar.mem[i].format_type.R.register_1 == 0){
                printf("%.4s","0000");
            }else {
                print_bin(mar.mem[i].format_type.R.register_1, 5);
                //printf("\t");
            }
            if(mar.mem[i].format_type.R.register_2 == 0){
                printf("%.4s", "0000");
            }else {
                print_bin(mar.mem[i].format_type.R.register_2, 5);
               // printf("\t");
            }
            if(mar.mem[i].mode == 'R'){
                if(mar.mem[i].format_type.R.register_3 == 0){
                    printf("%.4s", "0000");
                 }else {
                    print_bin(mar.mem[i].format_type.R.register_3, 5);
                  //  printf("\t");
                 }
                 if(mar.mem[i].format_type.R.garbage == 0){
                    printf("%.16s", "0000000000000000");
                    }else{
                         print_bin(mar.mem[i].format_type.R.garbage, 17);
                    }
            }else {
               // printf("\t");
               if(mar.mem[i].format_type.I.imm_value == 0){
                    printf("%.20s", "00000000000000000000");
                 }else {
                print_bin(mar.mem[i].format_type.I.imm_value, 21);
                  //  printf("\t");
                 }
            }
            printf("\n");
       }else {
                print_bin(mar.mem[i].format_type.N.value, 33);
            }
        
        
    }
}
void load_and_run(){
   // GtkFileChooser *f_chooser;/
      FILE *input = fopen("input.txt", "r");
   char token[11];
   static char * strings[100];
   int k = 0, index = 0, j = 1; 

   while (!feof(input)) {
      
      char temp[31] = {0};
      while (k < 4) {  
         fscanf(input, "%10s", token);      
         strcat(temp, token); 
         strcat(temp, " ");
         k++;
      }  

      if (j < 12) {
         strings[index] = malloc(31);
         strcpy(strings[index], temp);
      }  
      
      memset(temp,0,30);
      k = 0;
      j++;
      index++;
   }
  exec_processor(strings);
   int i =0;
   for(i =0; i < 12; i++){
        printf("%s \n", strings[i]);
   }
   fclose(input);
}
