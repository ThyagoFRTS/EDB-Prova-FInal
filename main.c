#include<stdio.h>
#include<stdlib.h>
#include"structs.h"
#include<string.h>
#include<locale.h>


int main ()
{
    Lista* eh_uma_fila=criar_lista();
    Lista2 *registro_venda=criarLista2();
    Avlcliente *arv_avlc=criaarvAVL();
    Avlproduto *arv_avlp=criaarvAVL_prod();
    int op1,codigo,quantidade,retorno,tam;
    Cliente novoCli;
    Produto novoProd;
    FILE *arq;
    Compilado auxiliar;
    float preco;
    char nomeCli[50],nomeProd[25];
    printf("Loading");
    arq=fopen("PRODUTOS\\produtos.txt","r");
        fseek(arq, 0, SEEK_END);
        tam = ftell(arq);
    fclose(arq);
    if(tam!=0){
        arv_avlp=carregarProduto(arv_avlp);
    }
    printf(".");
    arq=fopen("CLIENTES\\clientes.txt","r");
        fseek(arq, 0, SEEK_END);
        tam = ftell(arq);
    fclose(arq);
        if(tam!=0){
            arv_avlc=carregarCliente(arv_avlc);
        }
    printf(".");
    arq=fopen("VENDAS\\historico.txt","r");
        fseek(arq, 0, SEEK_END);
        tam = ftell(arq);
    fclose(arq);
    if(tam!=0){
        registro_venda=carregarVendas(registro_venda);
    }
    printf(".");
        arq=fopen("LISTA_ESPERA\\esperamano.txt","r");
        fseek(arq, 0, SEEK_END);
        tam = ftell(arq);
    fclose(arq);
        if(tam!=0){
            eh_uma_fila=carregarLista(eh_uma_fila);
        }
    printf(".");
    system("cls");

    do
    {
        system("cls");
        printf("\t\t\t\t\t------------Produto------------\n");
        printf("\t\t\t\t\t\t1-Inserir Produto\n\t\t\t\t\t\t2-Buscar Produto\n\t\t\t\t\t\t3-Alterar Produto\n\t\t\t\t\t\t4-Excluir Produto\n\t\t\t\t\t\t5-Exibir Estoque\n");
        printf("\t\t\t\t\t------------Cliente------------\n");
        printf("\t\t\t\t\t\t6-Cadastrar Cliente\n\t\t\t\t\t\t7-Alterar Cliente\n\t\t\t\t\t\t8-Excluir Cliente\n\t\t\t\t\t\t9-Exibir Clientes\n");
        printf("\t\t\t\t\t-------------Venda-------------\n");
        printf("\t\t\t\t\t\t10-Realizar Vendas\n\t\t\t\t\t\t11-Consultar Vendas\n\t\t\t\t\t\t12-Sair\n");
        printf("\t\t\t\t\tSelect: ");
        //print_lista(eh_uma_fila);
        scanf("%d",&op1);

        switch(op1)
        {
        case 1:
            system("cls");
            printf("Informar o nome do produto\n");
            scanf(" %[^\n]s",nomeProd);

            printf("Informar o codigo do produto\n");
            do
            {
                printf("Digitar outro codigo se houver produtos com o codigo digitado\n");
                scanf("%d",&codigo);

            }
            while(pesquisarProd(arv_avlp,codigo)!=0);

            printf("Informar o preco do produto\n");
            scanf("%f",&preco);

            printf("Informar a quantidade do produto\n");
            scanf("%d",&quantidade);

            novoProd.id=codigo;
            strcpy(novoProd.nome,nomeProd);
            novoProd.preco=preco;
            novoProd.quantidade=quantidade;
            arv_avlp=inserearvb_prod(arv_avlp,novoProd);
            printf("Inserido");
            system("pause");
            break;
        case 2:
            system("cls");
            printf("Informe o codigo do produto para a pesquisa");
            scanf("%d",&codigo);
            pesquisarProd(arv_avlp,codigo);
            system("pause");
            break;
        case 3:
            system("cls");

            printf("Digite o codigo do produto para a alteracao\n");
            scanf("%d",&codigo);
            retorno=editarProd(arv_avlp,codigo);
            printf("Alterado\n");
            if(retorno!=0)
            {
                auxiliar=venderCasoAdicionar(arv_avlc,arv_avlp,registro_venda,eh_uma_fila,retorno);
                eh_uma_fila=auxiliar.espera;
                registro_venda=auxiliar.lista_vendas;
            }
            printf("Lista de espera atual\n");
            print_lista(eh_uma_fila);
            system("pause");
            break;
        case 4:
            system("cls");
            printf("Digite o codigo do produto para a exclusao\n");
            scanf("%d",&codigo);
            arv_avlp=retira_prod(arv_avlp,codigo);
            eh_uma_fila=multiplosPopProd(eh_uma_fila,codigo);
            printf("Excluido\n");
            system("pause");
            break;
        case 5:
            system("cls");
            preordem_prod(arv_avlp);
            system("pause");
            break;
        case 6:
            system("cls");
            printf("Informar o nome do cliente\n");
            scanf(" %[^\n]s",nomeCli);
            fflush(stdin);
            printf("Informar o codigo do cliente\n");
            do
            {
                printf("Digitar outro codigo se houver clientes com o codigo digitado\n");
                scanf(" %d",&codigo);

            }
            while(pesquisarCliCli(arv_avlc,codigo)!=0);
            novoCli.id=codigo;
            strcpy(novoCli.nome,nomeCli);
            arv_avlc=inserearvb(arv_avlc,novoCli);
            printf("Inserido");
            system("pause");
            break;
        case 7:
            system("cls");
            printf("Digite o codigo do cliente para a alteracao\n");
            scanf("%d",&codigo);
            editarCliCli(arv_avlc,codigo);
            printf("Alterado\n");
            system("pause");
            break;
        case 8:
            system("cls");
            printf("Digite o codigo do cliente para a exclusao\n");
            scanf("%d",&codigo);
            arv_avlc=retira(arv_avlc,codigo);
            eh_uma_fila=multiplosPop(eh_uma_fila,codigo);
            printf("Excluido \n ");
            system("pause");
            break;
        case 9:
            system("cls");
            preordem(arv_avlc);
            system("pause");
            break;
        case 10:
            system("cls");
            auxiliar =vender(arv_avlc,arv_avlp,registro_venda,eh_uma_fila);
            registro_venda=auxiliar.lista_vendas;
            eh_uma_fila=auxiliar.espera;
            fflush(stdin);
            system("pause");
            break;
        case 11:
            system("cls");
            mostrar_registro(registro_venda);
            printf("Lista de espera atual\n");
            print_lista(eh_uma_fila);
            system("pause");
            break;
        case 12:
            system("cls");
            break;
        default:
            print_lista(eh_uma_fila);
            system("pause");
            break;
        }
    }
    while(op1!=12);
    printf("Salvando");
    salvarProduto(arv_avlp);
    printf(".");
    salvarCliente(arv_avlc);
    printf(".");
    salvarVendas(registro_venda);
    printf(".");
    salvarLista(eh_uma_fila);



    libera(registro_venda);
    liberaAvlCliente(arv_avlc);
    liberaAvlProduto(arv_avlp);
    liberarListEspera(eh_uma_fila);
    system("cls");
    printf("\n\nPrograma encerrado\n\n");
    return 0;
}
