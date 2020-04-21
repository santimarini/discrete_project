typedef struct elementoc{
    u32 vertice;
    u32 indice;
    struct elementoc *siguiente;
} ElementoC;

typedef struct cola{
    ElementoC *primer;
    ElementoC *ultimo;
    u32 longitud;
} Cola;



ElementoC *CrearElementoC(u32 v,u32 i);

void DestruirElementoC(ElementoC *elemento);
void Encolar(Cola *cola, u32 v, u32 i);
void Eliminar(Cola *cola);
Cola *CrearCola();
void DestruirCola(Cola *cola);
u32 PrimerElemento(Cola *cola);
u32 IndiceDelPrimero(Cola *cola);
u32 LongitudC(Cola* cola);
int EstaVaciaC(Cola* cola);
