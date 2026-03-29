#include <stdio.h>
#include <string.h>
#include <sha256.h>

int main(){
	unsigned char messageBlock[55]= {"hola Mundo"};
  messageBlock[strlen(messageBlock)] = 0x80;
  
  schedule(messageBlock, strlen(messageBlock));
  
  return 0;
}


