#include <stdlib.h>
#include "veinteveinte.h"
#include "pila.h"
#include "cola.h"
#include "para_ordenar.h"

// -- FUNCIONES DE COMPARACIÓN -- //
static int compareNombre(const void *n1, const void *n2) {
  ParaOrdenar x, y;
  x = (ParaOrdenar) n1;
  y = (ParaOrdenar) n2;
  if(x->nombre < y->nombre)
    return -1;
  else if(x->nombre == y->nombre)
    return 0;

  return 1;
}

static int compareInfoDecrec(const void *n1, const void *n2) {
  ParaOrdenar x, y;
  x = (ParaOrdenar) n1;
  y = (ParaOrdenar) n2;
  if(x->informacion > y->informacion)
    return -1;
  else if(x->informacion == y->informacion)
    return 0;

  return 1;
}

static int compareCardinal(const void *n1, const void *n2) {
  ParaOrdenar x, y;
  x = (ParaOrdenar) n1;
  y = (ParaOrdenar) n2;
  if(x->coloreo_cardinal < y->coloreo_cardinal)
    return -1;
  else if(x->coloreo_cardinal == y->coloreo_cardinal) {
    if(x->informacion > y->informacion)
      return 0;
  }
  
  return 1;
}

// --FUNCIONES DE ORDENACIÓN-- //
// asumimos que si el grafo es null, ese error se maneja en main.c
char WelshPowell(Grafo G) {
  // arreglo con nombre de cada vértice, su grado e índice que le
  // corresponde en el orden natural
  ParaOrdenar vertices_grados;
  vertices_grados = calloc(NumeroDeVertices(G), sizeof(struct ParaOrdenarA));
  if(!vertices_grados)
    return 1;

  for(u32 i = 0; i < NumeroDeVertices(G); i++) {
    vertices_grados[i].nombre = Nombre(i, G);
    vertices_grados[i].informacion = Grado(i, G);
  }
  // ordenamos el arreglo auxiliar en orden creciente por nombre de vértices
  qsort(vertices_grados, NumeroDeVertices(G), 
          sizeof(struct ParaOrdenarA), &compareNombre);
  // seteamos los índices de cada estructura (que serán los índices del orden
  // natural)
  for(u32 i = 0; i < NumeroDeVertices(G); i++)
    vertices_grados[i].indice = i;

  // volvemos a ordenar el Arreglo pero esta vez según la información de
  // nuestro interes
  qsort(vertices_grados, NumeroDeVertices(G),
          sizeof(struct ParaOrdenarA), &compareInfoDecrec);
  // modificamos el orden interno del Grafo aprovechando que tenemos en cada
  // estructura ParaOrdenarA el índice que le corresponde al vértice en el
  // orden natural
  for(u32 i = 0; i < NumeroDeVertices(G); i++)
    FijarOrden(i, G, vertices_grados[i].indice);

  free(vertices_grados);

  return 0;
}

char ChicoGrandeBC(Grafo G) {
  // arreglo con nombre de cada vértice, cantidad de vértices pintados
  // con el mismo color y el índice que le corresponde en el orden natural
  ParaOrdenar vertices_cardinal;
  u32 cantidad_colores = 0;
  u32 *arreglo_colores;
  vertices_cardinal = calloc(NumeroDeVertices(G), sizeof(struct ParaOrdenarA));

  if(!vertices_cardinal)
    return 1;

  for(u32 i = 0; i < NumeroDeVertices(G); i++) {
    if(Color(i, G) > cantidad_colores)
      cantidad_colores = Color(i, G);
  }
  cantidad_colores += 1;
  // creo un arreglo que denota en la posición i  la cantidad de
  // vértices pintados con el color i
  arreglo_colores = calloc(cantidad_colores, sizeof(u32));
  for(u32 i = 0; i < NumeroDeVertices(G); i++) {
    vertices_cardinal[i].nombre = Nombre(i, G);
    vertices_cardinal[i].informacion = Color(i, G);
  }
  qsort(vertices_cardinal, NumeroDeVertices(G), sizeof(struct ParaOrdenarA), 
          &compareNombre);

  for(u32 i = 0; i < NumeroDeVertices(G); i ++)
    vertices_cardinal[i].indice = i;

  for(u32 i = 0; i < NumeroDeVertices(G); i++)
    arreglo_colores[Color(i, G)] += 1;

  // seteo en cada estructura la cantidad de vértices pintados con el color
  // que está pintado el vértice en cuestión
  for(u32 i = 0; i < NumeroDeVertices(G); i++)
    vertices_cardinal[i].coloreo_cardinal = 
    				arreglo_colores[vertices_cardinal[i].informacion];

  // ordeno el arreglo de acuerdo a su cardinalidad y modifico el orden
  // interno
  qsort(vertices_cardinal, NumeroDeVertices(G), sizeof(struct ParaOrdenarA), 
          &compareCardinal);
  for(u32 i = 0; i < NumeroDeVertices(G); i++)
    FijarOrden(i, G, vertices_cardinal[i].indice);

  free(vertices_cardinal);
  free(arreglo_colores);

  return 0;
}

