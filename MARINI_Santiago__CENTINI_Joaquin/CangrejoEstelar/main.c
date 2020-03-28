#include <stdio.h>
#include <stdlib.h>
#include "veinteveinte.h"

int main()//int argc, char const *argv[]
{
	Grafo G;
	Grafo G2;
	G = ConstruccionDelGrafo();
	G2 = CopiarGrafo(G);
	printf("prueba para copair %lu \n", G2->vertices[2].nombre);
	DestruccionDelGrafo(G);
	DestruccionDelGrafo(G2);
	return 0;
}
