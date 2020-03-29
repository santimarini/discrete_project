#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "veinteveinte.h"


// -- auxiliar functions -- //
static int compare(const void *n1, const void *n2){
  int x, y;
  x = *(int *) n1;
  y = *(int *) n2;
  if(x < y)
    return -1;
  else if(x == y)
    return 0;
  
  return 1;
}

static u32 existevertice(Grafo G, u32 count, u32 vert){
  for (u32 i = 0; i < count; i++) {
    if(G->vertices[i].nombre == vert)
      return 1;
  }
  return 0;
}

static u32 get_idx(Grafo g, u32 count, u32 vert){
  u32 ret = 0;
  while(ret < count){
    if(g->vertices[ret].nombre == vert)
      return ret;
    ret++;
  }
  return 0;
}


// -- FUNCIONES DE CONSTRUCCION/DESTRUCCION/COPIA DEL GRAFO --
Grafo ConstruccionDelGrafo(char const *filename){
  Grafo G;
  G = calloc(1, sizeof(struct GrafoSt));
  FILE *fp = NULL;
  fp = fopen(filename, "r");

  if (fp == NULL) {
    fprintf(stderr, "could not open file '%s'\n", filename);
    return NULL;
  }
  if(G == NULL){
    fprintf(stderr, "memory reservation failure\n");
    return NULL;
  }
  const char c[2] = " ";
  char *token;
  char *linea;
  u32 tam = 0;
  u32 vertice, vecino;
  Lado tuplas;
  do {
    if(getline(&linea, &tam, fp) == -1) {
      break;
    }
    if(linea[0] == 'p'){
      token = strtok(linea, c);
      token = strtok(NULL, c);
      token = strtok(NULL, c);
      G->nVertices = atoi(token);
      token = strtok(NULL, c);
      G->nLados = atoi(token);
      token = strtok(NULL, c);
    }
  }while(linea[0] != 'p');
  u32 num_vertices = NumeroDeVertices(G);
  u32 num_lados = NumeroDeLados(G);
  G->vertices = calloc(num_vertices, sizeof(struct VerticeSt));
  G->orden_creciente = calloc(num_vertices, sizeof(struct VerticeSt));
  tuplas = calloc(num_lados, sizeof(struct LadoSt));
  u32 pos_ver = 0, i = 0;
  while(!feof(fp)){
    if(fscanf(fp,"%s %lu %lu", linea, &vertice, &vecino) == -1){
        break;
    }
    tuplas[i].extremo1 = vertice;
    tuplas[i].extremo2 = vecino;
    i++;
    if(!existevertice(G, pos_ver, vertice)){
      G->vertices[pos_ver].nombre = vertice;
      G->vertices[pos_ver].grado = 1;
      G->vertices[pos_ver].color = 0;
      G->orden_creciente[pos_ver].nombre = vertice;
      G->orden_creciente[pos_ver].grado = 1;
      G->orden_creciente[pos_ver].color = 0;
      pos_ver++;
    }else{
      G->vertices[get_idx(G, pos_ver, vertice)].grado += 1;
      G->orden_creciente[get_idx(G, pos_ver, vertice)].grado += 1;
    }
    if(!existevertice(G, pos_ver, vecino)){
      G->vertices[pos_ver].nombre = vecino;
      G->vertices[pos_ver].grado = 1;
      G->orden_creciente[pos_ver].nombre = vecino;
      G->orden_creciente[pos_ver].grado = 1;
      G->orden_creciente[pos_ver].color = 0;
      pos_ver++;
    }else{
      G->vertices[get_idx(G, pos_ver, vecino)].grado += 1;
      G->orden_creciente[get_idx(G, pos_ver, vecino)].grado += 1;
    }
  }
  
  u32 delta = 0;
  for(u32 i = 0; i < num_vertices; i++){
    if(delta < Grado(i, G)){
      delta = Grado(i, G);
    }
  }
  G->delta = delta;
  printf("delta of '%s' is: %lu\n", filename, G->delta);
  printf("\n");
  for(u32 i = 0; i < num_vertices; i++){
    u32 k = 0;
    G->vertices[i].vecinos = calloc(Grado(i, G), sizeof(struct VerticeSt));
    G->orden_creciente[i].vecinos = calloc(Grado(i, G), sizeof(struct VerticeSt));
    for(u32 j = 0; j < num_lados; j++){
      if(tuplas[j].extremo1 == Nombre(i, G)){
        G->vertices[i].vecinos[k] = G->vertices[get_idx(G, num_vertices, tuplas[j].extremo2)];
        G->orden_creciente[i].vecinos[k] = G->orden_creciente[get_idx(G, num_vertices, tuplas[j].extremo2)];
        k++;
      }
      if(tuplas[j].extremo2 == Nombre(i, G)){
        G->vertices[i].vecinos[k] = G->vertices[get_idx(G, num_vertices, tuplas[j].extremo1)];
        G->orden_creciente[i].vecinos[k] = G->orden_creciente[get_idx(G, num_vertices, tuplas[j].extremo1)];
        k++;
      }
    }
  }
  qsort(G->orden_creciente, NumeroDeVertices(G), sizeof(struct VerticeSt), &compare);

  free(tuplas);
  free(linea);
  fclose(fp);
  fp = NULL;

  return G;
}

