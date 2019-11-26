#include "turing.h"
#include <LiquidCrystal.h>

//PINES LCD ARDUINO ---------------------------------
int rsPin = 12;
int ePin = 11;
int d4Pin = 5;
int d5Pin = 4;
int d6Pin = 3;
int d7Pin = 2;
int redPin = 6 ;
int greenPin = 7 ;
int bluePin = 8 ;
LiquidCrystal lcd(rsPin, ePin, d4Pin, d5Pin, d6Pin, d7Pin);
////////////////////////////////////////////////////////////

maquina *m;
estado *q0, *q1, *q2, *q3, *qF;
transicion *t0, *t1, *t2, *t3, *t4, *t5, *t6, *t7, *t8, *t9;
cabeza *head;
int contador = 1;


//CADENA INGRESADA A EVALUAR
  char *t = "000001111";


void setup() {
  pinMode(redPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(bluePin,OUTPUT);
  digitalWrite(bluePin, HIGH);
  digitalWrite(greenPin, HIGH);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Maquina Turing");
  lcd.setCursor(0,1);
  lcd.print("0^n 1^n, n>=1");
  delay(4000);
  m = maquina_alloc();
  
  crear_estado(&q0, "q0");
  crear_estado(&q1, "q1");
  crear_estado(&q2, "q2");
  crear_estado(&q3, "q3");
  crear_estado(&qF, "qF");
  
  //Right =1, Left =-1
  //iniciar_transicion(nombre_transicion, estado_origen, simbolo, reemplazo, movimiento, estado_destino)
  crear_transicion(&t0);
  iniciar_transicion(t0, q0, '0', 'X', 1, q1);
  
  crear_transicion(&t1);
  iniciar_transicion(t1, q1, '0', '0', 1, q1);
  
  crear_transicion(&t2);
  iniciar_transicion(t2, q1, 'Y', 'Y', 1, q1);
  
  crear_transicion(&t3);
  iniciar_transicion(t3, q1, '1', 'Y', -1, q2);
  
  crear_transicion(&t4);
  iniciar_transicion(t4, q2, '0', '0', -1, q2);
  
  crear_transicion(&t5);
  iniciar_transicion(t5, q2, 'Y', 'Y', -1, q2);
  
  crear_transicion(&t6);
  iniciar_transicion(t6, q2, 'X', 'X', 1, q0);
  
  crear_transicion(&t7);
  iniciar_transicion(t7, q0, 'Y', 'Y', 1, q3);
  
  crear_transicion(&t8);
  iniciar_transicion(t8, q3, 'Y', 'Y', 1, q3);
  
  crear_transicion(&t9);
  iniciar_transicion(t9, q3, m->blank, m->blank, 0, qF);
  
  m->inicial = q0;
  m->final = qF;

  //Dependiendo de la palabra hay que cambiar el tamaño de memoria para asignar a las transiciones por defecto se deja en 11. 
  m->transiciones = (transicion**)calloc(sizeof(transicion*), 11);
  
  m->transiciones[0] = t0;
  m->transiciones[1] = t1;
  m->transiciones[2] = t2;
  m->transiciones[3] = t3;
  m->transiciones[4] = t4;
  m->transiciones[5] = t5;
  m->transiciones[6] = t6;
  m->transiciones[7] = t7;
  m->transiciones[8] = t8;
  m->transiciones[9] = t9;

  m->inputSymbols = "01";
  m->blank = ' ';
  
  head = cabeza_alloc();
  head->actual = q0;

  head->cinta = (char *)calloc(sizeof(char), strlen(t) + 1);
  strcpy(head->cinta, t);
  
  head->posicion = 0;
  
  
}


void loop() {
   if (contador) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(head->actual->nombre);
    lcd.print(": ");
    lcd.print(head->cinta);
    
    char *pos = (char *)malloc(sizeof(char) * head->posicion + 2);
    int i;
    for (i = 0; i < head->posicion; i++) {
      *(pos + i) = ' ';
    }
    *(pos + head->posicion) = '^';
    *(pos + head->posicion + 1) = 0;

    lcd.setCursor(4,1);
    lcd.print(pos);
    delay(1000);

    free(pos);
  } else {
    if(head->actual = qF){
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, LOW);
    
    }
  
    delay(5000);
  }
  
  contador = movimientos_maquina(m, head);
}
