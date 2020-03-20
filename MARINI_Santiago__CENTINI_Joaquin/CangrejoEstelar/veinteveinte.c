#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "veinteveinte.h"


// -- FUNCIONES DE CONSTRUCCION/DESTRUCCION/COPIA DEL GRAFO --
Grafo ConstruccionDelGrafo(){
	Grafo G;
	G = (Grafo) malloc(sizeof(Grafo));
	FILE *fp;
	fp = fopen ("anna.txt", "r");
	if (fp == NULL) {
		fprintf(stderr, "No se pudo abrir el archivo\n");
		return NULL;
	}
	if(G == NULL){
		fprintf(stderr, "Fallo al reservar memoria\n");
		return NULL;
	}
	const char c[2] = " ";
	char *token;
	u32 vertice1, vertice2;
	char *linea=NULL;
	int tam = 0;
	printf("acatodobien\n");
	if(getline(&linea,&tam,fp)==-1){
		fprintf(stderr, "Error en elprimer getline\n");
	}
	printf("acatodobien\n");
	while(linea[0]=='c'){
		if(getline(&linea,&tam,fp)==-1){
			fprintf(stderr, "Error en elprimer getline\n");
		}
	}
	//en este punto en linea esta : p edge vertice lados
	//si hago un fscanf u otro fgets empiezo a leer e v1 v2
	token = strtok(linea,c);
	token = strtok(NULL,c);
	token = strtok(NULL,c);
	G->nVertices=atoi(token);
	token = strtok(NULL,c);
	G->nAristas = atoi(token);
	token = strtok(NULL,c);
	printf("%lu \n", G->nVertices);
	printf("%lu \n", G->nAristas);


	//seteamos el orden, por defecto natural?, verificar si esta bien
	G->orden = calloc(G->nVertices, sizeof(u32));
	G->vertices = calloc(G->nVertices, sizeof(struct VerticeSt));

	for(int i = 0;i < (int)G->nVertices; i++){
		G->orden[i]=i+1;
		G->vertices[i].nombre = i+1;
	}
	printf("El nombre del vertice n5 del orden del grafo es: %lu\n", G->orden[5]);

	for(u32 i = 0; i <= G->nAristas; i++){
		free(linea);
		linea = NULL;
		tam = 0;
		if(getline(&linea,&tam,fp) == -1){
			fprintf(stderr, "Error en el 2 getline\n");
		}
		if (linea[0]=='e') {
			token = strtok(linea,c);
			token = strtok(NULL,c);
			vertice1=atoi(token);
			token = strtok(NULL,c);
			vertice2 = atoi(token);
			token = strtok(NULL,c);
			printf("%lu %lu\n",vertice1,vertice2 );
		}
		else{
			break;
		}
	}




	free(linea);
	fclose(fp);
	fp = NULL;
	return G;
}




// -- FUNCIONES PARA EXTRAER INFORMACION DEL GRAFO --

u32 NumeroDeVertices(Grafo G){
	assert(G != NULL);
	return(G->nVertices);
}

u32 NumeroDeLados(Grafo G){
	assert(G != NULL);
	return(G->nAristas);
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
