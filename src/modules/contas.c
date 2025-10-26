#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <locale.h>
#include <time.h>

#include "vendas.h"
#include "produto.h"
#include "financeiro.h"
#include "main.h"
#include "contas.h"

extern void limparBuffer();
extern void definirCor();

void marcarContaReceberComoPaga(int id);



void menuContasPagar() {
    int opcao;
    mostrarBoasVindas();
    do {
        definirCor(15, 0);
        printf("+--- ## Contas a Pagar ## --------------------------------------------------+\n");
        printf("| [1] Adicionar Conta a Pagar                [0] Voltar                     |\n");
        printf("| [2] Visualizar Contas a Pagar                                             |\n");
        printf("| [3] Marcar Conta a Pagar como Paga                                        |\n");
        printf("+---------------------------------------------------------------------------+\n");
        definirCor(7, 0);
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        switch (opcao) {
        case 1:
            adicionarContaPagar();
            break;
        case 2:
            mostrarBoasVindas();
            visualizarContasPagar();
            break;
        case 3: {
            int id;
            printf("Digite o ID da conta a pagar que deseja marcar como paga: ");
            scanf("%d", &id);
            limparBuffer();
            marcarContaPagarComoPaga(id);
            break;
        }
        case 4:
            printf("Voltando ao menu principal...\n");
            break;
        default:
            printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);
}

void menuContasReceber() {
    int opcao;
    mostrarBoasVindas();
    do {
        definirCor(15, 0);
        printf("+--- ## Contas a Receber ## ---------------------------------------------+\n");
        printf("| [1] Adicionar Conta a Receber                                          |\n");
        printf("| [2] Visualizar Contas a Receber                                        |\n");
        printf("| [3] Marcar Conta a Receber como Paga                                   |\n");
        printf("| [0] Voltar                                                             |\n");
        printf("+------------------------------------------------------------------------+\n");
        definirCor(7, 0);
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            adicionarContaReceber();
            break;
        case 2:
            mostrarBoasVindas();
            visualizarContasReceber();
            break;
        case 3: {
            int id;
            printf("Digite o ID da conta a receber que deseja marcar como paga: ");
            scanf("%d", &id);
            limparBuffer();
            marcarContaReceberComoPaga(id);
            break;
        }
        case 4:
            printf("Voltando ao menu principal...\n");
            break;
        default:
            printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);
}

void menuPrincipalContasPagar() {
    int opcao;
    mostrarBoasVindas();
    do {
        mostrarBoasVindas();
        definirCor(15, 0);
        printf("+--- ## Contas a Pagar/Receber ## ------------------------------------------+\n");
        printf("| [1] Contas a Pagar                                                        |\n");
        printf("| [2] Contas a Receber                                                      |\n");
        printf("| [0] Voltar                                                                |\n");
        printf("+---------------------------------------------------------------------------+\n");
        definirCor(7, 0);
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);


        switch (opcao) {
        case 1:
            mostrarBoasVindas();
            menuContasPagar();
            break;
        case 2:
            mostrarBoasVindas();
            menuContasReceber();
            break;
        case 3:
            printf("Saindo do sistema...\n");
            break;
        default:
            printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);
}

int parseData(const char *dataStr, struct tm *tm) {
    memset(tm, 0, sizeof(struct tm)); // Zera a estrutura 'tm'
    int dia, mes, ano;
    if (sscanf(dataStr, "%d/%d/%d", &dia, &mes, &ano) == 3) {
        tm->tm_mday = dia;
        tm->tm_mon = mes - 1;  // Em 'struct tm', os meses vão de 0 a 11
        tm->tm_year = ano - 1900; // O ano é contado a partir de 1900 em 'struct tm'
        return 1; // Retorna 1 para indicar sucesso
    }
    return 0; // Retorna 0 para indicar falha
}

// Função para visualizar contas a receber
void visualizarContasReceber() {
    FILE *contaFile = fopen(DATA_FILE_CONTAS_RECEBER, "rb");
    if (!contaFile) {
        printf("Erro ao abrir o arquivo de contas a receber!\n");
        return;
    }

    ContaReceber conta;
    char dataFormatada[11];
    printf("+================ ::              Contas a Receber               :: ===================================================================+\n");
    printf("+-------------------+-------------------+--------------------+--------------------+----------------------------------------------------+\n");
    printf("| ID                | Valor             | Data Vencimento    | Status             | Descrição                                          |\n");
    printf("+-------------------+-------------------+--------------------+--------------------+----------------------------------------------------+\n");

    while (fread(&conta, sizeof(ContaReceber), 1, contaFile) == 1) {
        strftime(dataFormatada, sizeof(dataFormatada), "%d/%m/%Y", localtime(&conta.dataVencimento));
        const char *statusStr = conta.status == 0 ? "Pendente" : "Paga";
        const char *cor = conta.status == 0 ? "\033[31m" : "\033[32m"; // Vermelho para Pendente, Verde para Paga
        printf("| %-17d | R$ %-14.2f | %-18s | %s%-18s\033[0m | %-50s |\n",
               conta.id,
               conta.valor,
               dataFormatada,
               cor, statusStr,
               conta.descricao); // Adiciona a descrição
    }

    printf("+-------------------+-------------------+--------------------+--------------------+----------------------------------------------------+\n");
    fclose(contaFile);
}


void adicionarContaReceber() {
    FILE *contaFile = fopen(DATA_FILE_CONTAS_RECEBER, "ab+");
    if (!contaFile) {
        printf("Erro ao abrir o arquivo de contas a receber!\n");
        return;
    }

    ContaReceber novaConta;
    novaConta.status = 0; // Inicia como pendente

    // Gerar ID
    fseek(contaFile, 0, SEEK_END);
    novaConta.id = ftell(contaFile) / sizeof(ContaReceber) + 1; // ID baseado na posição do arquivo

    printf("Digite o valor da conta a receber: R$ ");
    if (scanf("%f", &novaConta.valor) != 1 || novaConta.valor <= 0) {
        printf("Valor da conta inválido!\n");
        fclose(contaFile);
        return;
    }


    printf("Digite uma descrição para a conta: ");
    fgets(novaConta.descricao, sizeof(novaConta.descricao), stdin);
    novaConta.descricao[strcspn(novaConta.descricao, "\n")] = 0; // Remove a nova linha

    printf("Digite a data de vencimento (formato: dd/mm/yyyy): ");
    char dataVencimento[11];
    fgets(dataVencimento, sizeof(dataVencimento), stdin);
    struct tm tm;
    if (!parseData(dataVencimento, &tm)) {
        printf("Data de vencimento inválida!\n");
        fclose(contaFile);
        return;
    }
    novaConta.dataVencimento = mktime(&tm);

    fwrite(&novaConta, sizeof(ContaReceber), 1, contaFile);
    fclose(contaFile);
    printf("Conta a receber adicionada com sucesso!\n");
}

// Função para adicionar uma conta a pagar
void adicionarContaPagar() {
    FILE *contaFile = fopen(DATA_FILE_CONTAS_PAGAR, "ab+");
    if (!contaFile) {
        printf("Erro ao abrir o arquivo de contas a pagar!\n");
        return;
    }

    ContaPagar novaConta;
    novaConta.status = 0; // Inicia como pendente

    // Gerar ID
    fseek(contaFile, 0, SEEK_END);
    novaConta.id = ftell(contaFile) / sizeof(ContaPagar) + 1; // ID baseado na posição do arquivo

    printf("Digite o valor da conta a pagar: R$ ");
    if (scanf("%f", &novaConta.valor) != 1 || novaConta.valor <= 0) {
        printf("Valor da conta inválido!\n");
        fclose(contaFile);
        return;
    }
    limparBuffer();

    printf("Digite uma descrição para a conta: ");
    fgets(novaConta.descricao, sizeof(novaConta.descricao), stdin);
    novaConta.descricao[strcspn(novaConta.descricao, "\n")] = 0; // Remove a nova linha

    printf("Digite a data de vencimento (formato: dd/mm/yyyy): ");
    char dataVencimento[11];
    fgets(dataVencimento, sizeof(dataVencimento), stdin);
    struct tm tm;
    if (!parseData(dataVencimento, &tm)) {
        printf("Data de vencimento inválida!\n");
        fclose(contaFile);
        return;
    }
    novaConta.dataVencimento = mktime(&tm);

    fwrite(&novaConta, sizeof(ContaPagar), 1, contaFile);
    fclose(contaFile);
    printf("Conta a pagar adicionada com sucesso!\n");
}

void visualizarContasPagar() {
    FILE *contaFile = fopen(DATA_FILE_CONTAS_PAGAR, "rb");
    if (!contaFile) {
        printf("Erro ao abrir o arquivo de contas a pagar!\n");
        return;
    }

    ContaPagar conta;
    char dataFormatada[11];
    printf("+================ ::           Contas a Pagar               :: ========================================================================+\n");
    printf("+-------------------+-------------------+--------------------+--------------------+----------------------------------------------------+\n");
    printf("| ID                | Valor             | Data Vencimento    | Status             | Descrição                                          |\n");
    printf("+-------------------+-------------------+--------------------+--------------------+----------------------------------------------------+\n");

    while (fread(&conta, sizeof(ContaPagar), 1, contaFile) == 1) {
        strftime(dataFormatada, sizeof(dataFormatada), "%d/%m/%Y", localtime(&conta.dataVencimento));
        const char *statusStr = conta.status == 0 ? "Pendente" : "Paga";
        const char *cor = conta.status == 0 ? "\033[31m" : "\033[32m"; // Vermelho para Pendente, Verde para Paga
        printf("| %-17d | R$ %-14.2f | %-18s | %s%-18s\033[0m | %-50s |\n",
               conta.id,
               conta.valor,
               dataFormatada,
               cor, statusStr,
               conta.descricao);
    }

    printf("+-------------------+-------------------+--------------------+--------------------+----------------------------------------------------+\n");
    fclose(contaFile);
}


void marcarContaPagarComoPaga(int id) {
    FILE *contaFile = fopen(DATA_FILE_CONTAS_PAGAR, "rb+");
    if (!contaFile) {
        printf("Erro ao abrir o arquivo de contas a pagar!\n");
        return;
    }

    ContaPagar conta;
    int encontrado = 0;
    while (fread(&conta, sizeof(ContaPagar), 1, contaFile) == 1) {
        if (conta.id == id) {
            conta.status = 1; // Marcar como paga
            fseek(contaFile, -sizeof(ContaPagar), SEEK_CUR);
            fwrite(&conta, sizeof(ContaPagar), 1, contaFile);
            printf("Conta a pagar marcada como paga com sucesso!\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Conta a pagar com ID %d não encontrada!\n", id);
    }

    fclose(contaFile);
}

void marcarContaReceberComoPaga(int id) {
    FILE *contaFile = fopen(DATA_FILE_CONTAS_RECEBER, "rb+");
    if (!contaFile) {
        printf("Erro ao abrir o arquivo de contas a receber!\n");
        return;
    }

    ContaReceber conta;
    int encontrado = 0;
    while (fread(&conta, sizeof(ContaReceber), 1, contaFile) == 1) {
        if (conta.id == id) {
            conta.status = 1; // Marcar como paga
            fseek(contaFile, -sizeof(ContaReceber), SEEK_CUR);
            fwrite(&conta, sizeof(ContaReceber), 1, contaFile);
            printf("Conta a receber marcada como paga com sucesso!\n");
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Conta a receber com ID %d não encontrada!\n", id);
    }

    fclose(contaFile);
}


