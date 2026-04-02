#include <stdio.h>
#include <string.h>
#include <sha256.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

  if(argc < 2){
    printf("faltan argumentos\n");
    return 1;
  }

  unsigned char *sha256Out;

  if(strcmp(argv[1], "-m") == 0 && argc>2){
    sha256Out = sha256(argv[2]);
  }else{
    FILE *archivo;
    archivo = fopen(argv[1], "rb");
    
    if (archivo != NULL) {
      fseek(archivo, 0, SEEK_END);
      long tam = ftell(archivo); 
      fseek(archivo, 0, SEEK_SET);
      
      unsigned char* data = (unsigned char*)calloc(tam + 1, sizeof(unsigned char));
      if(!data) return 1;

      size_t leidos = fread(data, 1, tam, archivo);
      fclose(archivo);
      sha256Out = sha256(data);
    }
  }


  for(int i = 0; i < 32; i++) {
    printf("%02x", sha256Out[i]);
  }
  printf("\n");





  return 0;
}
