#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include "vendas.h"
#include "produto.h"
#include "financeiro.h"
#include "main.h"
#include "contas.h"
#include "link.h"



// Função para limpar o buffer de entrada
extern void mostrarMenuFinanceiro();
extern void definirCor();
extern void limparBuffer();
extern void mostrarBoasVindas();



void relatorioVendasPorPeriodo();
void visualizarDespesas();
void marcarDespesaComoPagaPorID();
// Função para calcular o total de vendas
float calcularTotalVendas() {
    FILE *vendaFile = fopen(DATA_FILE_VENDA, "rb");
    if (!vendaFile) {
        printf("Erro ao abrir o arquivo de vendas!\n");
        return 0.0f;
    }

    Venda venda;
    float totalVendas = 0.0f;

    // Lê cada venda e soma o total
    while (fread(&venda, sizeof(Venda), 1, vendaFile) == 1) {
        totalVendas += venda.valorTotal;
    }

    fclose(vendaFile);
    return totalVendas;
}

// Função para calcular as despesas
float calcularDespesas() {
    FILE *despesaFile = fopen(DATA_FILE_DESPESAS, "rb");
    if (!despesaFile) {
        printf("Erro ao abrir o arquivo de despesas!\n");
        return 0.0f;
    }

    float despesa, totalDespesas = 0.0f;
    char descricao[100]; // Para ler a descrição da despesa, se necessário

    // Leitura do arquivo de despesas
    while (fread(&despesa, sizeof(float), 1, despesaFile) == 1) {
        // Leitura da descrição, caso necessário
        if (fread(descricao, sizeof(descricao), 1, despesaFile) != 1) {
            printf("Erro ao ler descrição da despesa!\n");
            break;
        }

        // Acumula o valor da despesa
        totalDespesas += despesa;

        // Debug para verificar o valor da despesa e a descrição
        printf("Despesa: R$%.2f, Descrição: %s\n", despesa, descricao);
    }

    fclose(despesaFile);
    return totalDespesas;
}



void visualizarDespesas() {
    FILE *despesaFile = fopen(DATA_FILE_DESPESAS, "rb");
    if (!despesaFile) {
        printf("Erro ao abrir o arquivo de despesas!\n");
        return;
    }

    Despesa despesa;
    float totalDespesasPendentes = 0.0;  // Variável para armazenar o total das despesas pendentes
    float totalDespesasPagas = 0.0;      // Variável para armazenar o total das despesas pagas

    printf("+================ ::                 Despesas Registradas                :: =================================================================================================+\n");
    printf("+-------------------+-------------------+--------------------+--------------------------------------------------------------------------------------------------------------------------------------------------------+\n");
    printf("| ID                | Valor             | Status             | Descrição                                                                                                                                              |\n");
    printf("+-------------------+-------------------+--------------------+--------------------------------------------------------------------------------------------------------------------------------------------------------+\n");

    // Lê cada despesa
    while (fread(&despesa, sizeof(Despesa), 1, despesaFile) == 1) {
        // Determina o status e a cor como uma string
        const char *statusStr;
        const char *cor;
        if (despesa.status == 0) { // Pendente
            statusStr = "Pendente";
            cor = "\033[31m"; // Vermelho
            totalDespesasPendentes += despesa.valor;  // Acumula o valor das despesas pendentes
        } else { // Paga
            statusStr = "Paga";
            cor = "\033[32m"; // Verde
            totalDespesasPagas += despesa.valor;  // Acumula o valor das despesas pagas
        }

        // Exibe as informações da despesa, incluindo o status com cor
        printf("| %-17d | R$ %-14.2f | %s%-18s\033[0m | %-150s |\n", despesa.id, despesa.valor, cor, statusStr, despesa.descricao);
    }

    printf("+-------------------+-------------------+--------------------+--------------------------------------------------------------------------------------------------------------------------------------------------------+\n");

    // Exibe o total das despesas pendentes dentro do grid, com a cor vermelha
    printf("| %-17s | R$ %-14.2f | %s%-18s\033[0m | %-150s \n", "Total Pendentes", totalDespesasPendentes, "\033[31m", "Pendente", "");

    // Exibe o total das despesas pagas dentro do grid, com a cor verde
    printf("| %-17s | R$ %-14.2f | %s%-18s\033[0m | %-150s \n", "Total Pagas", totalDespesasPagas, "\033[32m", "Paga", "");

    printf("+------------------------------------------------------------+\n");

    fclose(despesaFile);
}





