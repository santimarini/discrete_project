#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "veinteveinte.h"
#include "avl_tree.h"


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

void merge(u32 *array, Node tree, int p, int q, int r, u32 cual){
  int i, j, k;
  int n_1 = (q - p) + 1;
  int n_2 = (r - q);
  u32 *L;
  u32 *R;
  Vertice vl = NULL, vr = NULL;
    // Asignacion de memoria
  L = (u32 *) malloc(n_1 * sizeof(u32));
  R = (u32 *) malloc(n_2 * sizeof(u32));

  // Copia de datos del arreglo A en los subarreglos L y R
  for (i = 0; i < n_1; i++){
    L[i] = array[p + i];
  }

  for (j = 0; j < n_2; j++){
    R[j] = array[q+j+1];
  }

  i = 0;
  j = 0;

  // Fusion de datos respetando el valor minimos entre dos arreglos
  for (k = p; k < r + 1; k++){
    if (i == n_1){
      array[k] = R[j];
      j =  j + 1;
    }
    else if(j == n_2){
      array[k] = L[i];
      i = i + 1;
    }
    else{
      if(cual == 1){
        vl = get_Vertice(L[i], tree);
        vr = get_Vertice(R[j], tree);
        if (vl->grado >= vr->grado){
          array[k] = L[i];
          i = i + 1;
        }
        else{
          array[k] = R[j];
          j = j + 1;
        }
      }
      else if(cual == 2){
        vl = get_Vertice(L[i], tree);
        vr = get_Vertice(R[j], tree);
        if (vl->color >= vr->color){
          array[k] = L[i];
          i = i + 1;
        }
        else{
          array[k] = R[j];
          j = j + 1;
        }
      }
      else if(cual == 3){
        vl = get_Vertice(L[i], tree);
        vr = get_Vertice(R[j], tree);
        if (vl->color <= vr->color){
          array[k] = L[i];
          i = i + 1;
        }
        else{
          array[k] = R[j];
          j = j + 1;
        }
      }
    }
  }
}

void merge_sort(u32 *array, Node tree, int p, int r, u32 cual){
  if (p < r){
        // Dividir el problema en subproblemas
    int q = (p + r)/2;

        // Resolver el problema de manera recursiva hasta llegar a una solucion trivial
    merge_sort(array, tree, p, q, cual);
    merge_sort(array, tree, q + 1, r, cual);

        // Fusion de resultados parciales
    merge(array, tree, p, q, r, cual);
  }
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
    /*free extra memory*/
  u32 max_grado = 0;
  Vertice v = NULL;
  for (u32 i = 0; i < num_vertices; i++){
    v = get_Vertice(G->orden_interno[i], G->node);
    if (v->grado > max_grado){
      max_grado = v->grado;
      G->delta = max_grado;
    }
  }

  free(linea);

  fclose(fp);
  fp = NULL;

  return G;
}

void DestruccionDelGrafo(Grafo G){
  if(G != NULL){
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
  if(i >= NumeroDeVertices(G) || j >= Grado(i,G))
    return -1u;
  Vertice v = get_Vertice(G->orden_interno[i], G->node);

  return v->vecinos[j]->color;
}

u32 NombreVecino(u32 j, u32 i, Grafo G){
  assert(G != NULL);
  Vertice v = get_Vertice(G->orden_interno[i], G->node);
  return v->vecinos[j]->nombre;
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
    v->color = x;
    return 0;
  }
  return 1;
}

char FijarOrden(u32 i, Grafo G, u32 N){
  assert(G != NULL);
  if(i < NumeroDeVertices(G) && N < NumeroDeVertices(G)){
    Vertice v_int = get_Vertice(G->orden_interno[i], G->node);
    Vertice v_nat = get_Vertice(G->orden_natural[N], G->node);
    v_int->nombre = v_nat->nombre;
    v_int->grado = v_nat->grado;
    v_int->color = v_nat->color;
    v_int->vecinos = realloc(v_int->vecinos, v_nat->grado * sizeof(struct VerticeSt));
    for(u32 j = 0; j < v_int->grado; j++){
      v_int->vecinos[j] = v_nat->vecinos[j];
    }
    return 0;
  }
  return 1;
}

// --FUNCIONES DE ORDENACION--

char WelshPowell(Grafo G){
  assert(G != NULL);
  u32 cual = 1;
  merge_sort(G->orden_interno, G->node, 0, NumeroDeVertices(G)-1, cual);

  return 0;
}

char RevierteBC(Grafo G){
  assert(G != NULL);
  u32 cual = 2;
  merge_sort(G->orden_interno, G->node, 0, NumeroDeVertices(G)-1, cual);

  return 0;
}

char ChicoGrandeBC(Grafo G){
  assert(G != NULL);
  u32 cual = 3;
  merge_sort(G->orden_interno, G->node, 0, NumeroDeVertices(G)-1, cual);
  
  return 0;
}

/*
u32 Greedy(Grafo G){
  u32 cantidad_de_colores = 1;
  u32 *color = calloc(cantidad_colores, sizeof(u32));
  if()
  for (u32 i = 0; i < NumeroDeVertices(G); i++){
    for (u32 j = 0; i < Grado(i, G); j++){
      printf("%lu\n", Grado(i,G));
      if(ColorVecino(i, j, G) == G->vertices[i].color){
        color += 1;
        FijarColor(color, i, G);
      }else{
        FijarColor(color, i, G);
      }
    }
  }

  return color;
}

*/
