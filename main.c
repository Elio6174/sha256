#include <stdio.h>
#include <string.h>
#include <sha256.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

  if(argc < 1){
    printf("faltan argumentos\n");
    return 1;
  }
  

  //unsigned char messageBlock[55];
  

  //int largo = strlen(argv[1]);
  //if(largo > 55){
  //  printf("mensaje mayor a 55 bytes se recortara\n");
  //  largo = 55;
  //}

  //memset(messageBlock, 0, 55);
  //memcpy(messageBlock, argv[1], largo);
  //printMessage(messageBlock);


  //printf("%s\n",messageBlock);
  
  
  unsigned char *sha256Out = sha256(argv[1]);

  //for(int i = 0; i < 32; i++) {
  //  printf("%02X", sha256Out[i]);
  //}
  printf("\n");
  return 0;
}