void menuDespesas() {
    int opcao;
    mostrarBoasVindas();
    do {
        definirCor(15, 0);
        printf("\n");
        printf("+--- ## Contas ##  --------------------------------------------------+\n");
        printf("|    [1] Adicionar Despesa        [4] Marcar Despesa como Paga       |\n");
        printf("|    [2] Visualizar Despesas      [5] Gerar Relatório Financeiro     |\n");
        printf("|    [3] Remover Despesa          [0] Voltar                         |\n");
        printf("+--------------------------------------------------------------------+\n");
        definirCor(7, 0);

        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
        case 1:

            adicionarDespesa();
            break;
        case 2:
            mostrarBoasVindas();
            visualizarDespesas(); // Chamada da nova função
            break;
        case 3:
            mostrarBoasVindas();
            removerDespesa(); // Chamada para remover despesa
            break;
        case 4:

            marcarDespesaComoPagaPorID(); // Chamada para marcar despesa como paga
            break;
        case 5:
            mostrarBoasVindas();
            gerarRelatorioFinanceiro();
            break;
        case 6:
            printf("Voltando ao menu principal...\n");
            break;
        default:
            printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);
}



void menuRelatorios() {
    int opcao;
    mostrarBoasVindas();
    do {
        definirCor(15, 0);
        printf("+--- ## Relatorios ##  ----------------------------------------+\n");
        printf("|    [1] Vendas por Período              [0] Voltar            |\n");
        printf("|    [2] Produtos Mais Vendidos                                |\n");
        printf("|    [3] Fluxo de Caixa                                        |\n");
        printf("+--------------------------------------------------------------+\n");
        definirCor(7, 0);
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {

        case 1: {
            char dataInicioStr[11]; // dd/mm/aaaa
            char dataFimStr[11];    // dd/mm/aaaa
            time_t dataInicio, dataFim;
            struct tm tm;

            // Solicita ao usuário as datas de início e fim
            printf("Digite a data de início (dd/mm/aaaa): ");
            scanf("%10s", dataInicioStr);
            printf("Digite a data de fim (dd/mm/aaaa): ");
            scanf("%10s", dataFimStr);

            // Verificação do formato da data
            if (strlen(dataInicioStr) != 10 || strlen(dataFimStr) != 10 || dataInicioStr[2] != '/' || dataFimStr[2] != '/') {
                printf("Formato de data inválido! Use dd/mm/aaaa.\n");
                break;
            }

            // Converte a data de início
            sscanf(dataInicioStr, "%d/%d/%d", &tm.tm_mday, &tm.tm_mon, &tm.tm_year);
            tm.tm_mon -= 1; // Ajusta para o formato 0-11
            tm.tm_year -= 1900; // Ajusta para o ano desde 1900
            tm.tm_hour = 0; // Inicializa horas, minutos e segundos
            tm.tm_min = 0;
            tm.tm_sec = 0;
            tm.tm_isdst = -1; // Ajusta automaticamente para horário de verão
            dataInicio = mktime(&tm);

            // Converte a data de fim
            sscanf(dataFimStr, "%d/%d/%d", &tm.tm_mday, &tm.tm_mon, &tm.tm_year);
            tm.tm_mon -= 1; // Ajusta para o formato 0-11
            tm.tm_year -= 1900; // Ajusta para o ano desde 1900
            tm.tm_hour = 0; // Inicializa horas, minutos e segundos
            tm.tm_min = 0;
            tm.tm_sec = 0;
            tm.tm_isdst = -1; // Ajusta automaticamente para horário de verão
            dataFim = mktime(&tm);

            // Gera o relatório de vendas por período
            relatorioVendasPorPeriodo(dataInicio, dataFim);
            break;
        }
        break;
        case 2:
            mostrarBoasVindas();
            relatorioProdutosMaisVendidos();
            break;
        case 3:
            mostrarBoasVindas();
            gerarRelatorioFluxoCaixa();
            break;
        case 0:
            printf("Voltando ao menu principal...\n");
            return; // Retorna para a função que chamou menuRelatorios
        default:
            printf("Opção inválida! Tente novamente.\n");
        }
    } while (1); // Loop infinito que só é quebrado pelo return
}

