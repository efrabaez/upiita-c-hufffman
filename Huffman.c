/**
 * Author:    Efrain
 * Created:   01/05/2019
 * 
 * (c) Copyright by Efraín.
 * Please red READ.ME FILE
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef struct _Nodo{
	char letter;
	int frequency;
	struct _Nodo *next;
	struct _Nodo *prev;
	struct Nodo *ptree;
	struct _nodoB *pbin;
}List;

typedef struct _nodoB{
	int data;
	struct _nodoB *next;
	struct _nodoB *prev;
}Binary;

typedef struct Nodo{
    char letter;
    int frequency;
    struct Nodo *left;
    struct Nodo *right;
}Tree;

/*Prototype of functions*/

/*List functions*/
List *allocateMemory(char, int);
int theSize(List *);
List *pushLast(char, int, List *, Tree *);
List *searchItem(char, List *);
List *letters(char [],List *);
List *sortList(List *);
void show(List *,int);

/*Binary list functions*/
Binary *allocateMemoryB(int);
Binary *PushB(int, Binary *);
void Bin(char [],List **);
void readBinary(List **);
void showB(Binary **);
void createSentence(List **,int [],int );
void showBin(List **lb);

/*Binary Search Tree functions*/
Tree *allocateMemoryBST(char, int);
Tree *pushBST(List *, Tree *);
void preOrder(Tree *);
void writeBSTFile(Tree *,FILE *);
List *readBSTFILE(List *,FILE *);
Tree *createBST(Tree *, List **);
Tree *registerBST(List **,Tree *);



int main() {
  FILE *archivo;
    List *l =NULL ,*l2=NULL,*LB=NULL;
    Tree *r =NULL,*rb = NULL;
    char frase[100];
    int opc = 0;

    do{
        printf("1.Codificar\n2.Decodificar\n-1.Salir\n\n");
        scanf("%d",&opc);
        switch(opc)
        {
            case 1:
                printf("Inserta una frase: \n");
                fflush(stdin);
                gets(frase);
                strupr(frase);
                l=letters(frase,l);
                printf("\n\n");
                show(l,1);
                l=sortList(l);
                l2=l;
                printf("\n\n");
                show(l2,1);

                r=pushBST(l,r);
                printf("\n\n\nLista total\n\n");
                show(l,1);

                printf("\n\n");
                preOrder(r);

                archivo=fopen("Arbol.txt","w");
                writeBSTFile(r,archivo);
                fclose(archivo);

                archivo=fopen("Arbol.txt","r");
                if(archivo==NULL){
                    printf("\nEl archivo no existe\n");
                }
                else{
                    LB=readBSTFILE(LB,archivo);
                }
                fclose(archivo);

                printf("\n\n");
                show(LB,2);

               printf("\n\nArbol desde lista\n");
                rb=registerBST(&LB,rb);
                preOrder(rb);
                printf("\n");
                showBin(&LB);
                Bin(frase,&LB);
            break;
            case 2:
                LB=NULL;
                rb=NULL;
                //Lee el archivo preorder
                archivo=fopen("Arbol.txt","r");
                if(archivo==NULL){
                    printf("\nEl archivo no existe\n");
                }
                else{
                    LB=readBSTFILE(LB,archivo);
                }
                fclose(archivo);
                printf("\n\n");
                show(LB,2); //Muestra la lista desde el archivo preorder
                printf("\n\nArbol desde lista\n");
                rb=registerBST(&LB,rb);
                preOrder(rb);
                printf("\nCodigo binario\n");
                showBin(&LB); //Muestra los 0 y 1 para cada letra

                readBinary(&LB);
            break;
        }
        system("pause");
        system("cls");
    }while(opc!=-1);

    return 0;








  system("PAUSE");
  return 0;
}


/*Here start program functions*/

