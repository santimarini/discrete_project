#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "veinteveinte.h"
#include "avl_tree.h"
#include <time.h>

struct ParaOrdenarA{
    u32 name;
    u32 informacion;
    u32 indice;
};

typedef struct ParaOrdenarA *ParaOrdenar;

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

static int compare1(const void *n1, const void *n2){
  ParaOrdenar x, y;
  x = (ParaOrdenar)n1;
  y = (ParaOrdenar)n2;
  if(x->name < y->name)
    return -1;
  else if(x->name == y->name)
    return 0;

  return 1;
}

static int compare2(const void *n1, const void *n2){
  ParaOrdenar x, y;
  x = (ParaOrdenar) n1;
  y = (ParaOrdenar) n2;
  if(x->informacion > y->informacion)
    return -1;
  else if(x->informacion == y->informacion)
    return 0;

  return 1;
}

static int compare3(const void *n1, const void *n2){
  ParaOrdenar x, y;
  x = (ParaOrdenar) n1;
  y = (ParaOrdenar) n2;
  if(x->informacion < y->informacion)
    return -1;
  else if(x->informacion == y->informacion)
    return 0;

  return 1;
}


// -- FUNCIONES DE CONSTRUCCION/DESTRUCCION/COPIA DEL GRAFO --
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

/*
u32 OrdenVecino(u32 j, u32 i, Grafo G){
  assert(G != NULL);
  Vertice v = get_Vertice(G->orden_interno[i], G->node);
  Vertice vec_j = v->vecinos[j];
  if (vec_j->nombre = G->orden_interno[i])
    return ;

}
*/
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

// --FUNCIONES DE ORDENACION--
char WelshPowell(Grafo G){
    ParaOrdenar A;
    A = calloc(NumeroDeVertices(G),sizeof(struct ParaOrdenarA));
    if(!A){
      return 1;
    }
    for(u32 i = 0; i < NumeroDeVertices(G); i++){
        A[i].name = Nombre(i,G);
        A[i].informacion = Grado(i,G);
    }
    qsort(A,NumeroDeVertices(G),sizeof(struct ParaOrdenarA),&compare1);
    for(u32 i = 0; i < NumeroDeVertices(G); i++){
      A[i].indice = i;
    }
    qsort(A,NumeroDeVertices(G),sizeof(struct ParaOrdenarA),&compare2);
    for(u32 i = 0; i < NumeroDeVertices(G); i++){
      FijarOrden(i,G,A[i].indice);
    }
    return 0;
}

char ChicoGrandeBC(Grafo G){
    ParaOrdenar A;
    u32 cantidad_colores;
    u32 *cantidad_vertices_color;
    A = calloc(NumeroDeVertices(G),sizeof(struct ParaOrdenarA));
    if(!A){
      return 1;
    }
    for(u32 i = 0; i < NumeroDeVertices(G); i++){
        A[i].name = Nombre(i,G);
        A[i].informacion = Color(i,G);
    }
    qsort(A,NumeroDeVertices(G),sizeof(struct ParaOrdenarA),&compare1);
    for(u32 i = 0; i < NumeroDeVertices(G); i ++){
        A[i].indice = i;
    }
    qsort(A,NumeroDeVertices(G),sizeof(struct ParaOrdenarA),&compare2);
    cantidad_colores = A[0].informacion + 1;
    cantidad_vertices_color = calloc(cantidad_colores,sizeof(u32));
    for(u32 i = 0; i < NumeroDeVertices(G); i++){
        cantidad_vertices_color[Color(i,G)] += 1;
    }
    for(u32 i = 0; i < NumeroDeVertices(G); i++){
        A[i].cardinal = cantidad_vertices_color[A[i].informacion];
    }
    qsort(A,NumeroDeVertices(G),sizeof(struct ParaOrdenarA),&compare3);
    for(u32 i = 0; i < NumeroDeVertices(G); i++){
      FijarOrden(i,G,A[i].indice);
    }
    return 0;
}

