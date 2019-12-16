#include<stdio.h>
#include<stdlib.h>
#include"structs.h"
#include<string.h>

Lista2* criarLista2(){
return NULL;
}

Lista2 *inserirRegistro(Lista2 *l, Registro v){
    Lista2 *novo = (Lista2*)malloc(sizeof(Lista2));
    novo->historico=v;
    novo->prox = l;
    return novo;
}

void libera(Lista2* lista) {
    Lista2 *p = lista;
    while (p != NULL) {
        p = lista->prox;
        free(lista);
        lista = p;
    }
    return NULL;
}

void mostrar_registro(Lista2 *a){
    if(a==NULL)
        printf("Lista vazia\n");
while(a!=NULL){
    printf("%s comprou %s\nQuantidade: %d\nValor total: %.2f\n---------------------------------------\n",a->historico.nomecli,a->historico.nomeprod,a->historico.quanti,a->historico.total_da_compra);
    a=a->prox;
}
}
