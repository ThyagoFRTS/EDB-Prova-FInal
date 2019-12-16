#include<stdio.h>
#include<stdlib.h>
#include"structs.h"
#include<string.h>

Avlproduto *criaarvAVL_prod ()
{
    return NULL;
}

int acesso_h_prod(Avlproduto *no)
{
    return  (no==NULL)?-1:no->h;
}

int calc_fb_prod(Avlproduto *no)
{
    return abs(altura_prod(no->esq) - altura_prod(no->dir));
}

int estavazia_prod (Avlproduto *a)
{
    return (a==NULL);
}

int maior_prod(int a, int b)
{
    return (a > b)?a:b;
}

int altura_prod(Avlproduto *a)
{
    if((a == NULL))
        return 0;
    else
        return 1 + maior_prod(altura_prod(a->esq), altura_prod(a->dir));
}

Avlproduto* rotacao_esquerda_prod(Avlproduto *raiz)
{
    Avlproduto *auxi=raiz->esq;
    raiz->esq=auxi->dir;
    auxi->dir=raiz;

    raiz->h=altura_prod(raiz);
    auxi->h=altura_prod(auxi);

    raiz=auxi;
    return auxi;
}

Avlproduto * rotacao_direita_prod(Avlproduto *raiz)
{
    Avlproduto *auxi=raiz->dir;
    raiz->dir=auxi->esq;
    auxi->esq=raiz;

    raiz->h=altura_prod(raiz);
    auxi->h=altura_prod(auxi);

    raiz=auxi;
    return auxi;
}

Avlproduto * rotacao_d_esquerda_prod(Avlproduto *no)
{

    no->esq=rotacao_direita_prod(no->esq);

    no=rotacao_esquerda_prod(no);
    return no;
}

Avlproduto* rotacao_d_direita_prod(Avlproduto *no)
{

    no->dir=rotacao_esquerda_prod(no->dir);

    no=rotacao_direita_prod(no);
    return no;
}

Avlproduto *inserearvb_prod(Avlproduto *a, Produto v)
{
    if (estavazia_prod(a))
    {
        Avlproduto *nova = (Avlproduto*) malloc(sizeof(Avlproduto));
        nova->produto= v;
        nova->h=0;
        nova->tem_lista_espera=0;
        nova->esq = NULL;
        nova->dir = NULL;
        return nova;
    }
    else
    {
        if (v.id < a->produto.id)   //lado esquerdo: <
        {
            a->esq = inserearvb_prod(a->esq,v);
            if(calc_fb_prod(a)>1)
            {
                if(a->dir==NULL && v.id < a->esq->produto.id)
                {
                    return rotacao_esquerda_prod(a);
                }
                else
                {
                    return rotacao_d_esquerda_prod(a);
                }
            }
        }
        else     //lado  direito: >=
        {
            a->dir = inserearvb_prod(a->dir,v);
            if(calc_fb_prod(a)>1)
            {
                if( a->esq==NULL &&  v.id > a->dir->produto.id)
                {
                    return rotacao_direita_prod(a);
                }
                else
                {
                    return rotacao_d_direita_prod(a);
                }
            }
        }
        return a;
    }
}

Avlproduto *retira_prod(Avlproduto *a, int v)
{
    if (estavazia_prod(a))
    {
        return NULL;
    }
    else if (v < a->produto.id)
    {
        a->esq = retira_prod(a->esq,v);
        if(calc_fb_prod(a)>1)
        {
            if( altura_prod(a->dir->esq)<=altura_prod(a->dir->dir))
            {
                return rotacao_direita_prod(a);

            }
            else
            {

                return rotacao_d_direita_prod(a);

            }
        }


    }
    else if (v > a->produto.id)
    {
        a->dir = retira_prod(a->dir,v);
        if(calc_fb_prod(a)>1)
        {
            if( altura_prod(a->esq->dir)<=altura_prod(a->esq->esq))
            {
                return rotacao_esquerda_prod(a);

            }
            else
            {

                return rotacao_d_esquerda_prod(a);

            }
        }

    }
    else
    {
        if ( a->esq == NULL && a->dir == NULL)
        {
            free(a);
            a=NULL;
        }
        else if ( a->esq == NULL )
        {
            Avlproduto *aux = a->dir;
            free(a);
            a = aux;
        }
        else if ( a->dir == NULL )
        {
            Avlproduto *aux = a->esq;
            free(a);
            a = aux;
        }
        else
        {
            Avlproduto *aux = a->esq;
            while(aux->dir!=NULL)
            {
                aux = aux->dir;
            }
            a->produto.id=aux->produto.id;
            aux->produto.id=v;
            a->esq = retira_prod(a->esq,v);

        }
    }
    return a;
}

