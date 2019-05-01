#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> //Librería que utilizo para cambiar todo a mayúscula.


 /*Definimos estructura*/
typedef struct _Node {
  char letter;
  int frequency;
  struct _Node *left;
  struct _Node *right;
} Node;
/*Declaramos prototipo de las funciones*/

void menu();


int main(){
  menu();
  system("PAUSE");
  return 0;
}

void menu(){
  
}