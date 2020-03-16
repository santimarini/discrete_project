#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "veinteveinte.h"


// -- FUNCIONES DE CONSTRUCCION/DESTRUCCION/COPIA DEL GRAFO --
Grafo ConstruccionDelGrafo(){
	FILE *fp;
	fp = fopen ("anna.txt", "rb");
	Grafo G;
	G = (Grafo) malloc(sizeof(Grafo));
	
	if (fp == NULL) {
		fprintf(stderr, "No se pudo abrir el archivo\n"); 
		return NULL;
	}

	if(G == NULL){
		fprintf(stderr, "Fallo al reservar memoria\n");
		return NULL;
	}
	u32 vertices, lados, vertice1, vertice2, anteriorvertice;
	char linea[FILE_LINE_MAX_SIZE];
	char letra;
	char *edge = NULL;
	int i = 0, j = 0;

	while(fgets(linea, sizeof(linea), fp) != NULL){
		letra = linea[0];

	//⬆⬆⬆ hasta acá andando joya ⬆⬆⬆//

		if(letra == 'p'){
			/*VER parseo de linea = "p edge 138 493" a algo como linea_parseada= ["p", "edge", "138", "493"](con strtok, lío),
			 no se me ocurre otra cosa;	vertice = (u32) linea_parseada[2]  */

			G->nVertices = vertices;
			G->nLados = lados;
			letra = '\n';
			edge = NULL;

		}else if(letra == 'e'){
			anteriorvertice = vertice1;
			fscanf(fp, "%c%d%d", &letra, &vertice1, &vertice2);
			letra = '\n';
			if(vertice1 != anteriorvertice){
				G->orden[i] = vertice1;
				G->vertices[i].nombre = vertice1;
				G->vertices[i].vecinos[j] = vertice2;
				j++;
			}
			if(vertice1 == anteriorvertice){
				G->vertices[i].vecinos[j] = vertice2;
				j++;
			}
			i++;
		}
	}
	int tam_dato;
	int tam_array;
	for(u32 l = 0; l < G->nVertices; l++){
		tam_dato = sizeof(u32);
	 	tam_array = sizeof(G->vertices[l].vecinos);
		G->vertices[l].grado = (u32)(tam_array/tam_dato);

	}
	u32 delta = 0;
	for(u32 k = 0; k < G->nVertices; k++) {
		if(G->vertices[k].grado > delta){
			delta = G->vertices[k].grado;
		}
	}
	G->delta = delta;
	fclose(fp);
	
	return G;
}




// -- FUNCIONES PARA EXTRAER INFORMACION DEL GRAFO --

u32 NumeroDeVertices(Grafo G){
	assert(G != NULL);
	return(G->nVertices);
}

u32 NumeroDeLados(Grafo G){
	assert(G != NULL);
	return(G->nLados);
}

u32 Delta(Grafo G){
	assert(G != NULL);
	return(G->delta);
}
/*
// -- FUNCIONES PARA EXTRAER INFORMACION DE LOS VERTICES --
u32 Nombre(u32 i,Grafo G){
	assert(G != NULL);
	return (G->orden[i].nombre);
}

u32 Color(u32 i,Grafo G){
	assert(G != NULL);
	(i>=G->nVertices)? -1 : (G->orden[i].color);
}

u32 Grado(u32 i,Grafo G){
	assert(G != NULL);
	(i>=G->nVertices)? -1 :(G->orden[i].grado);
}
*/
