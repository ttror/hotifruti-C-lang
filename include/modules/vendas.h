#ifndef VENDAS_H
#define VENDAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "produto.h"
#include "financeiro.h"
// Estrutura que representa uma venda
typedef struct {
    int idProduto;    // ID do produto vendido
    int quantidade;   // Quantidade vendida
    float valorTotal; // Valor total da venda
    time_t dataHora;  // Data e hora da venda
} Venda;

#define DATA_FILE_VENDA "vendas.dat" // Nome do arquivo para armazenar vendas

// Prototipa��o de fun��es relacionadas a vendas
void consultarVendas();              // Fun��o para consultar vendas
void cadastrarVenda(Venda venda);    // Fun��o para cadastrar uma nova venda
void cancelarVenda(int idVenda);     // Fun��o para cancelar uma venda
void gerenciarVendas();
#endif // VENDAS_H
