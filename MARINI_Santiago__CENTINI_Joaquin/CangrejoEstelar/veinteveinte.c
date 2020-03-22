#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "veinteveinte.h"


// -- FUNCIONES DE CONSTRUCCION/DESTRUCCION/COPIA DEL GRAFO --
Grafo ConstruccionDelGrafo(){
    Grafo G;
    G = (Grafo) malloc(sizeof(Grafo));
    FILE *fp =NULL;
    fp = fopen("anna.txt", "r");

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
    char *linea = NULL;
    u32 tam = 0;
    u32 grade = 1;
    u32 prev_vertice = 0, vertice = 0, vecino = 0;
    u32 pos = 0;
    while(!feof(fp)){
        if(getline(&linea, &tam, fp) == -1) {//hay q ver esto pq retorna -1 cuando hay EOF o error
            break;
        }
            prev_vertice = vertice; //guardo el valor de vertice para luego comparar
            if(linea[0] == 'p'){
            token = strtok(linea, c);
            token = strtok(NULL,c);
            token = strtok(NULL,c);
            G->nVertices = atoi(token);
            token = strtok(NULL,c);
            G->nLados = atoi(token);
            token = strtok(NULL,c);
        /*allocamos memoria para los vertices*/
            G->vertices = calloc(NumeroDeVertices(G), sizeof(struct VerticeSt));
        }else if(linea[0] == 'e'){
            /*parseo vertice*/
            token = strtok(linea, c);
            token = strtok(NULL, c);
            vertice = atoi(token);
            token = strtok(NULL, c);
            vecino = atoi(token);
            token = strtok(NULL, c);
       
            /*ahora comparo para ver si son iguales y aumento el grado*/

            //printf("grado de vertice %lu es %lu\n",vertice,grade);
            if(prev_vertice != 0){ //quiere decir q solo leyó un vertice
                if(prev_vertice == vertice){
                    grade++;
                }else{
                    /*quiere decir q no se repite, por eso ya lo pongo en vertices*/
                    /*hay q chequear las posiciones, está dejando lugares sin asignar*/
                    G->vertices[pos].nombre = vertice - 1; //
                    G->vertices[pos].grado = grade;
                    pos++;
                    grade = 1;
                	printf("count :%lu\n", pos);;
                }
            }
                    printf("grade %lu\n", grade);
        }
    }
    free(linea);
    /*vas a notar cuando corras q este for se ejecuta más allá de lo q deberia, se debe ejecutar hasta 136*/
    /*esto es lo q rompe el archivo*/
    for (u32 i=0; i< NumeroDeVertices(G);i++)
    	printf("orden vertice %lu : %lu\n",G->vertices[i].nombre, G->vertices[i].grado );

    if(fp != NULL){
    	//fclose(fp);
    	fp=NULL;
    }
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

/* -- FUNCIONES PARA EXTRAER INFORMACION DE LOS VERTICES -- */

u32 Nombre(u32 i,Grafo G){
    assert(G != NULL);
    return (G->vertices[i].nombre);
}

u32 Color(u32 i,Grafo G){
    assert(G != NULL);
    if(i >= G->nVertices)
        return -1;
    
    return(G->vertices[i].color);
}

u32 Grado(u32 i,Grafo G){
    assert(G != NULL);
    if (i >= G->nVertices)
        return -1u;

    return(G->vertices[i].grado);
}
