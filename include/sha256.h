#ifndef SHA256_H
#define SHA256_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <constants.h>


void printBlock(char[]);
void printBit(char);
void printBitInt(uint32_t);
void printScheduleBlock(uint32_t[64]);
void schedule(unsigned char[], int);
uint32_t w(uint32_t, int);// revisar esta parte puede ser mas eficiente aun en la variable n
uint32_t ch(uint32_t, uint32_t, uint32_t);
uint32_t maj(uint32_t, uint32_t, uint32_t);
void buildHash(uint32_t[64]);
uint32_t bitInvert(uint32_t);


void buildHash(uint32_t scheduleBlock[64]){
    int a=H0, b=H1, c=H2, d=H3, e=H4, f=H5, g=H6, h=H7;
    int z1, z0, choice, temp1, temp2, majority;

    for(int i=0; i<64; i++){
        z1 = w(e, 6)^w(e, 11)^w(e, 25);
        choice = ch(e, f, g);
        temp1 = h+z1+choice+K[i]+scheduleBlock[i];

        z0 = w(a, 2)^w(a, 13)^w(a, 22);
        majority = maj(a,b,c);
        temp2 = majority+z0;

        h=g;
        g=f;
        f=e;
        e=d+temp1;
        d=c;
        c=b;
        b=a;
        a = temp1 + temp2;


        printf("a: ");
        printBitInt(a);
        printf("\n");

        printf("b: ");
        printBitInt(b);
        printf("\n");

        printf("c: ");
        printBitInt(c);
        printf("\n");

        printf("d: ");
        printBitInt(d);
        printf("\n");

        printf("e: ");
        printBitInt(e);
        printf("\n");

        printf("f: ");
        printBitInt(f);
        printf("\n");

        printf("g: ");
        printBitInt(g);
        printf("\n");

        printf("h: ");
        printBitInt(h);
        printf("\n\n");

    }
    printf("a+H0: ");
    a = a+H0;
    printBitInt(a);
    printf("\n\n");


    printf("b+H1: ");
    b = b+H1;
    printBitInt(b);
    printf("\n\n");

    unsigned char sha2565[32];


    

    int i =0;
    //for(int i = 0; i < 4; i++){
      sha2565[i]     = (char)(a >> 24);
      sha2565[i + 1] = (char)(a >> 16);
      sha2565[i + 2] = (char)(a >> 8);
      sha2565[i + 3] = (char)(a >> 0);
      sha2565[i+4]     = (char)(b >> 24);
      sha2565[i + 5] = (char)(b >> 16);
      sha2565[i + 6] = (char)(b >> 8);
      sha2565[i + 7] = (char)(b >> 0);
    //}
    //indice += sizeof(int);

    /*
    printf("sha de los 4 primeros bytes %02x\n", sha2565);
    printf("sha de los 4 primeros bytes %02x\n", sha2565[0]);
    printf("sha de los 4 primeros bytes %02x\n", sha2565[1]);
    printf("sha de los 4 primeros bytes %02x\n", sha2565[2]);
    printf("sha de los 4 primeros bytes %02x\n", sha2565[3]);*/

    for(int i = 0; i < 8; i++) {
        printf("%02X ", sha2565[i]);
    }
    /*
    z1 = w(e, 6)^w(e, 11)^w(e, 25);
    printf("salida: ");
    printBitInt(z1);
    printf("\n\n");


    choice = ch(e, f, g);
    printf("salida: ");
    printBitInt(choice);
    printf("\n");


    temp1 = h+z1+choice+K[0]+scheduleBlock[0];
    printf("salida: ");
    printBitInt(temp1);
    printf("\n");

    /*printf("bit a: ");
    printBitInt(e);
    printf("\n");
    printf("bit 6: ");
    printBitInt(w(e, 6));
    printf("\n");*/
    

}




uint32_t w(uint32_t row, int n){
  return (row>>n)|(row<<(32-n)); 
}

uint32_t ch(uint32_t x, uint32_t y, uint32_t z){
    return (x & y)^(~x & z);
}

uint32_t maj(uint32_t x, uint32_t y, uint32_t z){
    return (x & y) ^ (x & z) ^ (y & z);
}

uint32_t bitInvert(uint32_t bit){
    uint32_t res = 0;
    
    for (int i = 0; i < 32; i++){
        res <<= 1;
        res |= (bit & 1);
        bit >>= 1;
    }
    return res;
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

  int out1=0, out2=0;
  for(int i=16; i<64; i++){
    out1 = w(scheduleBlock[i-15], 7) ^ w(scheduleBlock[i-15], 18) ^ (scheduleBlock[i-15]>>3);
    out2 = w(scheduleBlock[i-2], 17) ^ w(scheduleBlock[i-2], 19) ^ (scheduleBlock[i-2]>>10);
    scheduleBlock[i] = scheduleBlock[i-16] + out1 + scheduleBlock[i-7] + out2;
  }
  //printScheduleBlock(scheduleBlock);

  buildHash(scheduleBlock);
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