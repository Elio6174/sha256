#include <stdio.h>
    
void printBlock(char[64]);
void printBit(char);
void printScheduleBlock(char[64][4]);
void schedule(char[]);

int main(){
	char messageBlock[64]= {"hola Mundo"};
  //printBlock(messageBlock);
  
  schedule(messageBlock);
  return 0;
}

void schedule(char block[]){
  char scheduleBlock[64][4];
  
  for(int i=0; i<64; i++){
    for(int k=0; k<4;k++){
      if(i<16)
        scheduleBlock[i][k]= block[4*i +k];
      else
        scheduleBlock[i][k]= 0;
    }
  }

  printScheduleBlock(scheduleBlock);
}


void printBlock(char block[]){
  for(int i = 0; i < 10; i++){
    for(int k = 0; k < 4; k++){
      printBit(block[4*i + k]);
      printf(" ");
    }
    printf("\n");
  }
  printf("\n");
}

void printScheduleBlock(char scheduleBlock[64][4]){
  for(int i=0; i<64; i++){
    for(int k=0; k<4; k++){
      printBit(scheduleBlock[i][k]);
    }
    printf("\n");
  }
  printf("\n");
}

void printBit(char c){
  for(int i = 7; i >= 0; i--){
    int bit = (c >> i) & 1;
    printf("%d", bit);
  }
}
