#include <stdio.h>
#include <string.h>
#include <sha256.h>

int main(){
	unsigned char messageBlock[55]= {"hola mundo"};
  printf("Mensaje:%s\n", messageBlock);
  
  unsigned char *sha256Out = sha256(messageBlock);

  for(int i = 0; i < 32; i++) {
    printf("%02X", sha256Out[i]);
  }
  return 0;
}