void preordem_prod(Avlproduto *a)
{
    if (!estavazia_prod(a))
    {
        printf("Id :%d\nNome: %s\nPreco: %.2f$\nQuantidade: %d\n-----------------------\n", a->produto.id,a->produto.nome,a->produto.preco,a->produto.quantidade);
        preordem_prod(a->esq);
        preordem_prod(a->dir);
    }
}

int pesquisarProd(Avlproduto *a,int cod)
{
    if(estavazia_prod(a))
    {
        return 0;
    }
    else if(a->produto.id==cod)
    {
        printf("Produto existente\n");
        printf("Nome: %s\nCodigo: %d\nPreco: %.2f\nQuantiidade: %d\n",a->produto.nome,a->produto.id,a->produto.preco,a->produto.quantidade);

        return 1;
    }
    else if(a->produto.id>cod)
    {
        pesquisarProd(a->esq,cod);
    }
    else
    {
        pesquisarProd(a->dir,cod);
    }

}

Avlproduto* pesquisarItem(Avlproduto *a,int cod)
{
    if(estavazia_prod(a))
    {
        return NULL;
    }
    else if(a->produto.id ==cod)
    {
        return a;
    }
    else if(a->produto.id>cod)
    {
        pesquisarItem(a->esq,cod);
    }
    else
    {
        pesquisarItem(a->dir,cod);
    }
}

int adicionarQuantidade(Avlproduto *a,int cod,int quantidade)
{
    if(estavazia_prod(a))
    {
        return 0;
    }
    else if(a->produto.id==cod)
    {
        a->produto.quantidade+=quantidade;
        return 1;
    }
    else if(a->produto.id>cod)
    {
        adicionarQuantidade(a->esq,cod,quantidade);
    }
    else
    {
        adicionarQuantidade(a->dir,cod,quantidade);
    }
    return 0;
}

int editarProd(Avlproduto *a,int cod)
{
    int cont=0;
    if(estavazia_prod(a))
    {
        printf("Produto nao encontrado ou nada cadastrado\n");
        return 0;
    }
    else if(a->produto.id==cod)
    {
        char nomeProd[25];
        int op,quantidade;
        float preco;
        printf("Produto existente\n");
        printf("Nome: %s\nCodigo: %d\nPreco: %.2f\nQuantiidade: %d\n",a->produto.nome,a->produto.id,a->produto.preco,a->produto.quantidade);
        printf("Alterar nome do produto?\n1-Sim\n2-Nao\n");
        scanf("%d",&op);
        if(op==1)
        {
            printf("Informar o nome do produto\n");
            scanf(" %[^\n]s",nomeProd);
            strcpy(a->produto.nome,nomeProd);
        }
        fflush(stdin);
        printf("Alterar preco do produto?\n1-Sim\n2-Nao\n");
        scanf("%d",&op);
        if(op==1)
        {
            printf("Informar o preco do produto\n");
            scanf("%f",&preco);
            a->produto.preco=preco;
        }
        printf("Alterar quantidade do produto?\n1-Sim\n2-Nao\n");
        scanf("%d",&op);
        if(op==1)
        {
            printf("Informar a quantidade do produto\nObs:O valor digitado sera somado ao valor ja existente\n");
            scanf("%d",&quantidade);
            a->produto.quantidade+=quantidade;
            cont++;

        }
        printf("Informacoes atualizadas:\nNome: %s\nCodigo: %d\nPreco: %.2f\nQuantiidade: %d\n",a->produto.nome,a->produto.id,a->produto.preco,a->produto.quantidade);
        if(a->tem_lista_espera==1 && cont!=0)
        {
            return a->produto.id;
        }else{
        return 0;
        }
    }
    else if(a->produto.id>cod)
    {
        editarProd(a->esq,cod);
    }
    else
    {
        editarProd(a->dir,cod);
    }

}

Avlproduto* liberaAvlProduto(Avlproduto *a)
{
    if (!estavazia_prod(a))
    {
        liberaAvlProduto(a->esq);
        liberaAvlProduto(a->dir);
        free(a);
    }
    return NULL;
}
