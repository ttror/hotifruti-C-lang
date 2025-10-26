#ifndef CONTAS_H
#define CONTAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DATA_FILE_CONTAS_RECEBER "contas_receber.dat"
#define DATA_FILE_CONTAS_PAGAR "contas_pagar.dat"

// Estruturas para contas a receber e contas a pagar
typedef struct {
    int id;                // ID da conta
    float valor;           // Valor da conta
    char descricao[500];   // Descrição da conta
    time_t dataVencimento; // Data de vencimento
    int status;            // 0 para pendente, 1 para paga
} ContaReceber;

typedef struct {
    int id;                // ID da conta
    float valor;           // Valor da conta
    char descricao[500];   // Descrição da conta
    time_t dataVencimento; // Data de vencimento
    int status;            // 0 para pendente, 1 para paga
} ContaPagar;

// Funções para contas a receber
void adicionarContaReceber();
void visualizarContasReceber();
void marcarContaReceberComoPaga(int id);

// Funções para contas a pagar
void adicionarContaPagar();
void visualizarContasPagar();
void marcarContaPagarComoPaga(int id);

#endif // CONTAS_H
