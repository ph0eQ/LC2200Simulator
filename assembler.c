// Author: Nina Chepovska, Tyler Braden
// LC2200 Simulator
// Assembler

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {

   FILE *input = fopen("input.txt", "rb");
   char token[11];
   char * strings[100];
   int k = 0, index = 0, j = 1; 

   while (!feof(input)) {
      
      char temp[31];
      while (k < 4) {  
         fscanf(input, "%10s", token);      
         strcat(temp, token); 
         strcat(temp, " ");
         k++;
      }  

      if (j < 12) {
         strings[index] = malloc(31*sizeof(char));
         strcpy(strings[index], temp);
      }  
      
      memset(temp,0,30));
      k = 0;
      j++;
      index++;
   }
   
   //int m;
   //for (m = 1; m <= 11; m++) {
   //   printf("%s\n", strings[m - 1]);
   //}

   return 0;
}

