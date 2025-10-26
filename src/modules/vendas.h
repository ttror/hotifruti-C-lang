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

// Prototipação de funções relacionadas a vendas
void consultarVendas();              // Função para consultar vendas
void cadastrarVenda(Venda venda);    // Função para cadastrar uma nova venda
void cancelarVenda(int idVenda);     // Função para cancelar uma venda
void gerenciarVendas();
#endif // VENDAS_H
