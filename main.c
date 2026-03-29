#include <stdio.h>
#include <string.h>
#include <sha256.h>

int main(){
	unsigned char messageBlock[55]= {"este es un mensaje cifrado con el algoritmo sha256"};
  messageBlock[strlen(messageBlock)] = 0x80;
  
  schedule(messageBlock, strlen(messageBlock));
  
  //buildHash();


  return 0;
}


