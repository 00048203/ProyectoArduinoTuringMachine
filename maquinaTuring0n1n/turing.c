#include "turing.h"
#include <string.h>
#include <stdlib.h>

/*Funciones para la Cinta*/

maquina * maquina_alloc() {
  return calloc(sizeof(maquina), 1);
}
//Asignando espacio en memoria para la Cinta
void crear_maquina(maquina **m) {
  *m = calloc(sizeof(maquina), 1);
}
//Liberar espacio en memoria
void eliminar_maquina(maquina *m) {
  free(m);
}

int movimientos_maquina(maquina *m, cabeza *head) {
  if (head->actual == m->final) return 0;
  transicion *t, **tr = m->transiciones;
  while (*tr != 0) {
    t = *tr;
    if (t->inicial == head->actual && t->simbolo == *(head->cinta + head->posicion)) {
      *(head->cinta + head->posicion) = t->reemplazo;
      head->posicion += t->direccion;
      head->actual = t->siguiente;
      break;
    }
    tr++;
  }
  
  return 1;
}



// Asignar en memoria la transicion

void crear_transicion(transicion **t) {
  *t = calloc(sizeof(transicion), 1);
}


// Eliminar la transicion

void eliminar_transicion(transicion *t) {
  free(t);
}



void iniciar_transicion(transicion *t, estado *inicial, char simbolo, char reemplazo, char direccion, estado *siguiente) {
  t->inicial = inicial;
  t->simbolo = simbolo;
  t->reemplazo = reemplazo;
  t->direccion = direccion;
  t->siguiente = siguiente;
}


void crear_estado(estado **s, char *nombre) {
  estado *new = calloc(sizeof(estado), 1);
  
  if (nombre) {
    new->nombre = calloc(sizeof(char), strlen(nombre) + 1);
    strcpy(new->nombre, nombre);
  }
  
  *s = new;
}

void eliminar_estado(estado *s) {
  if (s->nombre) {
    free(s->nombre);
  }

  free(s);
}

cabeza * cabeza_alloc() {
  return calloc(sizeof(cabeza), 1);
}

void crear_cabeza(cabeza **head) {
  *head = calloc(sizeof(cabeza), 1);
}


void eliminar_cabeza(cabeza *head) {
  if (head->cinta) {
    free(head->cinta);
  }

  free(head);
}

