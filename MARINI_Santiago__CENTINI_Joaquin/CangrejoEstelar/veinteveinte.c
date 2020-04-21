#include <stdlib.h>
#include <assert.h>
#include "veinteveinte.h"
#include "avl_tree.h"
#include "pila.h"
#include "cola.h"

struct ParaOrdenarA{
    u32 name;
    u32 informacion;
    u32 cardinal;
    u32 indice;
};

typedef struct ParaOrdenarA *ParaOrdenar;
// -- auxiliar functions -- //
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
static int compare4(const void *n1, const void *n2){
    ParaOrdenar x, y;
    x = (ParaOrdenar) n1;
    y = (ParaOrdenar) n2;
    if(x->cardinal > y->cardinal)
      return -1;
    else if(x->cardinal == y->cardinal)
      return 0;

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
  if(cantidad_colores != N)
	 cantidad_colores = N;

  return cantidad_colores;
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
	 	for (u32 j = 0; j < Grado(i, G); j++)
	 		colores_vecinos[j] = ColorVecino(j, i, G);

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
static u32 DFS(u32 i, Grafo G, u32 **apilados, u32 *numap){
	Pila *pila = CrearPila();
	if (!pila)
		return 1;
	Apilar(pila, i);
	(*numap) += 1;
	(*apilados)[i] = 1;
	u32 p, q, existe = 0;
	while(!EstaVacia(pila)){
		p = Cima(pila); /*indice del orden interno de cima*/
		if(Grado(p, G) == NumeroDeVertices(G)-1){
			for (u32 i = 0; i < NumeroDeVertices(G); i++)
				(*apilados)[i] = 1;
			(*numap) = NumeroDeVertices(G);
			break;
		}
		existe = 0;
		for(u32 j = 0; j < Grado(p, G); j++){
			q = OrdenVecino(j, p, G);
			if(!(*apilados)[q]){
				existe = 1;
				Apilar(pila, q);
				(*numap) += 1;
				(*apilados)[q] = 1;
			}
		}
		if(!existe){
			Desapilar(pila);
		}
	}
	DestruirPila(pila);
	return 0;
}

u32 NumCCs(Grafo G){
	printf("STARTED NumCCs\n");
	u32 count = 0;
	u32 numap = 0;
	u32 *apilados = calloc(NumeroDeVertices(G), sizeof(u32));
	
	for (u32 i = 0; i < NumeroDeVertices(G); i++){
		if(numap == NumeroDeVertices(G))
			break;
		else if(!apilados[i]){
			if(DFS(i, G, &apilados, &numap))
				return -1u;
			count ++;
			printf("DFS vertice %lu finished\n", Nombre(i,G));
		}
	}
	
	free(apilados);
	return count;
}


