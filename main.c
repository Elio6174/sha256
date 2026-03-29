#include <stdio.h>
#include <string.h>

void printBlock(char[]);
void printBit(char);
void printBitInt(int);
void printScheduleBlock(int[64]);
void schedule(char[], int);
int w(int, int);// revisar esta parte puede ser mas eficiente aun en la
                // variable n

int main(){
	char messageBlock[55]= {"hola Mundo"};
  messageBlock[strlen(messageBlock)] = 0x80;
  
  
  schedule(messageBlock, strlen(messageBlock));
  printBlock(messageBlock);
  
  return 0;
}


int w(int row, int n){
  return (row>>n)|(row<<(32-n)); 
}

void schedule(char block[], int len){
  int scheduleBlock[64];
  //block[len+1] = 0x80;
  char temp[4];

  for(int i=0; i<64; i++){
    for(int k=0; k<4;k++){
      if(i<16){
        temp[k]=block[4*i+k];
    }else
        temp[k]=0;
    }
    scheduleBlock[i]=(temp[0] << 24)|(temp[1] << 16)|(temp[2] << 8)|(temp[3]);
  }
  scheduleBlock[15] = len*8;
  //scheduleBlock[11] = 128;
/*
  int out1=0, out2=0;
  for(int i=16; i<18; i++){
    printf("iteracion: %d\n", i);
    printf("w1\n");
    printBitInt(w(scheduleBlock[i-15],18));

    //out1 = w(scheduleBlock[i-15], 7) ^ w(scheduleBlock[i-15], 18) ^ (scheduleBlock[i-15]>>3);
    //printBitInt(out1);
    printf("\nw2\n");
    //out2 = w(scheduleBlock[i-2], 17) ^ w(scheduleBlock[i-2], 19) ^ (scheduleBlock[i-2]>>10);
    //scheduleBlock[i] = scheduleBlock[i-16] + out1 + scheduleBlock[i-7] + out2;

    //printBitInt(out2);
    //printf("\nSalida\n");
    //printBitInt(scheduleBlock[i]);
    //printf("\n");
    //printf("\n");

  }

  //printBitInt(w(scheduleBlock[1], 7));
  //printf("\n");
  //printBitInt(w(scheduleBlock[1], 18));
  //printf("\n");
  //printBitInt(scheduleBlock[1]>>3);
  //printf("\n");
*/
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

void printScheduleBlock(int scheduleBlock[64]){
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

void printBitInt(int c){
  for (int i = 31; i >= 0; i--) {
    if ((c>>i) & 1)
      printf("1");
    else
      printf("0");
  }
}

