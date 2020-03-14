#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "veinteveinte.h"

u32 NumeroDeVertices(Grafo G){
	assert(G!=NULL);
	return(G->nvertices);
}

u32 NumeroDeLados(Grafo G){
	assert(G!=NULL);
	return(G->nlados);
}

u32 Delta(Grafo G){
	assert(G != NULL);
	return(G->delta);
}

// -- FUNCIONES PARA EXTRAER INFORMACION DE LOS VERTICES --
u32 Nombre(u32 i,Grafo G){
	return (G->orden[i]->nombre);
}

u32 Color(u32 i,Grafo G){
	(i>=G->nvertices)? -1 : (G->orden[i]->color);
}

u32 Grado(u32 i,Grafo G){
	(i>=G->nvertices)? -1 :(G->orden[i]->grado);
}
