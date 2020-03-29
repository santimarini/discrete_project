#include <stdio.h>
#include <stdlib.h>
#include "veinteveinte.h"

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
    G = ConstruccionDelGrafo(filename);
    
    if (G != NULL)
        DestruccionDelGrafo(G);

    return 0;
}
