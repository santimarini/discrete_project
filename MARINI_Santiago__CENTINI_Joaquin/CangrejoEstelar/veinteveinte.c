#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "veinteveinte.h"


// -- FUNCIONES DE CONSTRUCCION/DESTRUCCION/COPIA DEL GRAFO --
Grafo ConstruccionDelGrafo(){
	Grafo G;
	G = malloc(sizeof(Grafo));
	if(G==NULL){
		perror("No se pudo reservar memoria");
	}
	FILE *fp;
	fp = fopen ( "anna.txt", "rb" );
	if (fp==NULL) {perror("No se pudo abrir el archivo"); exit (1);}
	char letra;
	char *edge;
	u32 vertices, lados, vertice1, vertice2, anteriorvertice;
	int i = 0, j = 0;
	while(feof(fp)==0){
		letra = fgetc(fp);
		if(letra == 'p'){
			fscanf(fp, "%c%s%d%d", &letra,edge,&vertices,&lados);
			G->nVertices = vertices;
			G->nLados = lados;
			letra = '\n';
			edge = NULL;

		}

		else if(letra == 'e'){
			anteriorvertice = vertice1;
			fscanf(fp, "%c%d%d", &letra,&vertice1,&vertice2);
			letra='\n';
			if(vertice1!=anteriorvertice){
				G->orden[i]=vertice1;
				G->vertices[i].nombre=vertice1;
				G->vertices[i].vecinos[j]=vertice2;
				j++;
			}
			if(vertice1==anteriorvertice){
				G->vertices[i].vecinos[j]=vertice2;
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
		if(G->vertices[k].grado>delta){
			delta = G->vertices[k].grado;
		}
	}
	G->delta = delta;


	fclose(fp);
	return G;
}




// -- FUNCIONES PARA EXTRAER INFORMACION DEL GRAFO --

u32 NumeroDeVertices(Grafo G){
	assert(G!=NULL);
	return(G->nVertices);
}

u32 NumeroDeLados(Grafo G){
	assert(G!=NULL);
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
