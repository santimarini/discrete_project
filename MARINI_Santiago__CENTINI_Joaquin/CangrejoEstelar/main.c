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
    printf("Ahora viene WelshPowell\n");
    WelshPowell(G);
    printf("paso WelshPowell el nuevo orden es: \n");
    for(u32 i = 0; i < NumeroDeVertices(G); i++){
      printf("nombre: %lu, grado: %lu \n", G->vertices[i].nombre, G->vertices[i].grado);
    }
    if (G != NULL)
        DestruccionDelGrafo(G);

    return 0;
}
