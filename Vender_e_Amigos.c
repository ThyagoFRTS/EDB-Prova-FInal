#include<stdio.h>
#include<stdlib.h>
#include"structs.h"
#include<string.h>

Compilado vender(Avlcliente* cliente,Avlproduto* produto,Lista2 *venda,Lista* fila){
    Compilado auxiliar;
    Registro auxi;
    int codclie,codprod,quantidade,restante;
    printf("Digite o codigo do cliente para realizar a venda\n");
    do{
        printf("Digitar outro codigo se nao houver clientes com o codigo digitado\n");
        scanf(" %d",&codclie);
        system("cls");
    }while(pesquisarCliCli(cliente,codclie)!=1);

    printf("Codigo encontrado\n\n");
    printf("Digite o codigo do produto para realizar a venda\n");
    do{
        printf("Digitar outro codigo se nao houver produtos com o codigo digitado\n");
        scanf(" %d",&codprod);
        system("cls");
    }while(pesquisarProd(produto,codprod)!=1);
    printf("Codigo encontrado\n\n");
    printf("Digite a quantidade\n");
    fflush(stdin);
    scanf(" %d",&quantidade);

    Avlcliente *temp2=retornaCliente(cliente,codclie);
    Avlproduto *temp=pesquisarItem(produto,codprod);

    if(temp->produto.quantidade-quantidade<0 ){
        strcpy(auxi.nomecli,temp2->cliente.nome);
        strcpy(auxi.nomeprod,temp->produto.nome);

        temp->tem_lista_espera=1;
        restante=abs(temp->produto.quantidade-quantidade);
        auxi.total_da_compra=(float)temp->produto.quantidade * temp->produto.preco;
        auxi.quanti=temp->produto.quantidade ;
        temp->produto.quantidade=0;
        venda=inserirRegistro(venda,auxi);
        if(fila==NULL){
            fila=push(fila,restante,codclie,codprod);
            auxiliar.espera=fila;
            //print_lista(fila);
        }else{
            fila=push(fila,restante,codclie,codprod);
            auxiliar.espera=fila;
            //print_lista(fila);
        }
        fflush(stdin);
        printf("Produtos restantes vendidos com sucesso, voce entrou na lista de espera\n");
        auxiliar.lista_vendas=venda;
        return auxiliar;

    }else{
        temp->produto.quantidade=temp->produto.quantidade-quantidade;
        strcpy(auxi.nomecli,temp2->cliente.nome);
        strcpy(auxi.nomeprod,temp->produto.nome);
        auxi.quanti=quantidade;
        auxi.total_da_compra=(float)quantidade * temp->produto.preco;
        venda=inserirRegistro(venda,auxi);
        printf("Venda feita com sucesso\n");
        auxiliar.lista_vendas=venda;
        return auxiliar;
    }
}

Compilado venderCasoAdicionar(Avlcliente* cliente,Avlproduto* produto,Lista2 *venda,Lista* fila,int codigo){
    Compilado auxiliar;
    int modulo;
    Registro auxi;

    Lista *f=pesquisarList(fila,codigo);
    Avlcliente *c = retornaCliente(cliente,f->codcliente);
    Avlproduto *p = pesquisarItem(produto,f->codproduto);
    system("cls");
    while(p->produto.quantidade!=0 && achei_o_melianteProd(fila,codigo)!=0 ){
    modulo=abs( p->produto.quantidade - f->quantidade);


    strcpy(auxi.nomecli,c->cliente.nome);
    strcpy(auxi.nomeprod,p->produto.nome);
    auxi.quanti=p->produto.quantidade;
    auxi.total_da_compra=(float)f->quantidade * p->produto.preco;


    if(p->produto.quantidade -f->quantidade<0){

        auxi.quanti=p->produto.quantidade;
        auxi.total_da_compra=(float)p->produto.quantidade * p->produto.preco;
        venda=inserirRegistro(venda,auxi);
        p->produto.quantidade=0;
        f->quantidade=modulo;
        printf("Havia clientes na espera por este produto\nProdutos restantes vendidos com sucesso, ainda ha clientes na lista de espera\n");
        auxiliar.espera=fila;
        auxiliar.lista_vendas=venda;
        //printf("b\n");
    }else{
        p->tem_lista_espera=0;

        auxi.quanti=f->quantidade;
        auxi.total_da_compra=(float)f->quantidade * p->produto.preco;
        venda=inserirRegistro(venda,auxi);
        p->produto.quantidade-=f->quantidade;
        printf("Cliente %s retirado da lista de espera\n", c->cliente.nome);
        fila=pop(fila,p->produto.id);
        printf("retirou\n");
        auxiliar.espera=fila;
        auxiliar.lista_vendas=venda;
        //printf("a\n");
        f=pesquisarList(fila,codigo);
        if(f==NULL){
            break;
        }
        c = retornaCliente(cliente,f->codcliente);
        p = pesquisarItem(produto,f->codproduto);

    }
    }
    return auxiliar;
}