/*List functions*/
List *allocateMemory(char _letter, int _frequency){
	List *newNode=NULL;

	newNode = (List *)malloc(sizeof (List));
	newNode->letter=_letter;
	newNode->frequency=_frequency;
	newNode->next=NULL;
	newNode->prev=NULL;
	newNode->ptree=NULL;
	newNode->pbin=NULL;

	return newNode;
}

int theSize(List *_list){
  int listSize = 0;

  while(_list){
    listSize++;
    _list=_list->next;
  }

  return listSize;
}

List *pushLast(char _letter, int _frequency, List *_list, Tree * _father){
 List *newNode = NULL, *listAux = NULL;
  
  newNode = allocateMemory(_letter, _frequency);
  if (!_list){
    _list = newNode;
  }
  else{
    listAux = _list;
    while(listAux->next){
      listAux=listAux->next;
    }
    listAux->next = newNode;
    newNode->prev = listAux;
    newNode->ptree = _father;
  }

  return _list;
}

List *searchItem(char _letter, List * _list){
  List *aux= NULL;
  int i=0; 

  aux=_list;
  while(aux){
    if(aux->letter==_letter){
      i++;
    }
    aux=aux->next;
  }
  if(i>0){
    aux=_list;
    while(aux){
      if(aux->letter == _letter){
        aux->frequency=aux->frequency+1;
      }
        aux=aux->next;
    }
  }else{
    _list=pushLast(_letter,1,_list,NULL);
  }

  return _list;
}

List *letters(char _sentence[],List *_list){
  int i=0;
  

  while(_sentence[i] != '\0'){
    if(i==0){
       _list=pushLast(_sentence[i],1,_list,NULL);
    }else {
      _list=searchItem(_sentence[i],_list);
      
    }
    i++;
  }
  
  return _list;
}

List *sortList(List *_list){
  List *nodeAux=NULL,*nodeAux2=NULL, *pos=NULL;
  Tree *father=NULL;
  int lSize = 0,i = 0,frequency = 0;
  char letter;

  nodeAux=_list;
  nodeAux2=_list;
  pos=_list;

  lSize=theSize(_list);
  for(i=0;i<lSize;i++) {
    frequency=nodeAux->frequency;
    letter=nodeAux->letter;
    father=nodeAux->ptree;
    nodeAux2=nodeAux->prev;
    while(nodeAux2!=NULL && (nodeAux2->frequency)>frequency) {
      nodeAux->frequency=nodeAux2->frequency;
      nodeAux->letter=nodeAux2->letter;
      nodeAux->ptree=nodeAux2->ptree;
      nodeAux=nodeAux->prev;
      nodeAux2=nodeAux->prev;
    }
    nodeAux->frequency=frequency;
    nodeAux->letter=letter;
    nodeAux->ptree=father;
    pos=pos->next;
    nodeAux=pos;
  }

    return _list;
}

void show(List *_list, int _c){
  
  if(!_list){
		printf("Lista vacia\n");
	}else{
	  if(_c==1){
      while(_list!=NULL){
        printf("%c=%d=%d  ",_list->letter,_list->frequency,_list->ptree);
        _list=_list->next;
      }
	  }else if(_c==2){
      while(_list!=NULL){
        printf("%c=%d ",_list->letter,_list->frequency);
        _list=_list->next;
      }
    }
  }
}


/*Binary list functions*/
Binary *allocateMemoryB(int _data){
	Binary *newNode;

	newNode=(Binary *)malloc(sizeof(Binary));
	newNode->data=_data;
	newNode->next=NULL;
	newNode->prev=NULL;

	return newNode;
}

Binary *PushB(int _data, Binary *_start){
	Binary *newNode, *auxNode;

	newNode=allocateMemoryB(_data);
	if(!_start){
        _start=newNode;
	}else{
        auxNode=_start;
        while(auxNode->next!=NULL)
        {
           auxNode=auxNode->next;
        }
        auxNode->next=newNode;
        newNode->prev=auxNode;
    }

	return _start;
}

