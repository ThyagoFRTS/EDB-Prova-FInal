#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"structs.h"

Avlcliente* carregarCliente(Avlcliente* arvore){
int cod;
char nom[50];
Cliente auxi;
FILE *arqui_cli;
arqui_cli=fopen("CLIENTES\\clientes.txt","r");
if(arqui_cli==NULL){
    printf("\nerro ao abrir o arquivo dos clientes\n");
    exit(1);
}
while(!feof(arqui_cli)){
    fscanf(arqui_cli,"%d",&cod);
    fscanf(arqui_cli," %[A-Z a-z]s",nom);
    auxi.id=cod;
    strcpy(auxi.nome,nom);
    arvore=inserearvb(arvore,auxi);
}
fclose(arqui_cli);
return arvore;
}

Avlproduto* carregarProduto(Avlproduto* arvore){
int cod,quanti;
char nom[30];
float preco;
Produto auxi;
FILE *arqui_prod;
arqui_prod=fopen("PRODUTOS\\produtos.txt","r");
if(arqui_prod==NULL){
    printf("erro\n");
    exit(1);
}
while(!feof(arqui_prod)){
    fscanf(arqui_prod,"%d",&cod);
    fscanf(arqui_prod," %[A-Z a-z]s",nom);
    fscanf(arqui_prod,"%f",&preco);
    fscanf(arqui_prod,"%d",&quanti);

    auxi.id=cod;
    strcpy(auxi.nome,nom);
    auxi.preco=preco;
    auxi.quantidade=quanti;

    arvore=inserearvb_prod(arvore,auxi);
}
fclose(arqui_prod);
return arvore;
}

Lista2* carregarVendas(Lista2* a){
    Registro auxi;
    FILE *arq=fopen("VENDAS\\historico.txt","r");
    if(arq==NULL){
        printf("\nerro ao abrir o arquivo de vendas\n");
    }

    while(!feof(arq)){
        fscanf(arq," %[A-Z a-z]s",auxi.nomecli);
        fscanf(arq,"%d",&auxi.quanti);
        fscanf(arq," %[A-Z a-z]s",auxi.nomeprod);
        fscanf(arq,"%f",&auxi.total_da_compra);
        a=inserirRegistro(a,auxi);
        }

    fclose(arq);
    return a;
}

Lista* carregarLista(Lista *a){
    int b,c,d;
    FILE *arq=fopen("LISTA_ESPERA\\esperamano.txt","r");
    if(arq==NULL){
        printf("\nerro ao abrir o arquivo de listas\n");
    }

    while(!feof(arq)){
        fscanf(arq,"%d",&b);
        fscanf(arq,"%d",&c);
        fscanf(arq,"%d",&d);
        a=push(a,d,b,c);
        }

    fclose(arq);
    return a;


}

void escreverClienteArq(Avlcliente *a, FILE *arqui_cli,int c){
    if(arqui_cli==NULL){
        printf("erro\n");
        exit(1);
    }
    fflush(stdin);
    if (!estavazia(a)) {
        if(a->cliente.id!=c){
        fprintf(arqui_cli,"%d%s\n", a->cliente.id ,a->cliente.nome);
        }else{
        fprintf(arqui_cli,"%d%s", a->cliente.id ,a->cliente.nome);
        }
        escreverClienteArq(a->esq,arqui_cli,c);
        escreverClienteArq(a->dir,arqui_cli,c);
    }
}

void salvarCliente(Avlcliente *arvr){
int cod_ult_elem;
Avlcliente*perc=arvr;

while(perc->dir!=NULL){
    perc=perc->dir;
}
cod_ult_elem=perc->cliente.id;

FILE *arqui_cli;
    arqui_cli=fopen("CLIENTES\\clientes.txt","w");
    escreverClienteArq(arvr,arqui_cli,cod_ult_elem);
fclose(arqui_cli);

}

void escreverProdutoArq(Avlproduto *a, FILE *arqui_prod,int c){
    if(arqui_prod==NULL){
        printf("\nerro, nao foi possivel abrir o arquivo de produtos\n");
        exit(1);
    }
    if (!estavazia_prod(a)) {
        if(a->produto.id !=c){
        fprintf(arqui_prod,"%d%s%f %d\n", a->produto.id ,a->produto.nome,a->produto.preco,a->produto.quantidade);
        }else{
        fprintf(arqui_prod,"%d%s%f %d", a->produto.id ,a->produto.nome,a->produto.preco,a->produto.quantidade);
        }
        escreverProdutoArq(a->esq,arqui_prod,c);
        escreverProdutoArq(a->dir,arqui_prod,c);
    }
}

void salvarProduto(Avlproduto *arvr){
int cod_ult_elem;
Avlproduto*perc=arvr;

while(perc->dir!=NULL){
    perc=perc->dir;
}
cod_ult_elem=perc->produto.id;

FILE *arqui_prod;
    arqui_prod=fopen("PRODUTOS\\produtos.txt","w");
    escreverProdutoArq(arvr,arqui_prod,cod_ult_elem);
fclose(arqui_prod);

}

void salvarVendas(Lista2 *a){
    FILE *arq=fopen("VENDAS\\historico.txt","w");
    if(arq==NULL){
        printf("\nerro ao abrir o arquivo de vendas\n");
    }
    while(a!=NULL){
        if(a->prox==NULL){
            fprintf(arq,"%s%d%s%f",a->historico.nomecli,a->historico.quanti,a->historico.nomeprod,a->historico.total_da_compra);
            a=a->prox;
        }else{
            fprintf(arq,"%s%d%s%f\n",a->historico.nomecli,a->historico.quanti,a->historico.nomeprod,a->historico.total_da_compra);
            a=a->prox;
        }
    }
    fclose(arq);
}

void salvarLista(Lista *a){
    FILE *arq=fopen("LISTA_ESPERA\\esperamano.txt","w");
    if(arq==NULL){
        printf("\nerro ao abrir o arquivo de listas\n");
    }
    while(a!=NULL){
        if(a->prox==NULL){
            fprintf(arq,"%d %d %d",a->codcliente, a->codproduto, a->quantidade );
            a=a->prox;
        }else{
            fprintf(arq,"%d %d %d\n",a->codcliente, a->codproduto, a->quantidade );
            a=a->prox;
        }
    }
    fclose(arq);

}

void salvarPadraoLista(Lista *a){
    FILE *arq=fopen("LISTA_ESPERA\\esperamano.txt","w");
    if(arq==NULL){
        printf("\nerro ao abrir o arquivo de listas\n");
    }
    fprintf(arq,"-1 -1 -1");
    fclose(arq);
}