void relatorioProdutosMaisVendidos() {
    FILE *dataFile, *indexFile;
    Produto produto;
    int *quantidades;  // Ponteiro para o array de quantidades
    int numProdutos = 0;  // Contador de produtos

    dataFile = fopen(DATA_FILE_PRODUTO, "rb");
    indexFile = fopen(INDEX_FILE_PRODUTO, "rb");

    if (!dataFile || !indexFile) {
        printf("Erro ao abrir os arquivos de dados ou índice!\n");
        if (dataFile) fclose(dataFile);
        if (indexFile) fclose(indexFile);
        return;
    }

    // Contar o número de produtos no arquivo de dados
    while (fread(&produto, sizeof(Produto), 1, dataFile) == 1) {
        numProdutos++;
    }

    // Alocar memória dinamicamente para armazenar as quantidades
    quantidades = (int *)malloc(numProdutos * sizeof(int));
    if (quantidades == NULL) {
        printf("Erro ao alocar memória para as quantidades de produtos!\n");
        fclose(dataFile);
        fclose(indexFile);
        return;
    }

    // Inicializar as quantidades
    for (int i = 0; i < numProdutos; i++) {
        quantidades[i] = 0;
    }

    // Percorrer novamente o arquivo para processar as quantidades
    fseek(dataFile, 0, SEEK_SET);  // Voltar para o início do arquivo de dados
    while (fread(&produto, sizeof(Produto), 1, dataFile) == 1) {
        // Supondo que o campo de quantidade já esteja sendo atualizado com as vendas
        quantidades[numProdutos] += produto.quantidade;  // Exemplo, ajustando conforme a lógica de vendas
    }

    // Exibir o relatório dos produtos mais vendidos
    printf("Relatório de Produtos Mais Vendidos:\n");
    for (int i = 0; i < numProdutos; i++) {
        printf("Produto %d: Quantidade Vendida: %d\n", i + 1, quantidades[i]);
    }

    free(quantidades);  // Liberar a memória alocada

    fclose(dataFile);
    fclose(indexFile);
}





