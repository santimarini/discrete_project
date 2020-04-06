#include <stdio.h>
#include <stdlib.h>
#include "veinteveinte.h"
#include "avl_tree.h"

int main(int argc, char const *argv[])
{

  if (argc < 2){
    fprintf(stderr, "few arguments: type ./a.out <filename>\n");
    return -1;
  
  }else if (argc > 2){
    fprintf(stderr, "many arguments: type ./a.out <filename>\n");
    return -1;
  }
  
  char const *filename = argv[1];
  Grafo G;
  printf("--------- STARTING ---------\n\n");
  
  G = ConstruccionDelGrafo(filename);
  printf("\n");
  DestruccionDelGrafo(G);
  printf("graph destroyed\n\n\n");
  printf("--------- FINISH ---------\n\n");

  return 0;
}
