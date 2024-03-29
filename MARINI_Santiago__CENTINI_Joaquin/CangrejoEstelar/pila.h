#ifndef _PILA_H
#define _PILA_H

typedef struct elemento {
  u32 vertice;
  u32 indice;
  struct elemento *siguiente;
} Elemento;

typedef struct pila {
  Elemento *cima;
  u32 longitud;
} Pila;

// funciones sobre pila
Pila *CrearPila();
void DestruirPila(Pila* pila);
Elemento *CrearElemento(u32 v);
void DestruirElemento(Elemento *elemento);
void Apilar(Pila *pila, u32 v);
void Desapilar(Pila *pila);
u32 Cima(Pila *pila);
u32 IndiceCima(Pila *pila);
u32 Longitud(Pila *pila);
int EstaVacia(Pila *pila);


#endif
