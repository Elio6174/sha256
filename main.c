#include <stdio.h>
#include <string.h>
#include <sha256.h>
#include <stdlib.h>

void printMessage(unsigned char[]);

int main(int argc, char *argv[]){

  if(argc < 1){
    return 1;
  }
  
  //printf("Mensaje impreso como parametro %s\n", argv[1]);
	
  unsigned char messageBlock[55];
  memcpy(messageBlock, argv[1], 55);
  
  //printMessage(messageBlock);

  for(int k = 0; k < 55; k++){
    printf("%c", messageBlock[k]);
  }
  printf("\n");




  unsigned char *sha256Out = sha256(messageBlock);

  for(int i = 0; i < 32; i++) {
    printf("%02X", sha256Out[i]);
  }
  printf("\n");
  return 0;
}

void printMessage(unsigned char message[]){
  for(int i = 0; i< 55; i++){
    printf("%s", message[i]);
  }
  printf("\n");
}


