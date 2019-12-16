#include<stdio.h>
#include<stdlib.h>
#include"structs.h"


Lista* criar_lista(){
    return NULL;
}
void liberarListEspera(Lista* a){
    Lista *p = a;
    while (p != NULL) {
        p = a->prox;
        free(a);
        a = p;
    }
    return NULL;
}
Lista *push(Lista *l, int quantidade, int idcli,int idprod){
    Lista *novo = (Lista*)malloc(sizeof(Lista));
    novo->quantidade  = quantidade;
    novo->codproduto=idprod;
    novo->codcliente=idcli;
    if(l==NULL){
        novo->ant = NULL;
        novo->prox = l;
        return novo;
    }else{
        Lista* a=l;
        while(a->prox!=NULL){
            a=a->prox;
        }
      a->prox=novo;
      novo->ant=a;
      novo->prox=NULL;
    }
    return l;
}

int achei_o_meliante(Lista *l, int codigo){
Lista *p=l;
while(p!=NULL && p->codcliente !=codigo){
    p=p->prox;
}


if(p==NULL){
    return 0;
}

return 1;
}
int achei_o_melianteProd(Lista *l, int codigo){
Lista *p=l;
while(p!=NULL && p->codproduto !=codigo){
    p=p->prox;
}


if(p==NULL){
    return 0;
}

return 1;
}

Lista* multiplosPop(Lista *l,int codigo){
while(achei_o_meliante(l,codigo)!=0){
    l=popCli(l,codigo);
}
    return l;
}

Lista* multiplosPopProd(Lista *l,int codigo){
while(achei_o_melianteProd(l,codigo)!=0){
    l=pop(l,codigo);
}
    return l;
}

Lista *pop(Lista *l,int codigo){
    Lista *p=l;
    while(p!=NULL && p->codproduto!=codigo){
        p=p->prox;
    }
    if(p==NULL){
        return l;
    }
    if(p==l){
        l = p->prox;

    }else{
        p->ant->prox=p->prox;
    }
    if(p->prox!=NULL){
        p->prox->ant=p->ant;
    }
    free(p);
    return l;
}

Lista *popCli(Lista *l,int codigo){
    Lista *p=l;
    while(p!=NULL && p->codcliente !=codigo){
        p=p->prox;
    }
    if(p==NULL){
        return l;
    }
    if(p==l){
        l = p->prox;

    }else{
        p->ant->prox=p->prox;
    }
    if(p->prox!=NULL){
        p->prox->ant=p->ant;
    }
    free(p);
    return l;
}

void print_lista(Lista *l){
    if(l==NULL){
        printf("Lista de espera vazia\n");
    }
    while(l != NULL){
        printf("Codido cliente:%d\nCodigo produto:%d\nQuantidade%d\n--------------------------\n", l->codcliente,l->codproduto,l->quantidade );
        l=l->prox;
    }
}

Lista* pesquisarList(Lista *p, int codigo_produto){
    Lista* l=p;
    while(l!=NULL && l->codproduto !=codigo_produto){
        l=l->prox;
    }

return p;
}