char RevierteBC(Grafo G){
    ParaOrdenar A;
    u32 cantidad_colores;
    u32 *cantidad_vertices_color;
    A = calloc(NumeroDeVertices(G),sizeof(struct ParaOrdenarA));
    if(!A){
      return 1;
    }
    for(u32 i = 0; i < NumeroDeVertices(G); i++){
        A[i].name = Nombre(i,G);
        A[i].informacion = Color(i,G);
    }
    qsort(A,NumeroDeVertices(G),sizeof(struct ParaOrdenarA),&compare1);
    for(u32 i = 0; i < NumeroDeVertices(G); i ++){
        A[i].indice = i;
    }
    qsort(A,NumeroDeVertices(G),sizeof(struct ParaOrdenarA),&compare2);
    cantidad_colores = A[0].informacion + 1;
    cantidad_vertices_color = calloc(cantidad_colores,sizeof(u32));
    for(u32 i = 0; i < NumeroDeVertices(G); i++){
        cantidad_vertices_color[Color(i,G)] += 1;
    }
    for(u32 i = 0; i < NumeroDeVertices(G); i++){
        A[i].cardinal = cantidad_vertices_color[A[i].informacion];
    }
    qsort(A,NumeroDeVertices(G),sizeof(struct ParaOrdenarA),&compare4);
    for(u32 i = 0; i < NumeroDeVertices(G); i++){
      FijarOrden(i,G,A[i].indice);
    }
    return 0;
}

char AleatorizarVertices(Grafo G, u32 R){
	ParaOrdenar A;
  A = calloc(NumeroDeVertices(G), sizeof(struct ParaOrdenarA));
  if(!A)
    return 1;

  for(u32 i = 0; i < NumeroDeVertices(G); i++){
      A[i].name = Nombre(i,G);
      A[i].informacion = Color(i, G);
	}
	/*acá ordeno para obtener los indices del orden natural*/
	qsort(A, NumeroDeVertices(G), sizeof(struct ParaOrdenarA), &compare1);
  
  for(u32 i = 0; i < NumeroDeVertices(G); i++)
    A[i].indice = i;

	for (u32 i = 0; i < NumeroDeVertices(G); i++){
		srand(R);
		u32 random = (u32) (rand() %  NumeroDeVertices(G));
		if (random != i){
			u32 tmp = A[random].indice;
			A[random].indice = A[i].indice;
			A[i].indice = tmp;
		}
	}

	for (u32 i = 0; i < NumeroDeVertices(G); i++)
		FijarOrden(i, G , A[i].indice);

	free(A);
  
  return 0;
}

static u32 IsIn(u32 e, u32 *array, u32 N){
	for (u32 i = 0; i < N; i++){
		if(array[i] == e)
			return 1;
	}
	return 0;
}

static u32 BuscarMinNoUsado(u32 *array, u32 N, u32 cantidad_colores){

	for (u32 i = 0; i < N; i++){
		if (!IsIn(i, array, N)){
				return i;
		}
	}
	return cantidad_colores - 1u;
}

u32 Greedy(Grafo G){
  assert(G != NULL);
  u32 color_minimo = 0;
  u32 cantidad_colores = 1;
  u32 *colores = (u32 *) calloc(NumeroDeVertices(G), sizeof(u32));
  u32 *colores_vecinos = NULL;
  for (u32 i = 0; i < NumeroDeVertices(G); i++)
  	FijarColor(-1u, i, G);

  for (u32 i = 0; i < NumeroDeVertices(G); i++) {
  	colores_vecinos = calloc(Grado(i, G), sizeof(u32));
	 	for (u32 j = 0; j < Grado(i, G); j++){
	 		colores_vecinos[j] = ColorVecino(j, i, G);
	  }
	 	color_minimo = BuscarMinNoUsado(colores_vecinos, Grado(i, G), cantidad_colores);
 		if(!IsIn(color_minimo, colores, cantidad_colores)){
			cantidad_colores += 1;
			colores[cantidad_colores - 1u] = color_minimo;
		}
 		FijarColor(color_minimo, i, G);
  	free(colores_vecinos);
  }
  free(colores);
  return cantidad_colores;
}



/* funciones sobre CC*/