// misma idea que WelshPowell //
char RevierteBC(Grafo G) {
  ParaOrdenar vertices_color;
  vertices_color = calloc(NumeroDeVertices(G), sizeof(struct ParaOrdenarA));
  if(!vertices_color)
    return 1;

  for(u32 i = 0; i < NumeroDeVertices(G); i++) {
    vertices_color[i].nombre = Nombre(i, G);
    vertices_color[i].informacion = Color(i, G);
  }
  qsort(vertices_color, NumeroDeVertices(G),
          sizeof(struct ParaOrdenarA), &compareNombre);

  for(u32 i = 0; i < NumeroDeVertices(G); i++)
    vertices_color[i].indice = i;

  qsort(vertices_color, NumeroDeVertices(G), sizeof(struct ParaOrdenarA),
    &compareInfoDecrec);

  for(u32 i = 0; i < NumeroDeVertices(G); i++)
    FijarOrden(i, G, vertices_color[i].indice);
  
  free(vertices_color);

  return 0;
}

char AleatorizarVertices(Grafo G, u32 R) {
  ParaOrdenar vertices_aleatorizados;
  vertices_aleatorizados = calloc(NumeroDeVertices(G),
        sizeof(struct ParaOrdenarA));
  if(!vertices_aleatorizados)
    return 1;

  for(u32 i = 0; i < NumeroDeVertices(G); i++) {
      vertices_aleatorizados[i].nombre = Nombre(i, G);
      vertices_aleatorizados[i].informacion = Color(i, G);
  }
  // acá ordeno para obtener los índices del orden natural
    qsort(vertices_aleatorizados, NumeroDeVertices(G),
      sizeof(struct ParaOrdenarA), &compareNombre);

  for(u32 i = 0; i < NumeroDeVertices(G); i++)
    vertices_aleatorizados[i].indice = i;

 // siembro semilla R para luego obtener un numero pseudoaleatorio con rand()
  srand(R);
  for(u32 i = 0; i < NumeroDeVertices(G); i++) {
    u32 random = (u32) (rand() %  NumeroDeVertices(G));
    if(random != i) { // para evitar hacer un swap entre una misma posición
      u32 tmp = vertices_aleatorizados[random].indice;
      vertices_aleatorizados[random].indice = vertices_aleatorizados[i].indice;
      vertices_aleatorizados[i].indice = tmp;
    }
  }

  for (u32 i = 0; i < NumeroDeVertices(G); i++)
    FijarOrden(i, G , vertices_aleatorizados[i].indice);

  free(vertices_aleatorizados);

  return 0;
}

// utilizo el recorrido del grafo BFS visto en el teórico para determinar si es
// bipartito o no

static u32 BFS(u32 i, Grafo G, u32 **visitados, u32 *numco, u32 *check) {
  Cola *cola = CrearCola();
  if (!cola)
    return 1;
  Encolar(cola, i);
  (*numco) += 1;
  (*visitados)[i] = 1;
  FijarColor(0, i, G);
  u32 p = 0, q = 0, existe = 0;

  while(!EstaVaciaC(cola)) {
    p = PrimerElemento(cola);
    existe = 0;
    for(u32 j = 0; j < Grado(p, G); j++) {
      q = OrdenVecino(j, p, G);
      if(!(*visitados)[q]) {
        existe = 1;
        Encolar(cola, q);
        (*numco) += 1;
        (*visitados)[q] = 1;
        if(Color(p, G) == 0)
            FijarColor(1, q, G);
        else if(Color(p, G) == 1)
            FijarColor(0, q, G);
      }
      if(Color(p, G) == ColorVecino(j, p, G)) {
        (*numco) = NumeroDeVertices(G);
        (*check) = 0;
        break;
      }
    }
    if(!existe)
      Desencolar(cola);
  }

  DestruirCola(cola);

  return 0;
}

char Bipartito(Grafo G) {
  // numco cuenta el número de vertices coloreados, que se corresponderá con el
  // número de vértices visitados
  u32 numco = 0;
  u32 esBipartito = 1;
  u32 *visitados = calloc(NumeroDeVertices(G), sizeof(u32));
  // fijo el color  de todos los vértices en 2 para identificar los vértices
  // no visitados, es decir, si el vértice en cuestión tiene color 2 no fue
  // visitado
  for(u32 i = 0; i < NumeroDeVertices(G); i++)
    FijarColor(2, i, G);

  for (u32 i = 0; i < NumeroDeVertices(G); i++) {
    if(numco == NumeroDeVertices(G))
      break;
    else if(!visitados[i]) {
      // por si hay algún error
      if(BFS(i, G, &visitados, &numco, &esBipartito))
        return -1;
    }
  }
  free(visitados);

  if(esBipartito)
    return 0;
  // como se determinó que el grafo no es bipartito se lo deja coloreado
  // con un coloreo propio.
  for(u32 i = 0; i < NumeroDeVertices(G); i++)
    FijarColor(i, i, G);
  
  return 1;
}

