#ifndef GRAFOST2020_H
#define GRAFOST2020_H
#define u32 unsigned long int

struct GrafoSt {
    u32 nVertices;
    u32 nLados;
	  u32 delta;
    struct VerticeSt *vertices;
    struct VerticeSt *orden_creciente;
};

struct VerticeSt {
    u32 nombre;
    u32 grado;
    u32 color;
    struct VerticeSt *vecinos;
};

struct LadoSt{
	u32 extremo1;
	u32 extremo2;
};

#endif