void relatorioVendasPorPeriodo(time_t dataInicio, time_t dataFim) {
    FILE *vendaFile = fopen("vendas.dat", "rb");
    if (!vendaFile) {
        printf("Erro ao abrir o arquivo de vendas!\n");
        return;
    }

    Venda venda;
    Produto produto;
    char buffer[20];
    struct tm *tm_info;

    printf("\n=== Relatório de Vendas por Período ===\n");
    printf("+--------------+------------------------------------+------------+---------------+---------------------+\n");
    printf("|  ID Produto  |          Nome do Produto           | Quantidade |  Valor Total  |   Data/Hora         |\n");
    printf("+--------------+------------------------------------+------------+---------------+---------------------+\n");

    // Variáveis para o valor total das vendas
    double valorTotalVendas = 0.0;
    int vendasEncontradas = 0;

    // Criação do arquivo de relatório
    FILE *relatorioFile = fopen("C:\\temp\\relatorio_vendas.txt", "w");
    if (!relatorioFile) {
        printf("Erro ao abrir o arquivo para salvar o relatório!\n");
        fclose(vendaFile);
        return;
    }

    // Escreve o cabeçalho no arquivo de relatório
    fprintf(relatorioFile, "\n=== Relatório de Vendas por Período ===\n");
    fprintf(relatorioFile, "+--------------+------------------------------------+------------+---------------+---------------------+\n");
    fprintf(relatorioFile, "|  ID Produto  |          Nome do Produto           | Quantidade |  Valor Total  |   Data/Hora         |\n");
    fprintf(relatorioFile, "+--------------+------------------------------------+------------+---------------+---------------------+\n");

    while (fread(&venda, sizeof(Venda), 1, vendaFile) == 1) {
        // Verifica se a venda está dentro do período
        if (difftime(venda.dataHora, dataInicio) >= 0 && difftime(dataFim, venda.dataHora) >= 0) {
            tm_info = localtime(&venda.dataHora);
            strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", tm_info);

            // Busca o produto correspondente à venda
            if (buscarProdutoPorId(venda.idProduto, &produto)) {
                // Recalcula o valor da venda
                double valorVenda = venda.quantidade * produto.precoVenda;

                printf("| %-11d  | %-30s     | %-10d | R$%-11.2f | %-16s |\n",
                       venda.idProduto, produto.nome, venda.quantidade, valorVenda, buffer);
                fprintf(relatorioFile, "| %-11d  | %-30s     | %-10d | R$%-11.2f | %-16s |\n",
                        venda.idProduto, produto.nome, venda.quantidade, valorVenda, buffer);

                valorTotalVendas += valorVenda; // Soma o valor calculado ao total
            } else {
                // Caso o produto não seja encontrado
                printf("| %-11d  | %-30s     | %-10d | R$%-11.2f | %-16s |\n",
                       venda.idProduto, "Produto não encontrado", venda.quantidade, venda.valorTotal, buffer);
                fprintf(relatorioFile, "| %-11d  | %-30s     | %-10d | R$%-11.2f | %-16s |\n",
                        venda.idProduto, "Produto não encontrado", venda.quantidade, venda.valorTotal, buffer);

                valorTotalVendas += venda.valorTotal; // Soma o valor diretamente, caso já esteja armazenado
            }

            vendasEncontradas = 1; // Marca que pelo menos uma venda foi encontrada
        }
    }

    if (!vendasEncontradas) {
        printf("|                     Nenhuma venda encontrada no período!                      |\n");
        fprintf(relatorioFile, "|                     Nenhuma venda encontrada no período!                      |\n");
    }

    printf("+--------------+------------------------------------+------------+---------------+---------------------+\n");
    fprintf(relatorioFile, "+--------------+------------------------------------+------------+---------------+---------------------+\n");

    // Adiciona o total no final do relatório
    printf("\nValor Total das Vendas no Período: R$ %.2f\n", valorTotalVendas);
    fprintf(relatorioFile, "\nValor Total das Vendas no Período: R$ %.2f\n", valorTotalVendas);

    fclose(vendaFile);
    fclose(relatorioFile);
}





void registrarTransacao(char tipo, float valor, const char *descricao) {
    // Valida o valor da transação
    if (valor < 0) {
        printf("Valor da transação deve ser positivo.\n");
        return;
    }

    Transacao transacao;
    transacao.dataHora = time(NULL);
    transacao.valor = valor;
    transacao.tipo = tipo;

    // Copia a descrição com segurança
    strncpy(transacao.descricao, descricao, sizeof(transacao.descricao) - 1);
    transacao.descricao[sizeof(transacao.descricao) - 1] = '\0'; // Garante a terminação

    FILE *file = fopen(DATA_FILE_FLUXO_CAIXA, "ab");
    if (!file) {
        printf("Erro ao abrir o arquivo de fluxo de caixa!\n");
        return;
    }

    fwrite(&transacao, sizeof(Transacao), 1, file);
    fclose(file);

    printf("Transação registrada com sucesso!\n");
}


