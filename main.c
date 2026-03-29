#include <stdio.h>
#include <string.h>

void printBlock(char[64]);
void printBit(char);
void printBitInt(int);
void printScheduleBlock(int[64]);
void schedule(char[]);

int main(){
	char messageBlock[64]= {"hola Mundo"};
  //printBlock(messageBlock);
  
  schedule(messageBlock);
  
  //printf("prueba de char a int\n");
  //char cadena[4] = {"asdf"};

  //int data = (int)cadena;
  
  //int data;
  //memcpy(&data, cadena, 4);
  
  //printBitInt(data);
  return 0;
}

void schedule(char block[]){
  int scheduleBlock[64];
  char temp[4];

  for(int i=0; i<10; i++){
    for(int k=0; k<4;k++){
      if(i<16){
        temp[k]=block[4*i+k];
        //scheduleBlock[i][k]= block[4*i +k];
    }else
        temp[k]=0;
    }
    //printf("%s\n", temp);i
    scheduleBlock[i]=(temp[0] << 24)|(temp[1] << 16)|(temp[2] << 8)|(temp[3]);
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

void printScheduleBlock(int scheduleBlock[64]){
  for(int i=0; i<10; i++){
    printBitInt(scheduleBlock[i]);
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

