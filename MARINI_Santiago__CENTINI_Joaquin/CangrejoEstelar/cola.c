#include <stdlib.h>
#include "GrafoSt2020.h"
#include "cola.h"
#include "veinteveinte.h"

ElementoC *CrearElementoC(u32 v,u32 i){
    ElementoC *elemento = (ElementoC *)malloc(sizeof(ElementoC));
    elemento->vertice = v;
    elemento->indice = i;
    elemento->siguiente = NULL;
    return elemento;
}

void DestruirElementoC(ElementoC *elemento){
    elemento->siguiente = NULL;
    free(elemento);
}

void Encolar(Cola *cola, u32 v, u32 i){
    ElementoC *elemento = CrearElementoC(v,i);
    if(!cola->primer){
        cola->primer = elemento;
        cola->ultimo = elemento;
    }
    else{
        cola->ultimo->siguiente = elemento;
        cola->ultimo = elemento;
    }
    cola->longitud++;
}

void Eliminar(Cola *cola){
    if(cola->primer){
        ElementoC *eliminado = cola->primer;
        cola->primer = cola->primer->siguiente;
        DestruirElementoC(eliminado);
        cola->longitud--;

        if(!cola->primer){
            cola->ultimo = NULL;
        }
    }
}

Cola *CrearCola(){
    Cola* cola = (Cola *) malloc(sizeof(Cola));
    cola->primer = NULL;
    cola->ultimo = NULL;
    cola->longitud = 0;
    return cola;
}

void DestruirCola(Cola *cola){
    while(cola->primer){
        Eliminar(cola);
    }
    free(cola);
}

u32 PrimerElemento(Cola *cola){
    if(cola->primer){
        return cola->primer->vertice;
    }
    else{
        return 0;
    }
}

u32 IndiceDelPrimero(Cola *cola){
    if(cola->primer){
        return cola->primer->indice;
    }
    else{
        return 0;
    }
}

u32 LongitudC(Cola* cola){
    return cola->longitud;
}

int EstaVaciaC(Cola* cola){
    return cola->longitud == 0;
}