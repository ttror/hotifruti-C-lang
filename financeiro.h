#ifndef FINANCEIRO_H
#define FINANCEIRO_H

#include <time.h> // Para usar time_t

#define DATA_FILE_FLUXO_CAIXA "fluxo_caixa.dat" // Nome do arquivo de fluxo de caixa
#define DATA_FILE_DESPESAS "despesas.dat"         // Nome do arquivo de despesas


typedef struct {
    int id;
    float valor;
    char descricao[500];
    int status; // 0 para pendente, 1 para paga
    time_t dataHora;
} Despesa;


typedef struct {
    time_t dataHora;              // Data e hora da transação
    float valor;                  // Valor da transação
    char tipo;                    // 'E' para entrada, 'S' para saída
    char descricao[100];          // Descrição da transação
} Transacao;

// Declarações de funções
void registrarTransacao(char tipo, float valor, const char *descricao);
void gerarRelatorioFluxoCaixa();
void limparBuffer();
float calcularTotalVendas();
float calcularDespesas();
void adicionarDespesa();
void gerarRelatorioFinanceiro();

#endif // FINANCEIRO_H
