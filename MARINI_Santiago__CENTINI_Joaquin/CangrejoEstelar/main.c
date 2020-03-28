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
	printf("El porden ascendente de los vertices de G2 es: ");
	for(u32 i = 0; i < NumeroDeVertices(G2); i++){
		printf("%lu \n", G2->orden_creciente[i].nombre);
	}
	printf("Si esto aparece entonces es problema del copia\n");
	DestruccionDelGrafo(G2);
	return 0;
}
