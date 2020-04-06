#ifndef GRAFOST2020_H
#define GRAFOST2020_H
#define u32 unsigned long int

struct GrafoSt {
    u32 nVertices;
    u32 nLados;
    u32 delta;
    struct __node *node;
    u32 *orden_interno;
    u32 *orden_natural;
};

struct __node 
{ 
  u32 key;
  struct VerticeSt *vert;
  struct __node *left; 
  struct __node *right; 
  int height; 
};

struct VerticeSt {
    u32 nombre;
    u32 grado;
    u32 color;
    struct VerticeSt **vecinos;
};

#endif
