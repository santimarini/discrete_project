#ifndef _COLA_H
#define _COLA_H

typedef struct elementoc {
    u32 vertice;
    struct elementoc *siguiente;
} ElementoC;

typedef struct cola {
    ElementoC *primer;
    ElementoC *ultimo;
    u32 longitud;
} Cola;

// funciones sobre cola 
ElementoC *CrearElementoC(u32 v);
void DestruirElementoC(ElementoC *elemento);
void Encolar(Cola *cola, u32 v);
void Desencolar(Cola *cola);
Cola *CrearCola();
void DestruirCola(Cola *cola);
u32 PrimerElemento(Cola *cola);
u32 IndiceDelPrimero(Cola *cola);
u32 LongitudC(Cola* cola);
int EstaVaciaC(Cola* cola);


#endif
