#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "GrafoSt2020.h"
#include "veinteveinte.h"
#include "avl_tree.h"

// -- FUNCIONES DE CONSTRUCCION/DESTRUCCION/COPIA DEL GRAFO --
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

Grafo ConstruccionDelGrafo(char const *filename){
  Grafo G = NULL;
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
  char *token = NULL;
  char *linea = NULL;
  u32 tam = 0;
  u32 vertice = 0, vecino = 0;
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
  Vertice *verts = calloc(num_vertices, sizeof(struct VerticeSt *));
  G->orden_natural = calloc(num_vertices, sizeof(u32));
  G->orden_interno = calloc(num_vertices, sizeof(u32));
  for (u32 i = 0; i < num_vertices; i++){
    verts[i] = calloc(1, sizeof (struct VerticeSt));
    verts[i]->vecinos = calloc(1, sizeof(Vertice));
  }
  struct __node *tree = NULL;
  Vertice ver = NULL, vec = NULL;
  u32 i = 0;
  while(!feof(fp)){
    if(fscanf(fp,"%s %lu %lu", linea, &vertice, &vecino) == -1){
      break;
    }
    if(!is_in_Node(vertice, tree)){
      verts[i]->nombre = vertice;
      verts[i]->grado = 1;
      verts[i]->color = -1u;
      G->orden_natural[i] = G->orden_interno[i] = vertice;
      tree = insert(tree, verts[i]);
      i++;
    }else{
      ver = get_Vertice(vertice, tree);
      ver->grado += 1;
      ver->vecinos = realloc(ver->vecinos, sizeof(Vertice) * (ver->grado));
      if (!ver->vecinos)
        fprintf(stderr, "realloc failure\n");
    }
    if(!is_in_Node(vecino, tree)){
      verts[i]->nombre = vecino;
      verts[i]->grado = 1;
      verts[i]->color = -1u;
      G->orden_natural[i] = G->orden_interno[i] = vecino;
      ver = get_Vertice(vertice, tree);
      ver->vecinos[ver->grado - 1u] = verts[i];
      verts[i]->vecinos[verts[i]->grado - 1u] = ver;
      tree = insert(tree, verts[i]);
      i++;
    }else{
      vec = get_Vertice(vecino, tree);
      ver = get_Vertice(vertice, tree);
      ver->vecinos[ver->grado - 1u] = vec;
      vec->grado += 1;
      vec->vecinos = realloc(vec->vecinos, sizeof(Vertice) * (vec->grado));
      if (!vec->vecinos)
        fprintf(stderr, "realloc failure\n");
      vec->vecinos[vec->grado - 1u] = ver;
    }
  }
  G->node = tree;
  qsort(G->orden_natural, num_vertices, sizeof(u32), &compare);
    /*calcule of delta*/

  Vertice v = NULL;
  for (u32 i = 0; i < num_vertices; i++){
    v = get_Vertice(G->orden_interno[i], G->node);
    if (v->grado > G->delta){
      G->delta = v->grado;
    }
  }

 /* Vertice ve = get_Vertice(18, tree);
  for (u32 i = 0; i < ve->grado; i++)
    printf("%lu ", ve->vecinos[i]->nombre);
    */
  free(verts);
  free(linea);

  fclose(fp);
  fp = NULL;

  return G;
}

void DestruccionDelGrafo(Grafo G){
  if(G != NULL){
    for (u32 i = 0; i < NumeroDeVertices(G); i++){
      free(get_Vertice(G->orden_interno[i], G->node)->vecinos);
      free(get_Vertice(G->orden_interno[i], G->node));
    }
    tree_Destroy(G->node);


    G->node = NULL;
    free(G->orden_natural);
    free(G->orden_interno);
    free(G);
    G = NULL;
  }
}
/*
Grafo CopiarGrafo(Grafo G){
  assert(G != NULL);
  Grafo G2;
  G2 = calloc(1, sizeof(struct GrafoSt));
  if(G2 == NULL){
    fprintf(stderr, "Fallo al reservar memoria\n");
    return NULL;
  }
  u32 num_vertices = NumeroDeVertices(G2)
  G2->nVertices = num_vertices;
  G2->nLados =  NumeroDeLados(G);
  G2->delta = Delta(G);
  G2->orden_interno = calloc(num_vertices, sizeof(u32));
  G2->orden_natural = calloc(num_vertices sizeof(u32));
  Vertice v = NULL;
  for(u32 i = 0; i < num_vertices; i++){
    v = get_Vertice(orden_interno[i], G->node);
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
*/// -- FUNCIONES PARA EXTRAER INFORMACION DEL GRAFO --

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

/// -- FUNCIONES PARA EXTRAER INFORMACION DE LOS VERTICES -- 

u32 Nombre(u32 i, Grafo G){
  assert(G != NULL);
  return (G->orden_interno[i]);
}

u32 Color(u32 i, Grafo G){
  assert(G != NULL);
  if(i >= NumeroDeVertices(G))
    return -1u;
  Vertice v = get_Vertice(G->orden_interno[i], G->node);

  if (v != NULL)
    return(v->color);
  
  return -1u;
}

u32 Grado(u32 i, Grafo G){
  assert(G != NULL);
  if (i >= G->nVertices)
    return -1u;
  
  Vertice v = get_Vertice(G->orden_interno[i], G->node);
  if (v != NULL)
    return(v->grado);
  
  return -1u;
}

/// --FUNCIONES PARA EXTRAER INFORMACION DE LOS VECINOS DE UN VERTICE-- 

u32 ColorVecino(u32 j, u32 i, Grafo G){
  assert(G != NULL);
  if (i >= NumeroDeVertices(G) || j >= Grado(i,G))
    return -1u;

  Vertice v = get_Vertice(G->orden_interno[i], G->node);
  if (v != NULL){
  	if (v->vecinos[0] != NULL)
    return v->vecinos[j]->color;
  }
  return -1u;
}

u32 NombreVecino(u32 j, u32 i, Grafo G){
  assert(G != NULL);

  Vertice v = get_Vertice(G->orden_interno[i], G->node);
  if (v != NULL)
    return v->vecinos[j]->nombre;

  return -1u;
}

static u32 get_index(u32 v, Grafo G){
	for(u32 i = 0; i < NumeroDeVertices(G); i++){
		if(v == G->orden_interno[i])
			return i;
	}
  return -1u;
}

u32 OrdenVecino(u32 j, u32 i, Grafo G){
  assert(G != NULL);
  Vertice v = get_Vertice(G->orden_interno[i], G->node);
  Vertice vec_j = v->vecinos[j];
  /*get idx of orden_interno*/
  return get_index(vec_j->nombre, G);
}

///  --FUNCIONES PARA MODIFICAR DATOS DE LOS VERTICES-- /
char FijarColor(u32 x, u32 i, Grafo G){
  if(i < NumeroDeVertices(G)){
    Vertice v = get_Vertice(G->orden_interno[i], G->node);
    if(v != NULL){
      v->color = x;
      return 0;
    }
  }
  return 1;
}

char FijarOrden(u32 i, Grafo G, u32 N){
  assert(G != NULL);
  if(i < NumeroDeVertices(G) && N < NumeroDeVertices(G)){
    G->orden_interno[i] = G->orden_natural[N];
    return 0;
  }
  return 1;
}
