#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED
typedef struct{
char nomecli[50],nomeprod[25];
float total_da_compra;
int quanti;
}Registro;

typedef struct reg{
Registro historico;
struct reg *prox;

}Lista2;

typedef struct no{
    int codvenda,quantidade,codcliente,codproduto;
    struct no *ant;
    struct no *prox;
}Lista;

typedef struct{
    int id;
    char nome[50];

}Cliente;

typedef struct{
    char nome[25];
    int id;
    float preco;
    int quantidade;
}Produto;

typedef struct arvb {
    int info;
    int h;
    struct arvb *esq;
    struct arvb *dir;
} Avl;

typedef struct arvbcli {
    Cliente cliente;
    int h;
    struct arvbcli *esq;
    struct arvbcli *dir;
} Avlcliente;

typedef struct arvbprod {
    Produto produto;
    int tem_lista_espera;
    int h;
    struct arvbprod *esq;
    struct arvbprod *dir;
} Avlproduto;

typedef struct{
Lista2 *lista_vendas;
Lista* espera;
}Compilado;

#endif // STRUCTS_H_INCLUDED
//Para a Struct Cliente
int acesso_h(Avlcliente *no);
int calc_fb(Avlcliente *no);
int estavazia (Avlcliente *a);
int maior(int a, int b);
int altura(Avlcliente *a);
int editarCliCli(Avlcliente *a,int cod);
int pesquisarCliCli(Avlcliente *a,int cod);
Avlcliente *criaarvAVL ();
Avlcliente *inserearvb(Avlcliente *a, Cliente v);
Avlcliente* rotacao_direita(Avlcliente *raiz);
Avlcliente* rotacao_esquerda(Avlcliente *raiz);
Avlcliente* rotacao_d_direita(Avlcliente *no);
Avlcliente* rotacao_d_esquerda(Avlcliente *no);
Avlcliente *retira(Avlcliente *a, int v);
Avlcliente* liberaAvlCliente (Avlcliente *a);
Avlcliente* carregarCliente(Avlcliente* arvore);
Avlcliente *retornaCliente(Avlcliente *a,int cod);
void preordem(Avlcliente *a);
void inordem(Avlcliente *a);
void posordem(Avlcliente *a);
void escreverClienteArq(Avlcliente *a, FILE *arqui_cli,int c);
void salvarCliente(Avlcliente *arvr);
//Para a Struct Produto
int acesso_h_prod(Avlproduto *no);
int calc_fb_prod(Avlproduto *no);
int estavazia_prod (Avlproduto *a);
int maior_prod(int a, int b);
int altura_prod(Avlproduto *a);
int pesquisarProd(Avlproduto *a,int cod);
int adicionarQuantidade(Avlproduto *a,int cod,int quantidade);
int editarProd(Avlproduto *a,int cod);
Avlproduto *criaarvAVL_prod ();
Avlproduto* rotacao_esquerda_prod(Avlproduto *raiz);
Avlproduto * rotacao_direita_prod(Avlproduto *raiz);
Avlproduto * rotacao_d_esquerda_prod(Avlproduto *no);
Avlproduto* rotacao_d_direita_prod(Avlproduto *no);
Avlproduto *inserearvb_prod(Avlproduto *a, Produto v);
Avlproduto *retira_prod(Avlproduto *a, int v);
Avlproduto* liberaAvlProduto(Avlproduto *a);
Avlproduto* pesquisarItem(Avlproduto *a,int cod);
Avlproduto* carregarProduto(Avlproduto* arvore);
void escreverProdutoArq(Avlproduto *a, FILE *arqui_prod,int c);
void preordem_prod(Avlproduto *a);
void salvarProduto(Avlproduto *arvr);
//Para listas
Lista* criar_lista();
Lista *push(Lista *l, int v, int idcli,int idprod);
Lista *pop(Lista *l,int codigo);
Lista* pesquisarList(Lista *p, int codigo_produto);
Lista* carregarLista(Lista *a);
Lista* multiplosPop(Lista *l,int codigo);
Lista* multiplosPopProd(Lista *l,int codigo);
Lista *popCli(Lista *l,int codigo);
void mostrar_registro(Lista2 *a);
void liberarListEspera(Lista* a);
void libera(Lista2* lista);
void print_lista(Lista *l);
void salvarVendas(Lista2 *a);
void salvarLista(Lista *a);
void salvarPadraoLista(Lista *a);
Lista2* carregarVendas(Lista2* a);
Lista2* criarLista2();
Lista2 *inserirRegistro(Lista2 *l, Registro v);
//Retorno do registro venda e fila
Compilado vender(Avlcliente* cliente,Avlproduto* produto,Lista2 *venda,Lista* fila);
Compilado venderCasoAdicionar(Avlcliente* cliente,Avlproduto* produto,Lista2 *venda,Lista* fila,int codigo);
//Outras funcoes
int get_size(const char* file_name);
int achei_o_melianteProd(Lista *l, int codigo);
int achei_o_meliante(Lista *l, int codigo);
