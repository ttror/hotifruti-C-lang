#ifndef PRODUTO_H
#define PRODUTO_H

#include <stdbool.h>


#define MAX 80                             // Tamanho máximo para strings
#define MAX_CODIGO_BARRAS 55               // Definição da constante MAX_CODIGO_BARRAS
#define MAX_IDS_PRODUTO 1000
// Estrutura para armazenar a data de validade
typedef struct {
    int dia;
    int mes;
    int ano;
} DataValidade;

// Estrutura para Produtos
typedef struct {
    int id;                                // Identificador único do produto
    char nome[MAX];                        // Nome do produto
    int quantidade;                        // Quantidade disponível do produto
    double precoCusto;                     // Preço de custo do produto
    double precoVenda;                     // Preço de venda do produto
    char tipo[MAX];                        // Tipo do produto
    char descricao[MAX];                   // Descrição do produto
    bool vendidoAGranela;                  // Indica se o produto é vendido a granel
    double precoPorKilo;                   // Preço por quilo do produto
    char codigoBarras[MAX_CODIGO_BARRAS];  // Código de barras do produto
    DataValidade validade;                 // Data de validade do produto
} Produto;

// Estrutura para entradas de índice
typedef struct {
    int id;                                // ID do produto
    long posicao;                          // Posição do produto no arquivo
} IndexEntryProduto;

// Estrutura para gerenciar IDs
typedef struct {
    int ids[MAX_CODIGO_BARRAS];             // Array de IDs para gerenciamento
    int count;                             // Contagem de IDs gerenciados
} IdManagerProduto;

extern IdManagerProduto idManagerProduto; // Declaração da variável externa para gerenciar IDs

// Declaração de funções relacionadas a produtos
bool buscarProdutoPorId(int id, Produto *produto);   // Para buscar um produto por ID
int contarProdutos();                                // Para contar produtos cadastrados
int obterNovoIdProduto();                            // Para obter um novo ID para o produto
void cadastrarProduto();                             // Para cadastrar um novo produto
void atualizarProduto(int id, int quantidadeVendida);// Para atualizar um produto com ID e nova quantidade
void removerProduto();                               // Para remover um produto
void listarProdutos();                               // Para listar todos os produtos
bool validarData(DataValidade data);                 // Para validar a data de validade
void exibirData(DataValidade data);                  // Para exibir a data de validade
void lerStringBalanca(char *str, int max, const char *prompt); // Para ler string com limite
void mostrarBoasVindasBalanca();                     // Para mostrar mensagem de boas-vindas

#endif // PRODUTO_H
