#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_LIMIT 1000


 /*Definimos estructura*/
typedef struct _Node {
  char letter;
  int frequency;
  struct _Node *left;
  struct _Node *right;
} Node;

/*Declaramos prototipo de las funciones*/
void menu();
/*Funciones guardar información fila*/
Node * allocateMemory(char, int);
Node * pushFirst(Node *, char, int);
Node * pushLast(Node *, char, int);
Node * pushPosition(Node *, char, int, int);
Node * pushItem(Node *, char, int, int);
/*Funcion tamaño lista*/
int theSize(Node *);
/*Funcion buscar elemento*/
int searchItem(Node *, int);

void showAll(Node *);

/*Funciones del c{odigo de Huffman*/

Node * frequencyTable(char *);

int main(){
  menu();
  system("PAUSE");
  return 0;
}

void menu(){
  char sentence[MAX_LIMIT], fileName[20], c;
  int opt = 0, i=0;
  FILE *fp;

  do{
    printf("1.- Encode\n2.- Show encode\n3.- Decode\n4.- Show decode\n(-1).- Exit");
    printf("\nType your choice: ");
    scanf("%i", &opt);
    fflush( stdin );


    switch (opt) {
      case 1:
        printf("1.-Type sentence\n2.-Open from file\nType your choice: ");
        scanf("%i", &opt);
        fflush( stdin );
        switch (opt) {
          case 1:
            printf("Type sentence to encode:");     
            scanf ("%[^\n]%*c", sentence);
            while(sentence[i] != '\0'){
              sentence[i] = toupper(sentence[i]);
              if (sentence[i] == ' ') {
                sentence[i] = '_';
              }
              i++;
            }
            
            printf("The string in upper case: %s\n", sentence);
            frequencyTable(sentence);
          break;
          case 2:
            printf( "Type file name: " );
            gets(fileName);
            strcat(fileName, ".txt");
            puts(fileName);
            fp = fopen(fileName, "r");
            if ( fp == NULL ) {
              printf ( "Could not open file %s", fileName) ;
            }
            printf( "Reading the file %s", fileName ) ;
            while ( 1 ) {
              c = fgetc ( fp ) ; // reading the file
              if (c == EOF){
                break ;
              }
              sentence[i] = c;
              i++;
            }
            i=0;
            while(sentence[i] != '\0'){
              sentence[i] = toupper(sentence[i]);
              if (sentence[i] == ' ') {
                sentence[i] = '_';
              }
              i++;
            }
            printf("The string in upper case: %s\n", sentence);
            frequencyTable(sentence);            
            fclose ( fp ) ; // Closing the file

          break;
        }

      break;
      case 2:
        printf("Type sentence to encode: ");     
      break;

    }
  
   system("PAUSE");
  } while(opt != -1);

}


/*Aquí comienzan las funciones del programa*/

/*Inicio bloque insertar datos*/
Node *allocateMemory(char _letter, int _frequency){
	Node *newNode = NULL;
	newNode = (Node *) malloc (sizeof(Node));
	newNode->letter = _letter;
  newNode->frequency = _frequency;
	newNode->left = NULL;
  newNode->right = NULL;

	return newNode;
}

Node * pushFirst(Node *_list, char _letter, int _frequency){
  Node *newNode = NULL;
  newNode = allocateMemory(_letter, _frequency);
  if(_list){
    newNode->right = _list;
    _list->left = newNode;
    }
  return newNode;
}

Node * pushLast(Node *_list, char _letter, int _frequency){
  Node *newNode = NULL, *listAux = NULL;
  newNode = allocateMemory(_letter, _frequency);
  if (!_list){
    _list = newNode;
  }
  else{
    listAux = _list;
    while(listAux->right){
      listAux=listAux->right;
    }
    listAux->right = newNode;
    newNode->left = listAux;
  }
  return _list;
}

Node * pushPosition(Node *_list, char _letter, int _frequency, int _position){
  Node * newNode = NULL, *listAux = NULL;
  int listSize = 0, i = 0;
  listSize = theSize(_list);
  if (listSize){
    if (_position <= 0){
      _list = pushFirst(_list, _letter, _frequency);
    }else if (_position >= listSize){
      _list =  pushLast(_list, _letter, _frequency);
    }else{
      listAux = _list;
      newNode = allocateMemory(_letter, _frequency);
      for(i=1; i < _position; i++){
        printf("%i", i);
        listAux = listAux->right;
      }
      newNode->right = listAux->right;
      listAux->right->left = newNode;
      listAux->right = newNode;
      newNode->right = listAux;
    }  
  }else{
    _list =  pushFirst(_list, _letter, _frequency);
  }
  return _list;
}

Node * pushItem(Node *_list, char _letter, int _frequency, int _item){
  int position = 0;
  position = searchItem(_list, _item);
  _list = pushPosition(_list, _letter, _frequency, position);
  return _list;
}


/*Funciones auxiliares*/
int searchItem(Node * _list, int _data){
  int position = 0;
  while(_list){
    if (_list->letter == _data) {
      break;
    }
    _list = _list->right;
    position++;
  }
  return position;
}


int theSize(Node *_list){
  int listSize = 0;
  while(_list){
    listSize++;
    _list=_list->right;
  }
  return listSize;
}

void showAll(Node *_list){
  if (!_list){
    printf("Vacia");
  }
  while(_list){
    printf("Letra: %c\t Frecuencua: %i\n", _list->letter, _list->frequency);
    _list = _list->right;
  } 
}






/*Inicio bloque de Huffman*/

Node * frequencyTable(char *_sentence){
  Node *newNode = NULL, *listAux = NULL;
  int i = 0, a=0;
    while (_sentence[i] != '\0') {
      if(newNode == NULL){
        newNode = pushFirst(newNode, _sentence[i], 1);
      }else {    
        listAux = newNode;
        while(listAux->right) {
          if (listAux->letter == _sentence[i]) {
            listAux->frequency++;
            break;
          }
          listAux=listAux->right;
         }
         if (!listAux->right) {
           newNode = pushLast(newNode, _sentence[i], 1);
         }
      }
      i++;
    }
  showAll(newNode);
  return newNode;
}


