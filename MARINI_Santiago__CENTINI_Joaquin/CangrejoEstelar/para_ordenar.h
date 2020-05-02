#ifndef _PARA_ORDENAR_H
#define _PARA_ORDENAR_H

// ésta estructura auxiliar nos ayudará para las funciones de reorden
struct ParaOrdenarA {
  u32 nombre;  // nombre del vértice
  u32 informacion;  // información de interés del vértice, sea grado o color
  u32 coloreo_cardinal; // campo que denota la cantidad de vértices que hay
                        // pintados con el mismo color que el vértice en
                        // cuestión
  u32 indice;  // índice que le corresponde al vértice en cuestión en el orden
               // natural
};

typedef struct ParaOrdenarA *ParaOrdenar;

#endif
