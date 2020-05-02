#include <stdlib.h>
#include "veinteveinte.h"
#include "cola.h"
#include <assert.h>

ElementoC *CrearElementoC(u32 v) {
  ElementoC *elemento = (ElementoC *) malloc(sizeof(ElementoC));
  elemento->vertice = v;
  elemento->siguiente = NULL;
  return elemento;
}

void DestruirElementoC(ElementoC *elemento) {
  if(elemento != NULL) {
    elemento->siguiente = NULL;
    free(elemento);
  }
}

void Encolar(Cola *cola, u32 v) {
  assert(cola != NULL);
  ElementoC *elemento = CrearElementoC(v);
  if(!cola->primer) {
    cola->primer = elemento;
    cola->ultimo = elemento;
  } else {
    cola->ultimo->siguiente = elemento;
    cola->ultimo = elemento;
  }
  cola->longitud++;
}

void Desencolar(Cola *cola) {
  assert(cola != NULL);
  if(cola->primer) {
    ElementoC *eliminado = cola->primer;
    cola->primer = cola->primer->siguiente;
    DestruirElementoC(eliminado);
    cola->longitud--;

    if(!cola->primer)
        cola->ultimo = NULL;
  }
}

Cola *CrearCola() {
  Cola* cola = (Cola *) malloc(sizeof(Cola));
  cola->primer = NULL;
  cola->ultimo = NULL;
  cola->longitud = 0;

  return cola;
}

void DestruirCola(Cola *cola) {
  if(cola != NULL) {
    while(cola->primer)
      Desencolar(cola);

    free(cola);
  }
}

u32 PrimerElemento(Cola *cola) {
  assert(cola != NULL);
  if(cola->primer)
    return cola->primer->vertice;

  return 0;
}

u32 LongitudC(Cola *cola) {
  assert(cola != NULL);
  return cola->longitud;
}

int EstaVaciaC(Cola *cola) {
  assert(cola != NULL);
  return cola->longitud == 0;
}
