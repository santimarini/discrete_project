#ifndef GrafoSt2020_H
#define GrafoSt2020_H
#define u32 unsigned int
#endif


struct vertice{
	u32 nombre;
	u32 grado;
	u32 color;
	vertice *vecinos[];
}

struct GrafoST{
	u32 nvertices;
	u32 nlados;
	u32 delta;
	vertice *orden[nvertices];
}

