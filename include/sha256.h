#ifndef SHA256_H
#define SHA256_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <constants.h>


void printBlock(char[]);
void printBit(char);
void printBitInt(uint32_t);
void printScheduleBlock(uint32_t[64]);
unsigned char* sha256(unsigned char[]);
uint32_t w(uint32_t, int);// revisar esta parte puede ser mas eficiente aun en la variable n
uint32_t ch(uint32_t, uint32_t, uint32_t);
uint32_t maj(uint32_t, uint32_t, uint32_t);
unsigned char* buildHash(uint32_t[64]);


unsigned char*
buildHash(uint32_t scheduleBlock[64]){
  uint32_t v[8] = {H0, H1, H2, H3, H4, H5, H6, H7};
  int z1, z0, choice, temp1, temp2, majority;

  for(int i=0; i<64; i++){
    z1 = w(v[4], 6)^w(v[4], 11)^w(v[4], 25);
    choice = ch(v[4], v[5], v[6]);
    temp1 = v[7]+z1+choice+K[i]+scheduleBlock[i];

    z0 = w(v[0], 2)^w(v[0], 13)^w(v[0], 22);
    majority = maj(v[0],v[1],v[2]);
    temp2 = majority+z0;

    v[7]=v[6];
    v[6]=v[5];
    v[5]=v[4];
    v[4]=v[3]+temp1;
    v[3]=v[2];
    v[2]=v[1];
    v[1]=v[0];
    v[0] = temp1 + temp2;
  }

  unsigned char* sha256 = (unsigned char*)malloc(32 * sizeof(unsigned char));
  if (sha256 == NULL) return NULL;

  for(int i = 0; i < 8; i++){
    v[i] = v[i]+H[i];
    for(int k = 0; k<4; k++){
      sha256[(i*4)+k]=(char)(v[i] >> (24-8*k));
    }
  }
  return sha256;
}


uint32_t 
w(uint32_t row, int n){
  return (row>>n)|(row<<(32-n)); 
}


uint32_t 
ch(uint32_t x, uint32_t y, uint32_t z){
    return (x & y)^(~x & z);
}


uint32_t 
maj(uint32_t x, uint32_t y, uint32_t z){
    return (x & y) ^ (x & z) ^ (y & z);
}


unsigned char*
sha256(unsigned char block[]){
  uint32_t scheduleBlock[64];
  unsigned char temp[4];
  block[strlen(block)] = 0x80;
  int len = strlen(block);

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

  int out1=0, out2=0;
  for(int i=16; i<64; i++){
    out1 = w(scheduleBlock[i-15], 7) ^ w(scheduleBlock[i-15], 18) ^ (scheduleBlock[i-15]>>3);
    out2 = w(scheduleBlock[i-2], 17) ^ w(scheduleBlock[i-2], 19) ^ (scheduleBlock[i-2]>>10);
    scheduleBlock[i] = scheduleBlock[i-16] + out1 + scheduleBlock[i-7] + out2;
  }
  //printScheduleBlock(scheduleBlock);

  return buildHash(scheduleBlock);
}


void 
printBlock(char block[]){
  for(int i = 0; i < 16; i++){
    for(int k = 0; k < 4; k++){
      printBit(block[4*i + k]);
      printf(" ");
    }
    printf("\n");
  }
  printf("\n");
}


void 
printScheduleBlock(uint32_t scheduleBlock[64]){
  for(int i=0; i<64; i++){
    printf("w%d\t  ", i);
    printBitInt(scheduleBlock[i]);
    printf("\n");
  }
}


void 
printBit(char c){
  for(int i = 7; i >= 0; i--){
    int bit = (c >> i) & 1;
    printf("%d", bit);
  }
}


void 
printBitInt(uint32_t c){
  for (int i = 31; i >= 0; i--) {
    if ((c>>i) & 1)
      printf("1");
    else
      printf("0");
  }
}

#endif // SHA256_H