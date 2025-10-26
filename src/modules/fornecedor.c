#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>
#include <stdbool.h>
#include "fornecedor.h"

void lerString(char *buffer, int tamanho, const char *prompt) {
    printf("%s", prompt);
    fflush(stdin); // Limpa o buffer antes de ler
    if (fgets(buffer, tamanho, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = 0; // Remove a nova linha
    }
}

// Função para contar fornecedores


int contarFornecedores() {
    FILE *dataFile = fopen(FORNECEDOR_DATA_FILE, "rb"); // Use o nome correto da constante
    if (!dataFile) {
        return 0;
    }

    fseek(dataFile, 0, SEEK_END);
    long tamanho = ftell(dataFile);
    fclose(dataFile);

    return tamanho / sizeof(Fornecedor);
}

// Função para cadastrar um fornecedor
void cadastrarFornecedor(int *quantidade) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    FILE *dataFile, *indexFile;
    char continuar = 'S';

    do {
        FILE *dataFile = fopen(FORNECEDOR_DATA_FILE, "ab+");
        indexFile = fopen(FORNECEDOR_INDEX_FILE , "ab+");

        if (!dataFile || !indexFile) {
            printf("Erro ao abrir os arquivos de dados ou índice!\n");
            if (dataFile) fclose(dataFile);
            if (indexFile) fclose(indexFile);
            return;
        }

        Fornecedor novoFornecedor;
        IndexEntryFornecedor indice;
        bool idExistente = false;

        printf("Digite o ID do fornecedor: ");
        scanf("%d", &novoFornecedor.id);
        getchar(); // Limpa o buffer

        // Verificar se o ID já existe
        while (fread(&indice, sizeof(IndexEntryFornecedor), 1, indexFile)) {
            if (indice.id == novoFornecedor.id) {
                idExistente = true;
                break;
            }
        }

        if (idExistente) {
            printf("ID %d já existe! Escolha outro ID.\n", novoFornecedor.id);
            fclose(dataFile);
            fclose(indexFile);
            return;
        }

        // Lê os dados do fornecedor
        lerString(novoFornecedor.nome_empresa, MAX_NOME_EMPRESA, "Digite o nome da empresa: ");
        lerString(novoFornecedor.nome_fantasia, MAX_NOME_FANTASIA, "Digite o nome fantasia: ");
        lerString(novoFornecedor.cnpj, MAX_CNPJ, "Digite o CNPJ: ");
        lerString(novoFornecedor.inscricao_estadual, MAX_INSCRICAO_ESTADUAL, "Digite a inscrição estadual: ");
        lerString(novoFornecedor.inscricao_municipal, MAX_INSCRICAO_MUNICIPAL, "Digite a inscrição municipal: ");
        lerString(novoFornecedor.endereco, MAX_ENDERECO, "Digite o endereço: ");
        lerString(novoFornecedor.telefone, MAX_TELEFONE, "Digite o telefone: ");
        lerString(novoFornecedor.email, MAX_EMAIL, "Digite o email: ");
        lerString(novoFornecedor.atividade_principal, MAX_ATIVIDADE, "Digite a atividade principal: ");
        lerString(novoFornecedor.responsavel_setor, MAX_RESPONSAVEL, "Digite o responsável pelo setor: ");

        long posicao = ftell(dataFile);
        fwrite(&novoFornecedor, sizeof(Fornecedor), 1, dataFile);

        // Criar nova entrada de índice
        IndexEntryFornecedor indiceNovo = {novoFornecedor.id, posicao};
        fwrite(&indiceNovo, sizeof(IndexEntryFornecedor), 1, indexFile);

        fclose(dataFile);
        fclose(indexFile);

        (*quantidade)++;
        SetConsoleTextAttribute(hConsole, 10);
        printf("Fornecedor cadastrado com sucesso!\n\n");
        SetConsoleTextAttribute(hConsole, 7);
        // Pergunta se deseja continuar cadastrando
        printf("Deseja continuar cadastrando? (S/N): ");
        char buffer[10];
        fgets(buffer, sizeof(buffer), stdin);
        continuar = toupper(buffer[0]);

    } while (continuar == 'S');
}

// Função para listar fornecedores
void listarFornecedores() {
    int quantidade = contarFornecedores();
    if (quantidade == 0) {
        printf("Nenhum fornecedor cadastrado no sistema.\n");
        return;
    }

    FILE *dataFile = fopen(FORNECEDOR_DATA_FILE, "rb");
    if (!dataFile) {
        printf("Erro ao abrir o arquivo de dados!\n");
        return;
    }

    Fornecedor fornecedor;

    printf("+-------+---------------------------------+--------------------------------+-------------------+----------------------+----------------------+-------------------------+\n");
    printf("| ID    | Nome da Empresa                 | Nome Fantasia                  | CNPJ              | Inscrição Estadual   | Inscrição Municipal  | Responsável             |\n");
    printf("+-------+---------------------------------+--------------------------------+-------------------+----------------------+----------------------+-------------------------+\n");

    for (int i = 0; i < quantidade; i++) {
        fseek(dataFile, i * sizeof(Fornecedor), SEEK_SET);
        fread(&fornecedor, sizeof(Fornecedor), 1, dataFile);

        if (fornecedor.id > 0) { // Exibe apenas fornecedores válidos
            printf("| %-5d | %-31s | %-20s           | %-18s | %-20s | %-20s | %-22s |\n",
                   fornecedor.id, fornecedor.nome_empresa, fornecedor.nome_fantasia, fornecedor.cnpj,
                   fornecedor.inscricao_estadual, fornecedor.inscricao_municipal, fornecedor.responsavel_setor);
        }
    }


    printf("+-------+---------------------------------+--------------------------------+--------------------+----------------------+----------------------+------------------------+\n");
    getchar();
    getchar();
    fclose(dataFile);
}