// Função para gerar um relatório do fluxo de caixa
void gerarRelatorioFluxoCaixa() {
    FILE *file = fopen(DATA_FILE_FLUXO_CAIXA, "rb");
    if (!file) {
        printf("Erro ao abrir o arquivo de fluxo de caixa!\n");
        return;
    }

    Transacao transacao;
    float saldoInicial = 0.0f;
    float saldoFinal = 0.0f;
    float totalEntradas = 0.0f;
    float totalSaidas = 0.0f;
    char buffer[20];
    struct tm *tm_info;

    printf("\n=== Relatório de Fluxo de Caixa ===\n");
    printf("+---------------------+---------+-------------+-----------------------------------+\n");
    printf("| Data/Hora           | Tipo    | Valor       | Descrição                         |\n");
    printf("+---------------------+---------+-------------+-----------------------------------+\n");

    while (fread(&transacao, sizeof(Transacao), 1, file) == 1) {
        tm_info = localtime(&transacao.dataHora);
        strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", tm_info);

        printf("| %-19s | %-7c | R$ %-9.2f | %-33s |\n",
               buffer, transacao.tipo, transacao.valor, transacao.descricao);

        if (transacao.tipo == 'E') {
            totalEntradas += transacao.valor;
        } else if (transacao.tipo == 'S') {
            totalSaidas += transacao.valor;
        }
    }

    saldoFinal = saldoInicial + totalEntradas - totalSaidas;

    printf("+---------------------+---------+-------------+-----------------------------------+\n");
    printf("Total de Entradas: R$ %.2f\n", totalEntradas);
    printf("Total de Saídas:   R$ %.2f\n", totalSaidas);
    printf("Saldo Final:       R$ %.2f\n\n", saldoFinal);

    fclose(file);
}
void marcarDespesaComoPaga(int id) {
    FILE *despesaFile = fopen(DATA_FILE_DESPESAS, "rb+");
    if (!despesaFile) {
        printf("Erro ao abrir o arquivo de despesas!\n");
        return;
    }

    Despesa despesa;
    int encontrado = 0;

    // Lê cada despesa do arquivo
    while (fread(&despesa, sizeof(Despesa), 1, despesaFile) == 1) {
        if (despesa.id == id) { // Verifica se o ID da despesa corresponde
            despesa.status = 1; // Marca como paga
            fseek(despesaFile, -sizeof(Despesa), SEEK_CUR); // Volta para a posição da despesa
            fwrite(&despesa, sizeof(Despesa), 1, despesaFile); // Atualiza a despesa
            encontrado = 1; // Marca que a despesa foi encontrada
            break; // Sai do loop após encontrar a despesa
        }
    }

    fclose(despesaFile); // Fecha o arquivo

    // Mensagem para o usuário
    if (encontrado) {
        printf("Despesa marcada como paga com sucesso!\n");
    } else {
        printf("Despesa com ID %d não encontrada!\n", id);
    }
}

void marcarDespesaComoPagaPorID() {
    int id;
    printf("Digite o ID da despesa que deseja marcar como paga: ");
    if (scanf("%d", &id) != 1) {
        printf("ID inválido!\n");
        limparBuffer();
        return;
    }
    limparBuffer(); // Limpa o buffer após a leitura

    // Chama a função para marcar a despesa como paga
    marcarDespesaComoPaga(id);
}




void removerDespesa() {
    int id;
    printf("Digite o ID da despesa a ser removida: ");
    scanf("%d", &id);
    limparBuffer();

    FILE *despesaFile = fopen(DATA_FILE_DESPESAS, "rb");
    FILE *tempFile = fopen("temp.dat", "wb");
    if (!despesaFile || !tempFile) {
        printf("Erro ao abrir os arquivos!\n");
        if (despesaFile) fclose(despesaFile);
        if (tempFile) fclose(tempFile);
        return;
    }

    Despesa despesa;
    int found = 0;

    while (fread(&despesa, sizeof(Despesa), 1, despesaFile)) {
        if (despesa.id == id) {
            found = 1; // Marca que a despesa foi encontrada
            printf("Despesa com ID %d removida com sucesso!\n", id);
            continue; // Não grava a despesa removida no arquivo temporário
        }
        fwrite(&despesa, sizeof(Despesa), 1, tempFile);
    }

    fclose(despesaFile);
    fclose(tempFile);

    if (found) {
        // Renomeia o arquivo temporário para o original
        remove(DATA_FILE_DESPESAS);
        rename("temp.dat", DATA_FILE_DESPESAS);
    } else {
        remove("temp.dat"); // Remove o arquivo temporário se nada foi encontrado
        printf("Despesa com ID %d não encontrada!\n", id);
    }
}

// Função para adicionar uma nova despesa aos registros
void adicionarDespesa() {
    FILE *despesaFile = fopen(DATA_FILE_DESPESAS, "ab+");
    if (!despesaFile) {
        printf("Erro ao abrir o arquivo de despesas!\n");
        return;
    }

    Despesa novaDespesa;
    novaDespesa.dataHora = time(NULL);
    novaDespesa.status = 0; // Inicia como pendente

    // Gerar ID
    fseek(despesaFile, 0, SEEK_END);
    long numRegistros = ftell(despesaFile) / sizeof(Despesa);
    novaDespesa.id = numRegistros > 0 ? numRegistros + 1 : 1; // ID baseado na contagem de registros

    printf("Digite o valor da despesa: R$ ");
    if (scanf("%f", &novaDespesa.valor) != 1 || novaDespesa.valor <= 0) {
        printf("Valor de despesa inválido!\n");
        fclose(despesaFile);
        return;
    }
    limparBuffer();

    printf("Digite uma descrição para a despesa: ");
    fgets(novaDespesa.descricao, sizeof(novaDespesa.descricao), stdin);
    novaDespesa.descricao[strcspn(novaDespesa.descricao, "\n")] = 0; // Remove a nova linha

    fwrite(&novaDespesa, sizeof(Despesa), 1, despesaFile);
    fclose(despesaFile);
    printf("Despesa adicionada com sucesso! ID: %d\n", novaDespesa.id);
}




