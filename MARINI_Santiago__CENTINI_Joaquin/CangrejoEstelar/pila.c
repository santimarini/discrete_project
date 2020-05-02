#include <stdlib.h>
#include "veinteveinte.h"
#include "pila.h"
#include <assert.h>

Pila *CrearPila() {
  Pila* pila = (Pila *) calloc(1, sizeof(Pila));
  pila->cima = NULL;
  pila->longitud = 0;
  return pila;
}

void DestruirPila(Pila *pila) {
  if(pila != NULL) {
    while(pila->cima != NULL)
      Desapilar(pila);

    free(pila);
  }
}

Elemento *CrearElemento(u32 v) {
  Elemento* elemento = (Elemento *) malloc(sizeof(Elemento));
  elemento->vertice = v;
  elemento->siguiente = NULL;
  return elemento;
}

void DestruirElemento(Elemento *elemento) {
  if(elemento != NULL) {
    elemento->siguiente = NULL;
    free(elemento);
  }
}

void Apilar(Pila *pila, u32 v) {
  assert(pila != NULL);
  Elemento* elemento = CrearElemento(v);
  elemento->siguiente = pila->cima;
  pila->cima = elemento;
  pila->longitud++;
}

void Desapilar(Pila *pila) {
  assert(pila != NULL);
  Elemento *eliminar = pila->cima;
  pila->cima = pila->cima->siguiente;
  DestruirElemento(eliminar);
  pila->longitud--;
}

u32 Cima(Pila *pila) {
  assert(pila != NULL);
  if(pila->cima == NULL)
      return 0;
  else
      return pila->cima->vertice;
}

u32 Longitud(Pila *pila) {
  assert(pila != NULL);
  return pila->longitud;
}

int EstaVacia(Pila *pila) {
  assert(pila != NULL);
  return pila->longitud == 0;
}
