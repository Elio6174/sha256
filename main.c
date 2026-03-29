#include <stdio.h>
#include <string.h>

void printBlock(char[64]);
void printBit(char);
void printBitInt(int);
void printScheduleBlock(char[64][4]);
void schedule(char[]);

int main(){
	char messageBlock[64]= {"hola Mundo"};
  //printBlock(messageBlock);
  
  schedule(messageBlock);
  
  printf("prueba de char a int\n");
  char cadena[4] = {"asdf"};

  //int data = (int)cadena;
  int data;
  memcpy(&data, cadena, 4);
  
  printBitInt(data);
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

void printBitInt(int c){
  for (int i = 31; i >= 0; i--) {
    int k = c >> i; // Desplaza el bit a la posición 0
    if (k & 1)      // Comprueba si el bit es 1
      printf("1");
    else
      printf("0");
  }
   printf("\n");
}