void Bin(char _sentence[],List **_list){
  FILE *archivo=NULL;
  List *listAux=NULL;
  Binary *binaryAux=NULL;

  listAux=(*_list);
  int i=0,b[300]={0},j=0,k=0,baux[8]={0},c=0,l,d=0,dec[100]={0},ax=0,total=0;
  char *charac;
  while(_sentence[i]!='\0'){//Sustituye los 0 y 1 en la frase
    while(listAux){
      if(listAux->letter==_sentence[i]){
        binaryAux=listAux->pbin;
        while(binaryAux){
          b[j]=binaryAux->data;
          binaryAux=binaryAux->next;
          j++;
        }
      }
      listAux=listAux->next;
    }
    listAux=(*_list);
    i++;
  }
  total=i;
  printf("\nTotal frase:%d ",total);
  printf("\n\nFrase binaria\n");
  for(i=0;i<j;i++) {
    printf("%d",b[i]);
  }
    /*Binary to decimal*/
  ax=j;
  for(i=0;i<j;i++) {
    baux[k]=b[i];//pasa 8 binarios a auxiliar
    if(k==7){
      l=7;
      for(k=0;k<=7;k++) {
        if(baux[k]==1){
          d=d+(baux[k]*pow(2,l));
        }
        l--;
      }
      dec[c]=d;//Pasa el decimal a dec
      c++;
      d=0;
      k=0;
      ax-=8;
    }else{
      k++;
    }
  }
  printf("\nvalor ax: %d",ax);
  if(ax<8 && ax>=0) {
    for(k=ax;k<8;k++){//Rellena los 0 que hagan falta
      baux[k]=0;
    }
    l=7;
    d=0;
    for(k=0;k<=7;k++) {
      if(baux[k]==1){
        d=d+(baux[k]*pow(2,l));
      }
      l--;
    }
    dec[c]=d;
  }
  i=0;
  printf("Valor de c: %d\n",c);
  printf("\nNumeros decimales\n");
  charac=(char*)malloc(c*sizeof(char));
  for(i=0;i<=c;i++) {
    charac[i]=dec[i];
    printf("%d ",dec[i]);
  }
  /* Imprime frase cifrada */
  archivo=fopen("sentenceCode.txt","w");
  for(i=0;i<=c;i++) {
    fputc(charac[i],archivo);
  }
  fclose(archivo);
}

