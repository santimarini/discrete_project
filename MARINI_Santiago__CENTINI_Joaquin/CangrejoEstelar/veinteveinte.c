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
	fp = fopen ("anna.txt", "rb");

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
	char *seteo;
	char *letra;
	do{
		fgets(linea,FILE_LINE_MAX_SIZE,fp);
	}while(linea[0]!='p');
	//en este punto en linea esta : p edge vertice lados
	//si hago un fscanf u otro fgets empiezo a leer e v1 v2
	int i=0;
	int j=0;
	while(i!=2){
		if(linea[j]==' '){
			i++;
		}
		j++;
	}
	i = 0;
	while(linea[j]!=' '){
		seteo[i] = linea[j];
		i++;
		j++;
	}
	G->nVertices = atoi(seteo);
	printf("%lu \n", G->nVertices);
	i = 0;
	j++;
	while(linea[j]!='\n'){
		seteo[i] = linea[j];
		i++;
		j++;
	}
	seteo[i] ='\n';
	G->nLados = atoi(seteo);
	printf("%lu\n", G->nLados);
	//seteamos el orden, por defecto natural?, verificar si esta bien
	G->orden = malloc(sizeof(u32)*G->nVertices);
	G->vertices = calloc(G->nVertices,sizeof(Vertice));

	for(int i = 0;i < (int)G->nVertices; i++){
		G->orden[i]=i+1;
		//G->vertices[i].nombre = i+1;
	}
	printf("El nombre del vertice n5 del orden del grafo es: %lu\n", G->orden[5]);
	char basura;
	for(u32 i = 0;i < G->nLados; i++){
		fscanf(fp,"%c %lu %lu\n",&basura,&vertice1,&vertice2);
		/* --PRIMER INTENTO DE SETER VECINOS Y CREAR VERTICES--(MEDIO RANCIO)
		if(i==0){
			//crearvertice();
			//setear un vecino;
		}
		else{
			if(G->vertices[i-1].nombre != vertice1){
				//crearvertice();
			}
			else{
				//setear un vecino;
			}
		}*/
	}

	if(fclose(fp)==-1){perror("No se pudo cerrar el archivo");};
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
