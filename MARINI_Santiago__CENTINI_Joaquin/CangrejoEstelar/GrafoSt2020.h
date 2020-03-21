#ifndef GRAFOST2020_H
#define GRAFOST2020_H
#define u32 unsigned long int




struct GrafoSt {
    u32 nVertices;
    u32 nLados;
	u32 delta;
    struct VerticeSt *vertices;
    u32 *orden; // es de tipo u32 por que solo necesitamos conocer el nombre del vertice
};

struct VerticeSt {
    u32 nombre;
    u32 grado;
    u32 color;
    u32 *vecinos; // es de tipo u32 solo necesitamos el nombre, luego buscar en el arreglo de vertices
};


#endif
