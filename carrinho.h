#ifndef CARRINHO_H
#define CARRINHO_H

#include <stdbool.h>
#include <stdlib.h>
#include "produto.h"

// Estrutura de item do carrinho
typedef struct {
    Produto produto;  // Produto no carrinho
    float quantidade; // Quantidade comprada
    float precoTotal; // Quantidade * preço unitário
} ItemCarrinho;

// Estrutura do carrinho
typedef struct {
    ItemCarrinho *itens; // Array dinâmico de itens
    int totalItens;      // Número de itens no carrinho
    int capacidade;      // Capacidade total atual do array
} Carrinho;

// Inicializa o carrinho
void inicializarCarrinho(Carrinho *carrinho);

// Adiciona um item ao carrinho
bool adicionarProdutoAoCarrinho(Carrinho *carrinho, const char *nomeOuId, bool porNome);

// Exibe os itens no carrinho
void visualizarCarrinho(const Carrinho *carrinho);

// Finaliza a venda e processa os itens no carrinho
void realizarVendaComCarrinho(Carrinho *carrinho);

// Limpa os itens do carrinho
void limparCarrinho(Carrinho *carrinho);

// Libera os recursos do carrinho
void destruirCarrinho(Carrinho *carrinho);

#endif  // CARRINHO_H