// Função para gerar um relatório financeiro mostrando receitas, despesas e lucro/prejuízo
#include <stdio.h>
#include <time.h>

extern void relatorioVendasPorPeriodo(time_t dataInicio, time_t dataFim);
extern void visualizarDespesas();
extern void gerarRelatorioFluxoCaixa();
extern float calcularTotalVendas();
extern float calcularDespesas();

void gerarRelatorioFinanceiro() {

    time_t dataInicio, dataFim;
    struct tm tm;
    char dataInicioStr[11], dataFimStr[11];

    // Abre o arquivo para salvar o relatório
    FILE *arquivo = fopen("C:\\temp\\relatorio.txt", "w");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo para salvar o relatório.\n");
        return;
    }

    // Pergunta ao usuário as datas para o relatório
    printf("Digite a data de início para o relatório (dd/mm/aaaa): ");
    scanf("%10s", dataInicioStr);
    printf("Digite a data de fim para o relatório (dd/mm/aaaa): ");
    scanf("%10s", dataFimStr);

    // Converte a data de início
    sscanf(dataInicioStr, "%d/%d/%d", &tm.tm_mday, &tm.tm_mon, &tm.tm_year);
    tm.tm_mon -= 1; // Ajusta para o formato 0-11
    tm.tm_year -= 1900; // Ajusta para o ano desde 1900
    tm.tm_hour = 0;
    tm.tm_min = 0;
    tm.tm_sec = 0;
    tm.tm_isdst = -1;
    dataInicio = mktime(&tm);

    // Converte a data de fim
    sscanf(dataFimStr, "%d/%d/%d", &tm.tm_mday, &tm.tm_mon, &tm.tm_year);
    tm.tm_mon -= 1;
    tm.tm_year -= 1900;
    tm.tm_hour = 0;
    tm.tm_min = 0;
    tm.tm_sec = 0;
    tm.tm_isdst = -1;
    dataFim = mktime(&tm);

    // Escreve no arquivo o cabeçalho do relatório
    fprintf(arquivo, "\n=== Relatório Financeiro ===\n");

    // Relatório de Vendas
    fprintf(arquivo, "\n--- Relatório de Vendas ---\n");
    relatorioVendasPorPeriodo(dataInicio, dataFim);
    fprintf(arquivo, "\n");

    // Relatório de Despesas
    fprintf(arquivo, "--- Relatório de Despesas ---\n");
    visualizarDespesas();
    fprintf(arquivo, "\n");

    // Relatório de Fluxo de Caixa
    fprintf(arquivo, "--- Relatório de Fluxo de Caixa ---\n");
    gerarRelatorioFluxoCaixa();
    fprintf(arquivo, "\n");

    // Calculando totais financeiros
    float totalVendas = calcularTotalVendas();
    float totalDespesas = calcularDespesas();
    float saldoFinal = totalVendas - totalDespesas;

    // Escreve o resumo financeiro no arquivo
    fprintf(arquivo, "\n=== Resumo Financeiro ===\n");
    fprintf(arquivo, "Total de Vendas: R$ %.2f\n", totalVendas);
    fprintf(arquivo, "Total de Despesas: R$ %.2f\n", totalDespesas);
    fprintf(arquivo, "Saldo Final: R$ %.2f\n", saldoFinal);

    fprintf(arquivo, "\nRelatório gerado com sucesso!\n");

    // Fecha o arquivo
    fclose(arquivo);

    // Mensagem para o usuário
    printf("\nRelatório salvo em C:\\temp\\relatorio.txt\n");
}


