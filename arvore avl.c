#include <stdio.h>
#include <stdlib.h>


typedef struct no{
    int info;
    struct no *esquerda;
    struct no *direita;
    int altura;
}AVL;



int maior(int a, int b){
    return (a>b) ? a:b;
}

int altura(AVL *a){
    if(a == NULL)
        return 0;

    return a->altura;
}

int get_balanco(AVL *a){
    if(a == NULL)
        return 0;

    return altura(a->direita) - altura(a->esquerda);
}

AVL *criar_arvore(){
    return NULL;
}


AVL *novo_no(int v){
    AVL *novo      = (AVL*)malloc(sizeof(AVL));
    novo->info     = v;
    novo->altura   = 1;
    novo->esquerda = novo->direita = NULL;
    return novo;
}

AVL *gira_esquerda(AVL *a){
    AVL *x = a->direita;
    AVL *y = x->esquerda;

    x->esquerda = a;
    a->direita  = y;

    a->altura = 1 + maior(altura(a->esquerda), altura(a->direita));
    x->altura = 1 + maior(altura(x->esquerda), altura(x->direita));

    return x;
}

AVL *gira_direita(AVL *a){
    AVL *x = a->esquerda;
    AVL *y = x->direita;

    x->direita  = a;
    a->esquerda = y;

    a->altura = 1 + maior(altura(a->esquerda), altura(a->direita));
    x->altura = 1 + maior(altura(x->esquerda), altura(x->direita));

    return x;
}

AVL *inserir(AVL *a, int v){
    if(a == NULL){
        return novo_no(v);
    }else if(v < a->info){
        a->esquerda = inserir(a->esquerda, v);
    }else if(v > a->info){
        a->direita  = inserir(a->direita, v);
    }else {
        return a;
    }

    a->altura = 1 + maior(altura(a->esquerda), altura(a->direita));

    int balanco = get_balanco(a);

    if(balanco > 1 && v > a->direita->info){
        return gira_esquerda(a);
    }

    if(balanco < -1 &&  v < a->esquerda->info){
        return gira_direita(a);
    }

    if(balanco > 1 && v < a->direita->info){

    }

    if(balanco > )



    return a;
}


void print_in_order(AVL *a){
    if(a!=NULL){
        print_in_order(a->esquerda);
        printf("%d \n", a->info);
        print_in_order(a->direita);
    }
}

int main(){
    AVL *my_arvore = criar_arvore();

    my_arvore = inserir(my_arvore, 10);
    my_arvore = inserir(my_arvore, 20);
    my_arvore = inserir(my_arvore, 30);

    print_in_order(my_arvore);

}