void readBinary(List ** _binaryList){
  List *aux=NULL;
  FILE *fp=NULL;
  char code[100],t;
  int i,total=0,*decimal,*binary,k=0,j=0,nt=0;

  aux=(*_binaryList);
  fp=fopen("sentenceCode.txt","r");
  if(!fp){
    printf("Archivo inexistente\n");
  }else{
    i=0;
    while(feof(fp)==0) {
      fscanf(fp,"%c",&code[i]);
      i++;
    }
    fclose(fp);
    printf("\n\nCodigo del archivo: \n");
    for(j=0;j<(i-1);j++) {
      printf("%d ",code[j]);
    }
    decimal=(int*)malloc((i)*sizeof(int));
    total=i;
    printf("Valor de total: %d\n",total);
    for(i=0;i<(total-1);i++) {
      decimal[i]=code[i];
      if(decimal[i]<0){
        decimal[i]+=256;
      }
      printf("%d ",decimal[i]);
    }
    //Convirtiendo a binario
    binary=(int*)malloc((total*8)*sizeof(int));
    k=0;
    for(i=0;i<(total-1);i++) {
      int temporal[8]={0};
      for(j=0;decimal[i]!=0;j++){
        temporal[j]=decimal[i]%2;
        decimal[i]=decimal[i]/2;
      }
      j=7;
      while(j>=0){
        binary[k]=temporal[j];
        j--;
        k++;
      }
    }
    //Arreglo con numeros binarios
    printf("\n\nNumeros binarios: \n");
    for(i=0;i<k;i++) {
      printf("%i",binary[i]);
    }
  }
  printf("\n%d",i);
  createSentence(&aux,binary,i);
}
void showB(Binary **_start){
 Binary *binaryAux = NULL;
  
  binaryAux=(*_start);
	if(!binaryAux){
		printf("Lista vacia\n");
	}else{
    while(binaryAux){
      printf("%i ",binaryAux->data);
      binaryAux=binaryAux->next;
    }
  }  
}
void createSentence(List **_list,int _binSentence[],int _total){
  List *listAux;
  Binary *binaryAux;
  int i=0,pos1=0,pos2=0,cont=0,root=0;
  char sentence[100]={'0'};

  listAux=(*_list);
  root=listAux->frequency;
  while(pos1!=root) {
    cont=0;
    if(listAux->letter!='-'){
      binaryAux=listAux->pbin;
      while(binaryAux!=NULL) {
        if(binaryAux->data==_binSentence[i]){
          if(binaryAux->next==NULL){
            sentence[pos1]=listAux->letter;
            pos1++;
            _total-=(cont+1);
          }
          binaryAux=binaryAux->next;
          i++;
          cont++;
        }else {
          binaryAux=NULL;
          i=pos2;
        }
      }
    }
    listAux=listAux->next;
    if(!listAux){
      listAux=(*_list);
    }
    pos2=i;
  }
  printf("\nMensaje:\n");
  i=0;
  while(sentence[i]!=0) {
    printf("%c ",sentence[i]);
    i++;
  }  
}
void showBin(List **_binaryList){
  Binary *binaryAux;
  List *listAux;

  listAux=(*_binaryList);
    if(!listAux){
      printf("\nLista vacia\n");
    }
    while(listAux) {
      if(listAux ->pbin){
        printf("\n%c=",listAux ->letter);
        binaryAux=listAux->pbin;
        showB(&binaryAux);
      }
      listAux=listAux->next;
    }
}

/*Binary Search Tree functions*/
Tree *allocateMemoryBST(char _letter, int _frequency){
	Tree *newNode;
	newNode = (Tree *)malloc(sizeof (Tree));
	newNode->letter=_letter;
	newNode->frequency=_frequency;
  newNode->left=NULL;
  newNode->right=NULL;

	return newNode;
}
Tree *pushBST(List *_list, Tree *_root){
   List *aux, *aux2;
    Tree *Izq,*Der,*raiz;
    int suma;

    raiz=_root;
    aux=_list;
    while(aux->next!=NULL)
    {
        aux2=aux->next;
        if(aux->ptree==NULL && aux2->ptree==NULL)
        {
            Izq=allocateMemoryBST(aux->letter,aux->frequency);
            //printf("\n%c=%d",Izq->letra,Izq->frecuencia);
            Der=allocateMemoryBST(aux2->letter,aux2->frequency);
            //printf("\n%c=%d",Der->letra,Der->frecuencia);
            raiz=allocateMemoryBST('-',Izq->frequency+Der->frequency);
            raiz->left=Izq;
            raiz->right=Der;
            //printf("%c %d   %c %d",raiz->izquierda->letra,raiz->izquierda->frecuencia,raiz->derecha->letra,raiz->derecha->frecuencia);
        }
        if(aux->ptree!=NULL && aux2->ptree!=NULL)
        {
            suma=aux->ptree->frequency;
            //printf("\n%d",suma);
            suma+=aux2->ptree->frequency;
            //printf("\n%d",suma);
            raiz=allocateMemoryBST('-',suma);
            raiz->left=aux->ptree;
            raiz->right=aux2->ptree;
            //printf("%c %d   %c %d",raiz->izquierda->letra,raiz->izquierda->frecuencia,raiz->derecha->letra,raiz->derecha->frecuencia);
        }
        if(aux->ptree!=NULL && aux2->ptree==NULL)
        {
            Der=allocateMemoryBST(aux2->letter,aux2->frequency);
            //printf("\n%c=%d",Der->letra,Der->frecuencia);
            //printf("\n%c=%d",aux->parbol->letra,aux->parbol->frecuencia);
            suma=aux->ptree->frequency;
            //printf("\n%d",suma);
            suma+=Der->frequency;
            //printf("\n%d",suma);
            raiz=allocateMemoryBST('-',suma);
            raiz->left=aux->ptree;
            raiz->right=Der;
            //printf("%c %d   %c %d",raiz->izquierda->letra,raiz->izquierda->frecuencia,raiz->derecha->letra,raiz->derecha->frecuencia);
        }
        if(aux->ptree==NULL && aux2->ptree!=NULL)
        {
            Izq=allocateMemoryBST(aux->letter,aux->frequency);
            //printf("\n%c=%d",Izq->letra,Izq->frecuencia);
            raiz=allocateMemoryBST('-',Izq->frequency+aux2->ptree->frequency);
            raiz->left=Izq;
            raiz->right=aux2->ptree;
            //printf("%c %d   %c %d",raiz->izquierda->letra,raiz->izquierda->frecuencia,raiz->derecha->letra,raiz->derecha->frecuencia);
        }
        _list=pushLast(raiz->letter,raiz->frequency,_list,raiz);
        //printf("\n");
        //Mostrar(li);
        //printf("\n");
        _list=sortList(_list);
        //printf("\n");
        //Mostrar(li);
        aux=aux2->next;
    }
    raiz=aux->ptree;
    return raiz;
}
void preOrder(Tree *_tree){
  if(_tree){
    printf("%c%d",_tree->letter,_tree->frequency);
    preOrder(_tree->left);
    preOrder(_tree->right);
  }
}