void DestruccionDelGrafo(Grafo G){
  for(u32 i = 0; i < NumeroDeVertices(G); i++){
    free(G->vertices[i].vecinos);
    free(G->orden_creciente[i].vecinos);
  }
  free(G->orden_creciente);
  free(G->vertices);
  free(G);
}

Grafo CopiarGrafo(Grafo G){
  assert(G != NULL);
  Grafo G2;
  G2 = calloc(1, sizeof(struct GrafoSt));
  if(G2 == NULL){
    fprintf(stderr, "Fallo al reservar memoria\n");
    return NULL;
  }
  G2->nVertices = NumeroDeVertices(G);
  G2->nLados =  NumeroDeLados(G);
  G2->delta = Delta(G);
  G2->vertices = calloc(NumeroDeVertices(G), sizeof(struct VerticeSt));
  G2->orden_creciente = calloc(NumeroDeVertices(G2), sizeof(struct VerticeSt));
  for(u32 i = 0; i < NumeroDeVertices(G); i++){
    G2->vertices[i].nombre = G->vertices[i].nombre;
    G2->orden_creciente[i].nombre = G->orden_creciente[i].nombre;
    G2->vertices[i].grado = G->vertices[i].grado;
    G2->orden_creciente[i].grado = G->orden_creciente[i].grado;
    G2->vertices[i].color = G->vertices[i].color;
    G2->orden_creciente[i].color = G->orden_creciente[i].color;
    G2->vertices[i].vecinos = calloc(Grado(i, G2), sizeof(struct VerticeSt));
    G2->orden_creciente[i].vecinos = calloc(G2->orden_creciente[i].grado, sizeof(struct VerticeSt));
    for (u32 j = 0; j < Grado(i, G2); j++) {
      G2->vertices[i].vecinos[j] = G->vertices[i].vecinos[j];
    }

    for(u32 j = 0; j < G2->orden_creciente[i].grado; j++){
      G2->orden_creciente[i].vecinos[j] = G->orden_creciente[i].vecinos[j];
    }
  }
  return G2;
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

u32 Nombre(u32 i, Grafo G){
  assert(G != NULL);
  return (G->vertices[i].nombre);
}

u32 Color(u32 i, Grafo G){
  assert(G != NULL);
  if(i >= G->nVertices)
    return -1u;

  return(G->vertices[i].color);
}

u32 Grado(u32 i, Grafo G){
  assert(G != NULL);
  if (i >= G->nVertices)
    return -1u;

  return(G->vertices[i].grado);
}

/* --FUNCIONES PARA EXTRAER INFORMACION DE LOS VECINOS DE UN VERTICE-- */

u32 ColorVecino(u32 j, u32 i, Grafo G){
  assert(G != NULL);
  if(i >= NumeroDeVertices(G) || j >= Grado(i,G))
    return -1u;

  return G->vertices[i].vecinos[j].color;
}

u32 NombreVecino(u32 j, u32 i, Grafo G){
  assert(G != NULL);
  return G->vertices[i].vecinos[j].nombre;
}

u32 OrdenVecino(u32 j, u32 i, Grafo G){
  assert(G != NULL);
  return get_idx(G,NumeroDeVertices(G),G->vertices[i].vecinos[j].nombre);
}

/*  --FUNCIONES PARA MODIFICAR DATOS DE LOS VERTICES-- */

char FijarColor(u32 x, u32 i, Grafo G){
  if(i < NumeroDeVertices(G)){
    G->vertices[i].color = x;
    return 0;
  }
  return 1;
}
char FijarOrden(u32 i, Grafo G, u32 N){
  assert(G != NULL);
  if(i < NumeroDeVertices(G) && N < NumeroDeVertices(G)){
    G->vertices[i].nombre = G->orden_creciente[N].nombre;
    G->vertices[i].grado = G->orden_creciente[N].grado;
    G->vertices[i].color = G->orden_creciente[N].color;
    G->vertices[i].vecinos = realloc(G->vertices[i].vecinos, G->orden_creciente[N].grado * sizeof(struct VerticeSt));
    for(u32 j = 0; j < G->vertices[i].grado; j++){
      G->vertices[i].vecinos[j] = G->orden_creciente[N].vecinos[j];
    }
    return 0;
  }
  return 1;
}
