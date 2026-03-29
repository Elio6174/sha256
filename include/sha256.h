#ifndef SHA256_H
#define SHA256_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>


void printBlock(char[]);
void printBit(char);
void printBitInt(uint32_t);
void printScheduleBlock(uint32_t[64]);
void schedule(unsigned char[], int);
int w(uint32_t, int);// revisar esta parte puede ser mas eficiente aun en la
                    // variable n


int w(uint32_t row, int n){
  return (row>>n)|(row<<(32-n)); 
}

void schedule(unsigned char block[], int len){
  uint32_t scheduleBlock[64];
  unsigned char temp[4];

  for(int i=0; i<64; i++){
    for(int k=0; k<4;k++){
      if(i<14)
        temp[k]=block[4*i+k];
      else
        temp[k]=0;
    }
    scheduleBlock[i]=(temp[0] << 24)|(temp[1] << 16)|(temp[2] << 8)|(temp[3]);
  }
  scheduleBlock[15] = (len-1)*8;

  //printBitInt(scheduleBlock[15]);

  int out1=0, out2=0;
  for(int i=16; i<64; i++){
    //printf("iteracion %d\n", i);
    out1 = w(scheduleBlock[i-15], 7) ^ w(scheduleBlock[i-15], 18) ^ (scheduleBlock[i-15]>>3);
    //printf("out1:\n");
    //printBitInt(out1);
    //printf("\n");
    out2 = w(scheduleBlock[i-2], 17) ^ w(scheduleBlock[i-2], 19) ^ (scheduleBlock[i-2]>>10);
    //printf("out2:\n");
    //printBitInt(out2);
    //printf("\n");
    scheduleBlock[i] = scheduleBlock[i-16] + out1 + scheduleBlock[i-7] + out2;
    //printf("salida:\n");
    //printBitInt(scheduleBlock[i]);
    //printf("\n\n");


    //printBitInt(out2);
    //printf("\nSalida\n");
    //printf("\n");
    //printf("\n");

  }

  /*int i = 18;

  
  printf("w16: ");
  printBitInt(scheduleBlock[i-2]);
  printf("\n");

  printf("w16: right rotate 17: ");
  printBitInt(w(scheduleBlock[i-2], 17));
  printf("\n");

  printf("w16: right rotate 19: ");
  printBitInt(w(scheduleBlock[i-2], 19));
  printf("\n");

  printf("w16: right shift   3: ");
  printBitInt(scheduleBlock[i-2]>>10);
  printf("\n");

  
  //printBitInt(w(scheduleBlock[1], 18));
  //printf("\n");
  //printBitInt(scheduleBlock[1]>>3);
  //printf("\n");*/

  printScheduleBlock(scheduleBlock);
}



void printBlock(char block[]){
  for(int i = 0; i < 16; i++){
    for(int k = 0; k < 4; k++){
      printBit(block[4*i + k]);
      printf(" ");
    }
    printf("\n");
  }
  printf("\n");
}

void printScheduleBlock(uint32_t scheduleBlock[64]){
  for(int i=0; i<64; i++){
    printf("w%d\t  ", i);
    printBitInt(scheduleBlock[i]);
    printf("\n");
  }
}

void printBit(char c){
  for(int i = 7; i >= 0; i--){
    int bit = (c >> i) & 1;
    printf("%d", bit);
  }
}

void printBitInt(uint32_t c){
  for (int i = 31; i >= 0; i--) {
    if ((c>>i) & 1)
      printf("1");
    else
      printf("0");
  }
}

#endif // SHA256_H