void writeBSTFile(Tree *_tree,FILE *_fp){
  if(_tree!=NULL) {
    fprintf(_fp,"%c %d ", _tree->letter, _tree->frequency);
    writeBSTFile(_tree->left, _fp);
    writeBSTFile(_tree->right, _fp);
  }  
}
List *readBSTFILE(List *_list,FILE *_fp){
  char letter,l2,space;
  int frequency=0;

  while(!feof(_fp)) {
    fscanf(_fp,"%c",&letter);
    if(letter==l2 && letter!='-'){
      return _list;
    }
    fscanf(_fp,"%c",&space);
    fscanf(_fp,"%d",&frequency);
    fscanf(_fp,"%c",&space);
    _list=pushLast(letter, frequency, _list, NULL);
    l2=letter;
  }

  return _list;
}
Tree *createBST(Tree *_root, List **_list){
  Tree *treeAux, *newTree;
  Binary *bin = NULL;
  int sum = 0;
  
  newTree=allocateMemoryBST((*_list)->letter,(*_list)->frequency);
  if(_root==NULL){
    return newTree;
  } 
  else{
    treeAux=_root;
    while(treeAux) {
      if(!treeAux->left && !treeAux->right) {
        treeAux->left=newTree;
        bin=PushB(0,bin);
        if(newTree->letter!='-') {
          (*_list)->pbin=bin;
        }
        return _root;
      }
      if(treeAux->right!=NULL) {
       treeAux=treeAux->right;
       bin=PushB(1,bin);
      }else {
        sum=treeAux->left->frequency+newTree->frequency;
        if(treeAux->frequency==sum) {
          treeAux->right=newTree;
          bin=PushB(1,bin);
          if(newTree->letter!='-') {
            (*_list)->pbin=bin;
          }
          return _root;
        }else {
          treeAux=treeAux->left;
          bin=PushB(0,bin);
        }
      }
    }
  }
}
Tree *registerBST(List **_binaryList,Tree *_tree){
  List *listAux;
  listAux=(*_binaryList);
  
  while(listAux) {
    _tree=createBST(_tree,&listAux);
    listAux=listAux->next;
  }
  return _tree;
}