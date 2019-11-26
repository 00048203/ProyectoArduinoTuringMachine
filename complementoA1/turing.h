#ifndef _TURING_H_
#define _TURING_H_
  
// Estado
typedef struct {
  char *nombre;
} estado;

// Transicion
typedef struct {
  estado *inicial;
  char simbolo;
  char reemplazo;
  char direccion;
  estado *siguiente;
} transicion;

// Maquina
typedef struct {
  estado *inicial;
  transicion **transiciones;
  estado *final;
  char *inputSymbols;
  char blank;
} maquina;

// Cabeza
typedef struct {
  char *cinta;
  int posicion;
  estado *actual;
} cabeza;

#ifdef __cplusplus
extern "C"{
#endif

maquina * maquina_alloc();
void crear_maquina(maquina **m);
void eliminar_maquina(maquina *m);
int movimientos_maquina(maquina *m, cabeza *head);

void crear_transicion(transicion **t);
void eliminar_transicion(transicion *t);
void iniciar_transicion(transicion *t, estado *inicial, char simbolo, char reemplazo, char direccion, estado *q);
void crear_estado(estado **s, char *nombre);
void eliminar_estado(estado *s);
cabeza * cabeza_alloc();
void crear_cabeza(cabeza **head);
void eliminar_cabeza(cabeza *head);

#ifdef __cplusplus
} // extern "C"
#endif
#endif