char SwitchColores(Grafo G, u32 i, u32 j) {
  u32 cantidad_colores = 0;
  u32 *array_colores = calloc(NumeroDeVertices(G), sizeof(u32));
  for(u32 k = 0; k < NumeroDeVertices(G); k++) {
    if(Color(k, G) > cantidad_colores)
      cantidad_colores = Color(k, G);
  }
  // le sumo uno, pues cantidad_colores = color_max + 1
  cantidad_colores += 1;
  if(i > cantidad_colores || j > cantidad_colores)
    return 1;
  else {
    for(u32 k = 0; k < NumeroDeVertices(G); k++) {
      if(Color(k, G) == i)
        FijarColor(j, k, G);
      else if(Color(k, G) == j)
        FijarColor(i, k, G);
    }
  }
  free(array_colores);

  return 0;
}

static u32 IsIn(u32 e, u32 *array, u32 N) {
  for (u32 i = 0; i < N; i++) {
    if(array[i] == e)
      return 1;
  }

  return 0;
}

// ésta función retorna el color minimo no usado
// pej: a = [0,1,3,4]; BuscarMinNoUsado(a, 4, cantidad_colores) = 2
static u32 BuscarMinNoUsado(u32 *array, u32 N, u32 cantidad_colores) {
  for (u32 i = 0; i < N; i++) {
    if (!IsIn(i, array, N))
      return i;
  }
  // si no hay color disponible, genero uno nuevo
  if(cantidad_colores != N)
    cantidad_colores = N;

  return cantidad_colores;
}

u32 Greedy(Grafo G) {
  u32 color_minimo = 0;
  u32 cantidad_colores = 1;
  u32 *colores = (u32 *) calloc(NumeroDeVertices(G), sizeof(u32));
  u32 *colores_vecinos = NULL;
  for (u32 i = 0; i < NumeroDeVertices(G); i++)
    FijarColor(-1u, i, G);

  for(u32 i = 0; i < NumeroDeVertices(G); i++) {
    colores_vecinos = calloc(Grado(i, G), sizeof(u32));
    for(u32 j = 0; j < Grado(i, G); j++)
      colores_vecinos[j] = ColorVecino(j, i, G);
    // busco el color que sus vecinos no tienen
    color_minimo = BuscarMinNoUsado(colores_vecinos, Grado(i, G), 
            cantidad_colores);
    // actualizo cantidad de colores
    if(!IsIn(color_minimo, colores, cantidad_colores)) {
      cantidad_colores += 1;
      colores[cantidad_colores - 1u] = color_minimo;
    }
    FijarColor(color_minimo, i, G);
    free(colores_vecinos);
  }
  free(colores);

  return cantidad_colores;
}

//--- FUNCIONES SOBRE CCs --- //
// apila los visitados, comenzando por vértice i del orden interno
static u32 DFS(u32 i, Grafo G, u32 **apilados, u32 *numap) {
  Pila *pila = CrearPila();
  if(!pila)
    return 1;
  Apilar(pila, i);
  (*numap) += 1;
  (*apilados)[i] = 1;
  u32 p = 0, q = 0, existe = 0;
  while(!EstaVacia(pila)) {
    // indice del orden interno de vertice en la cima
    p = Cima(pila); 
    //si tengo numvertices vecinos, salgo pues comp conexas == 1 
    if(Grado(p, G) == NumeroDeVertices(G) - 1u) {
      for (u32 i = 0; i < NumeroDeVertices(G); i++)
        (*apilados)[i] = 1;
      (*numap) = NumeroDeVertices(G);
      break;
    }
    existe = 0;
    for(u32 j = 0; j < Grado(p, G); j++) {
      // q es el vecino j de p (primer elm de la pila)
      q = OrdenVecino(j, p, G); 
      if(!(*apilados)[q]) {
        existe = 1;
        Apilar(pila, q);
        (*numap) += 1;
        (*apilados)[q] = 1;
        break;
      }
    }
    if(!existe)
      Desapilar(pila);
  }
  DestruirPila(pila);

  return 0;
}

u32 NumCCs(Grafo G) {
  u32 count = 0;
  // número de apilados, lo uso para hacer chequeos de casos particulares
  u32 numap = 0;
  // apilados[i] == 1 quiere decir que el vertice i del orden interno
  // fue apilado(visitado), de lo contrario == 0
  u32 *apilados = calloc(NumeroDeVertices(G), sizeof(u32));

  for(u32 i = 0; i < NumeroDeVertices(G); i++) {
    if(numap == NumeroDeVertices(G))
      break;
    else if(!apilados[i]) {
      // por si hay algún error
      if(DFS(i, G, &apilados, &numap))
        return -1u;
      count++;
    }
  }
  free(apilados);

  return count;
}