// Função para editar um fornecedor pelo ID
void editarFornecedor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    FILE *dataFile = fopen(FORNECEDOR_DATA_FILE, "rb+");
    if (!dataFile) {
        printf("Erro ao abrir o arquivo de dados de fornecedores!\n");
        return;
    }

    int idEditar;
    printf("Digite o ID do fornecedor a ser editado: ");
    scanf("%d", &idEditar);
    getchar(); // Limpar o buffer

    Fornecedor fornecedor;
    bool fornecedorEncontrado = false;
    long posicao;

    // Percorre o arquivo de dados para encontrar o fornecedor
    while (fread(&fornecedor, sizeof(Fornecedor), 1, dataFile)) {
        if (fornecedor.id == idEditar) {
            fornecedorEncontrado = true;
            posicao = ftell(dataFile) - sizeof(Fornecedor);
            break;
        }
    }

    if (fornecedorEncontrado) {


        printf("Fornecedor encontrado! Selecione o campo que deseja editar:\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
        printf("+---------------------------------------------------------+\n");
        printf("|    [1] Nome da Empresa     [5] Inscrição Municipal      |\n");
        printf("|    [2] Nome Fantasia       [6] Email                    |\n");
        printf("|    [3] CNPJ                [7] Atividade                |\n");
        printf("|    [4] Inscrição Estadual  [8] Responsável              |\n");
        printf("+---------------------------------------------------------+\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        printf("Escolha uma opção (1-8): ");

        int opcao;
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer

        // Atualiza apenas o campo escolhido
        switch (opcao) {
        case 1:
            lerString(fornecedor.nome_empresa, MAX_NOME_EMPRESA, "Digite o novo nome da empresa: ");
            break;
        case 2:
            lerString(fornecedor.nome_fantasia, MAX_NOME_FANTASIA, "Digite o novo nome fantasia: ");
            break;
        case 3:
            lerString(fornecedor.cnpj, MAX_CNPJ, "Digite o novo CNPJ: ");
            break;
        case 4:
            lerString(fornecedor.inscricao_estadual, MAX_INSCRICAO_ESTADUAL, "Digite a nova inscrição estadual: ");
            break;
        case 5:
            lerString(fornecedor.inscricao_municipal, MAX_INSCRICAO_MUNICIPAL, "Digite a nova inscrição municipal: ");
            break;
        case 6:
            lerString(fornecedor.email, MAX_EMAIL, "Digite o novo email: ");
            break;
        case 7:
            lerString(fornecedor.atividade_principal, MAX_ATIVIDADE, "Digite a nova atividade principal: ");
            break;
        case 8:
            lerString(fornecedor.responsavel_setor, MAX_RESPONSAVEL, "Digite o novo responsável pelo setor: ");
            break;
        default:
            printf("Opção inválida!\n");
            fclose(dataFile);
            return;
        }

        fseek(dataFile, posicao, SEEK_SET);
        fwrite(&fornecedor, sizeof(Fornecedor), 1, dataFile);
        SetConsoleTextAttribute(hConsole, 10);
        printf("Fornecedor atualizado com sucesso!\n");
        SetConsoleTextAttribute(hConsole, 7);
    } else {
        printf("Fornecedor com ID %d não encontrado.\n", idEditar);
    }

    fclose(dataFile);
}

// Função para remover um fornecedor
void removerFornecedor(int *quantidade) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    FILE *dataFile = fopen(FORNECEDOR_DATA_FILE, "rb+");
    if (!dataFile) {
        printf("Erro ao abrir o arquivo de dados de fornecedores!\n");
        return;
    }

    int idRemover;
    printf("Digite o ID do fornecedor a ser removido: ");
    scanf("%d", &idRemover);
    getchar(); // Limpar o buffer

    Fornecedor fornecedor;
    bool fornecedorEncontrado = false;
    long posicao;

    // Percorre o arquivo de dados para encontrar o fornecedor
    while (fread(&fornecedor, sizeof(Fornecedor), 1, dataFile)) {
        if (fornecedor.id == idRemover) {
            fornecedorEncontrado = true;
            posicao = ftell(dataFile) - sizeof(Fornecedor);
            break;
        }
    }

    if (fornecedorEncontrado) {
        fornecedor.id = -1; // Marcar como removido
        fseek(dataFile, posicao, SEEK_SET);
        fwrite(&fornecedor, sizeof(Fornecedor), 1, dataFile);
        (*quantidade)--;
        SetConsoleTextAttribute(hConsole, 10);
        printf("Fornecedor removido com sucesso!\n");
        SetConsoleTextAttribute(hConsole, 7);
    } else {
        printf("Fornecedor com ID %d não encontrado.\n", idRemover);
    }

    fclose(dataFile);
}
