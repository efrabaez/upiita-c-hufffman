#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct _Nodo{
	char letra;
	int frecuencia;
	struct _Nodo *sig;
	struct _Nodo *ant;
	struct Nodo *parbol;
	struct _nodoB *pbin;
}Lista;

typedef struct _nodoB{
	int dato;
	struct _nodoB *sig;
	struct _nodoB *ant;
}Binario;

typedef struct Nodo{
    char letra;
    int frecuencia;
    struct Nodo *izquierda;
    struct Nodo *derecha;
}Arbol;

Lista *memoria(char c, int f)
{
	Lista *NuevoNodo;
	NuevoNodo = (Lista *)malloc(sizeof (Lista));
	NuevoNodo->letra=c;
	NuevoNodo->frecuencia=f;
	NuevoNodo->sig=NULL;
	NuevoNodo->ant=NULL;
	NuevoNodo->parbol=NULL;
	NuevoNodo->pbin=NULL;
	return NuevoNodo;
}
Binario *memoriaB(int d)
{
	Binario *NuevoNodo;
	NuevoNodo = (Binario *)malloc(sizeof (Binario));
	NuevoNodo->dato=d;
	NuevoNodo->sig=NULL;
	NuevoNodo->ant=NULL;
	return NuevoNodo;
}
Arbol *memoria2(char c, int f)
{
	Arbol *NuevoNodo;
	NuevoNodo = (Arbol *)malloc(sizeof (Arbol));
	NuevoNodo->letra=c;
	NuevoNodo->frecuencia=f;
    NuevoNodo->izquierda=NULL;
    NuevoNodo->derecha=NULL;
	return NuevoNodo;
}
int Tamanio(Lista *n)
{
    int i=0;
    if(n==NULL){
    	printf("Lista vacia\n");
	}
	else{
		do{
        	n=n->sig;
        	i++;
	    }while(n!=NULL);
	}
	return i;
}
Lista *InsertarF(int dato, char f, Lista *inicio, Arbol *p)
{
	Lista *nuevo, *aux;
	nuevo=memoria(dato,f);
	if(inicio==NULL){
        inicio=nuevo;
	}else{
        aux=inicio;
        while(aux->sig!=NULL)
        {
           aux=aux->sig;
        }
        aux->sig=nuevo;
        nuevo->ant=aux;
        nuevo->parbol=p;
    }
	return inicio;
}
Binario *InsertarB(int dato,Binario *inicio)
{
	Binario *nuevo, *aux;
	nuevo=memoriaB(dato);
	if(inicio==NULL){
        inicio=nuevo;
	}else{
        aux=inicio;
        while(aux->sig!=NULL)
        {
           aux=aux->sig;
        }
        aux->sig=nuevo;
        nuevo->ant=aux;
    }
	return inicio;
}
void Mostrar(Lista *inicio,int c)
{
	if(inicio==NULL){
		printf("Lista vacia\n");
	}else{
	    if(c==1){
            while(inicio!=NULL){
                printf("%c=%d=%d  ",inicio->letra,inicio->frecuencia,inicio->parbol);
                inicio=inicio->sig;
            }
	    }
	    else if(c==2){
            while(inicio!=NULL){
            printf("%c=%d ",inicio->letra,inicio->frecuencia);
            inicio=inicio->sig;}
        }
    }
}
void MostrarB(Binario **inicio)
{
    Binario *aux;
    aux=(*inicio);
	if(aux==NULL){
		printf("Lista vacia\n");
	}else{
        while(aux!=NULL){
            printf("%d ",aux->dato);
            aux=aux->sig;}
    }
}
void Preorder(Arbol *a)
{
    if(a!=NULL){
        printf("%c%d ",a->letra,a->frecuencia);
        Preorder(a->izquierda);
        Preorder(a->derecha);
    }
}
Lista *busqueda(char c, Lista *l)
{
    Lista *aux;
    aux=l;
    int i=0;
    while(aux!=NULL){
        if(aux->letra==c){i++;}
        aux=aux->sig;
    }
    if(i>0){
        aux=l;
        while(aux!=NULL){
            if(aux->letra==c){
                aux->frecuencia=aux->frecuencia+1;}
            aux=aux->sig;}
    }else{
        l=InsertarF(c,1,l,NULL);
    }
    return l;
}
Lista *letras(char f[],Lista *li)
{
    int i=0;
    while(f[i]!='\0')
    {
        if(i==0){
            li=InsertarF(f[i],1,li,NULL);}
        else{
            li=busqueda(f[i],li);}
        i++;
    }
    return li;
}
Lista *Ordena(Lista *li)
{
    Lista *aux,*pos,*aux2;
    Arbol *pa;

    aux=li;
    aux2=li;
    pos=li;
    int t,i,f;
    char d;

    t=Tamanio(li);
    for(i=0;i<t;i++)
    {
        f=aux->frecuencia;
        d=aux->letra;
        pa=aux->parbol;

        aux2=aux->ant;
        while(aux2!=NULL && (aux2->frecuencia)>f)
        {
            aux->frecuencia=aux2->frecuencia;
            aux->letra=aux2->letra;
            aux->parbol=aux2->parbol;
            aux=aux->ant;
            aux2=aux->ant;
        }
        aux->frecuencia=f;
        aux->letra=d;

        aux->parbol=pa;

        pos=pos->sig;
        aux=pos;
    }

    return li;
}
Arbol *Alta(Lista *li, Arbol *Raiz)
{
    Lista *aux, *aux2;
    Arbol *Izq,*Der,*raiz;
    int suma;

    raiz=Raiz;
    aux=li;
    while(aux->sig!=NULL)
    {
        aux2=aux->sig;
        if(aux->parbol==NULL && aux2->parbol==NULL)
        {
            Izq=memoria2(aux->letra,aux->frecuencia);
            //printf("\n%c=%d",Izq->letra,Izq->frecuencia);
            Der=memoria2(aux2->letra,aux2->frecuencia);
            //printf("\n%c=%d",Der->letra,Der->frecuencia);
            raiz=memoria2('-',Izq->frecuencia+Der->frecuencia);
            raiz->izquierda=Izq;
            raiz->derecha=Der;
            //printf("%c %d   %c %d",raiz->izquierda->letra,raiz->izquierda->frecuencia,raiz->derecha->letra,raiz->derecha->frecuencia);
        }
        if(aux->parbol!=NULL && aux2->parbol!=NULL)
        {
            suma=aux->parbol->frecuencia;
            //printf("\n%d",suma);
            suma+=aux2->parbol->frecuencia;
            //printf("\n%d",suma);
            raiz=memoria2('-',suma);
            raiz->izquierda=aux->parbol;
            raiz->derecha=aux2->parbol;
            //printf("%c %d   %c %d",raiz->izquierda->letra,raiz->izquierda->frecuencia,raiz->derecha->letra,raiz->derecha->frecuencia);
        }
        if(aux->parbol!=NULL && aux2->parbol==NULL)
        {
            Der=memoria2(aux2->letra,aux2->frecuencia);
            //printf("\n%c=%d",Der->letra,Der->frecuencia);
            //printf("\n%c=%d",aux->parbol->letra,aux->parbol->frecuencia);
            suma=aux->parbol->frecuencia;
            //printf("\n%d",suma);
            suma+=Der->frecuencia;
            //printf("\n%d",suma);
            raiz=memoria2('-',suma);
            raiz->izquierda=aux->parbol;
            raiz->derecha=Der;
            //printf("%c %d   %c %d",raiz->izquierda->letra,raiz->izquierda->frecuencia,raiz->derecha->letra,raiz->derecha->frecuencia);
        }
        if(aux->parbol==NULL && aux2->parbol!=NULL)
        {
            Izq=memoria2(aux->letra,aux->frecuencia);
            //printf("\n%c=%d",Izq->letra,Izq->frecuencia);
            raiz=memoria2('-',Izq->frecuencia+aux2->parbol->frecuencia);
            raiz->izquierda=Izq;
            raiz->derecha=aux2->parbol;
            //printf("%c %d   %c %d",raiz->izquierda->letra,raiz->izquierda->frecuencia,raiz->derecha->letra,raiz->derecha->frecuencia);
        }
        li=InsertarF(raiz->letra,raiz->frecuencia,li,raiz);
        //printf("\n");
        //Mostrar(li);
        //printf("\n");
        li=Ordena(li);
        //printf("\n");
        //Mostrar(li);
        aux=aux2->sig;
    }
    raiz=aux->parbol;
    return raiz;
}
void GenArchivo(Arbol *a,FILE *ar) //Arbol en preorder
{
    if(a!=NULL)
    {
        fprintf(ar,"%c %d ",a->letra,a->frecuencia);
        GenArchivo(a->izquierda,ar);
        GenArchivo(a->derecha,ar);
    }
}
Lista *LeerArbol(Lista *l,FILE *ar)//Crea lista desde el archivo
{
    char letra,l2,space;
    int fre;

    while(!feof(ar))
    {
        fscanf(ar,"%c",&letra);
        if(letra==l2 && letra!='-'){
            return l;
        }
        fscanf(ar,"%c",&space);
        fscanf(ar,"%d",&fre);
        fscanf(ar,"%c",&space);
        l=InsertarF(letra,fre,l,NULL);
        l2=letra;
    }
    return l;
}
Arbol *GenArbol(Arbol *raiz, Lista **l)//Crea arbol desde preorder y saca los 1 y 0
{
    Arbol *aux, *nuevo;
    Binario *bin;
    bin=NULL;
    nuevo=memoria2((*l)->letra,(*l)->frecuencia);
    int sum;
    if(raiz==NULL) return nuevo;
    else{
        aux=raiz;
        while(aux!=NULL)
        {
            if(aux->izquierda==NULL && aux->derecha==NULL)
            {
                aux->izquierda=nuevo;
                bin=InsertarB(0,bin);
                if(nuevo->letra!='-'){
                    (*l)->pbin=bin;
                }
                return raiz;
            }
            if(aux->derecha!=NULL)
            {
                aux=aux->derecha;
                bin=InsertarB(1,bin);
            }
            else
            {
                sum=aux->izquierda->frecuencia+nuevo->frecuencia;
                if(aux->frecuencia==sum){
                    aux->derecha=nuevo;
                    bin=InsertarB(1,bin);
                    if(nuevo->letra!='-'){
                        (*l)->pbin=bin;
                    }
                    return raiz;
                }
                else{
                    aux=aux->izquierda;
                    bin=InsertarB(0,bin);
                }
            }
        }
    }
}
Arbol *altArbol(Lista **lb,Arbol *arbol)
{
    Lista *aux;
    aux=(*lb);
    while(aux!=NULL){
        arbol=GenArbol(arbol,&aux);
        aux=aux->sig;
    }
    return arbol;
}
void MostrarBin(Lista **lb) //Muestra los 0 y 1 de cada letra
{
    Binario *aux;
    Lista *auxl;
    auxl=(*lb);
    if(auxl==NULL){
        printf("\nLista vacia\n");
    }
    while(auxl!=NULL)
    {
        if(auxl->pbin!=NULL){
            printf("\n%c=",auxl->letra);
            aux=auxl->pbin;
            MostrarB(&aux);
        }
        auxl=auxl->sig;
    }
}
void Bin(char fr[],Lista **lis)//Sustituye los 0 y 1 en la frase, saca el valor decimal y lo imprime en el archivo
{
    FILE *archivo;
    Lista *aux;
    Binario *aux2;
    aux=(*lis);
    int i=0,b[300]={0},j=0,k=0,baux[8]={0},c=0,l,d=0,dec[100]={0},ax=0,total;
    char *carac;
    while(fr[i]!='\0')//Sustituye los 0 y 1 en la frase
    {
        while(aux!=NULL){
            if(aux->letra==fr[i]){
                aux2=aux->pbin;
                while(aux2!=NULL){
                    b[j]=aux2->dato;
                    aux2=aux2->sig;
                    j++;
                }
            }
            aux=aux->sig;
        }
        aux=(*lis);
        i++;
    }
    total=i;
    printf("\nTotal frase:%d ",total);
    printf("\n\nFrase binaria\n");
    for(i=0;i<j;i++)
    {
        printf("%d",b[i]);
    }
    //Binario a decimal
    ax=j;
    for(i=0;i<j;i++)
    {
        baux[k]=b[i];//pasa 8 binarios a auxiliar
        if(k==7){
            l=7;
            for(k=0;k<=7;k++)
            {
                if(baux[k]==1){
                    d=d+(baux[k]*pow(2,l));
                }
                l--;
            }
            dec[c]=d;//PAsa el decimal a dec
            c++;
            d=0;
            k=0;
            ax-=8;
        }else{
            k++;
        }
    }
    printf("\nvalor ax: %d",ax);
    if(ax<8 && ax>=0)
    {
        for(k=ax;k<8;k++){//Rellena los 0 que hagan falta
            baux[k]=0;
        }
        l=7;
        d=0;
        for(k=0;k<=7;k++)
        {
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
    carac=(char*)malloc(c*sizeof(char));
    for(i=0;i<=c;i++)
    {
        carac[i]=dec[i];
        printf("%d ",dec[i]);
    }
    //Imprime frase cifrada
    archivo=fopen("Codigo.txt","w");
    for(i=0;i<=c;i++)
    {
        fputc(carac[i],archivo);
    }
    fclose(archivo);
}
void LeerBinario(Lista **lb)
{
    Lista *aux;
    aux=(*lb);
    FILE *archivo;
    char codigo[100],t;
    int i,total=0,*decimal,*binario,k,j,nt=0;

    archivo=fopen("Codigo.txt","r");
    if(archivo==NULL){
        printf("Error el archivo no existe\n");}
    else{
        i=0;
        while(feof(archivo)==0)
        {
            fscanf(archivo,"%c",&codigo[i]);
            i++;
        }
        fclose(archivo);
        printf("\n\nCodigo leido del archivo\n");
        for(j=0;j<(i-1);j++)
        {
            printf("%d ",codigo[j]);
        }
        decimal=(int*)malloc((i)*sizeof(int));
        total=i;
        printf("Valor de total: %d\n",total);
        for(i=0;i<(total-1);i++)
        {
            decimal[i]=codigo[i];
            if(decimal[i]<0){
                decimal[i]+=256;
            }
            printf("%d ",decimal[i]);
        }
        //Convirtiendo a binario
        binario=(int*)malloc((total*8)*sizeof(int));
        k=0;
        for(i=0;i<(total-1);i++)
        {
            int temporal[8]={0};
            for(j=0;decimal[i]!=0;j++){
                temporal[j]=decimal[i]%2;
                decimal[i]=decimal[i]/2;
            }
            j=7;
            while(j>=0){
                binario[k]=temporal[j];
                j--;
                k++;
            }
        }
        //Arreglo con numeros binarios
        printf("\n\nArreglo de numeros binarios\n");
        for(i=0;i<k;i++)
        {
            printf("%i",binario[i]);
        }
    }
    printf("\n%d",i);
    formaFrase(&aux,binario,i);
}
void formaFrase(Lista **l,int bin[],int total)
{
    Lista *aux;
    Binario *ax;
    aux=(*l);
    int i=0,pos=0,pos2=0,cont=0,raiz=0;
    char frase[100]={'0'};
    //printf("\n%d\n",total);
    raiz=aux->frecuencia;
    while(pos!=raiz)
    {
        cont=0;
        //printf("\n%d",total);
        //printf("%c ",aux->letra);
        if(aux->letra!='-'){
            ax=aux->pbin;
            while(ax!=NULL)
            {
                if(ax->dato==bin[i]){
                    if(ax->sig==NULL){
                        frase[pos]=aux->letra;
                        pos++;
                        total-=(cont+1);
                        //printf("\n%d",pos);
                    }
                    ax=ax->sig;
                    i++;
                    cont++;
                }else{
                    ax=NULL;
                    i=pos2;
                    //printf("\n%d",i);
                }
            }
        }
        aux=aux->sig;
        if(aux==NULL){
            aux=(*l);
        }
        pos2=i;
        //printf("\n%d",pos2);
    }
    printf("\nMensaje:\n");
    i=0;
    while(frase[i]!=0)
    {
        printf("%c ",frase[i]);
        i++;
    }
}

int main()
{
    FILE *archivo;
    Lista *l,*l2,*LB;
    Arbol *r,*rb;
    r=NULL;
    rb=NULL;
    l=NULL;
    l2=NULL;
    LB=NULL;
    char frase[100];
    int opc;

    do{
        printf("1.Codificar\n2.Decodificar\n3.Salir\n\n");
        scanf("%d",&opc);
        switch(opc)
        {
            case 1:
                printf("Inserta una frase: \n");
                fflush(stdin);
                gets(frase);
                strupr(frase);

                l=letras(frase,l);
                printf("\n\n");
                Mostrar(l,1);
                l=Ordena(l);
                l2=l;
                printf("\n\n");
                Mostrar(l2,1);

                r=Alta(l,r);
                printf("\n\n\nLista total\n\n");
                Mostrar(l,1);

                printf("\n\n");
                Preorder(r);

                archivo=fopen("Arbol.txt","w");
                GenArchivo(r,archivo);
                fclose(archivo);

                archivo=fopen("Arbol.txt","r");
                if(archivo==NULL){
                    printf("\nEl archivo no existe\n");
                }
                else{
                    LB=LeerArbol(LB,archivo);
                }
                fclose(archivo);

                printf("\n\n");
                Mostrar(LB,2);

                printf("\n\nArbol desde lista\n");
                rb=altArbol(&LB,rb);
                Preorder(rb);
                printf("\n");
                MostrarBin(&LB);
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
                    LB=LeerArbol(LB,archivo);
                }
                fclose(archivo);
                printf("\n\n");
                Mostrar(LB,2); //Muestra la lista desde el archivo preorder
                printf("\n\nArbol desde lista\n");
                rb=altArbol(&LB,rb);
                Preorder(rb);
                printf("\nCodigo binario\n");
                MostrarBin(&LB); //Muestra los 0 y 1 para cada letra

                LeerBinario(&LB);
            break;
        }
        system("pause");
        system("cls");
    }while(opc!=3);

    return 0;
}
