#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#include <ctype.h>
#include <windows.h>
#include <stdbool.h>
#include "cliente.h"
#include "main.h"



// Macro para uso no listar usuário, não faz referência ao usuario.h
#define MAX_NOME       32
#define MAX_CPF        16 // Considerando o formato XXX.XXX.XXX-XX
#define MAX_RG         15 // Considerando o formato XX.XXX.XXX-X
#define MAX_TELEFONE   16 // Considerando o formato (XX) XXXXX-XXXX
#define MAX_ENDERECO   31
#define MAX_EMAIL      25
#define MAX_DATA       11 // Formato DD/MM/AAAA

extern void definiCor();
extern void lerString(char *buffer, int tamanho, const char *prompt); // Especificando os parâmetros
extern void mostrarBoasVindas();
extern void truncarString();


// Função para contar clientes
int contarClientes() {
    FILE *dataFile = fopen(DATA_FILE, "rb");
    if (!dataFile) {
        return 0; // Retorna 0 se o arquivo não puder ser aberto
    }

    fseek(dataFile, 0, SEEK_END);
    long tamanho = ftell(dataFile);
    fclose(dataFile);

    return tamanho / sizeof(Cliente); // Corrigido para retornar o número correto de clientes
}

// Função para editar um cliente pelo ID
void editarCliente() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    FILE *dataFile = fopen(DATA_FILE, "rb+");
    if (!dataFile) {
        printf("Erro ao abrir o arquivo de dados de clientes!\n");
        return;
    }

    int idEditar;
    printf("Digite o ID do cliente a ser editado: ");
    scanf("%d", &idEditar);
    getchar(); // Limpar o buffer

    Cliente cliente;
    bool clienteEncontrado = false;
    long posicao;

    // Percorre o arquivo de dados para encontrar o cliente
    while (fread(&cliente, sizeof(Cliente), 1, dataFile)) {
        if (cliente.id == idEditar) {
            clienteEncontrado = true;
            posicao = ftell(dataFile) - sizeof(Cliente);
            break;
        }
    }

    if (clienteEncontrado) {
        printf("Cliente encontrado! Selecione o campo que deseja editar:\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
        printf("+-------------------------------------------+\n");
        printf("|    [1] Nome     [3] Endereço  [5] RG      |\n");
        printf("|    [2] Telefone [4] CPF       [6] Email   |\n");
        printf("|    [7] Data Nascimento                   |\n");
        printf("+-------------------------------------------+\n\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        printf("Escolha uma opção (1-7): ");

        int opcao;
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer

        // Atualiza apenas o campo escolhido
        switch (opcao) {
        case 1:
            lerString(cliente.nome, MAX_NOME, "Digite o novo nome: ");
            break;
        case 2:
            lerString(cliente.telefone, MAX_TELEFONE, "Digite o novo telefone: ");
            break;
        case 3:
            lerString(cliente.endereco, MAX_ENDERECO, "Digite o novo endereço: ");
            break;
        case 4:
            lerString(cliente.cpf, MAX_CPF, "Digite o novo CPF: ");
            break;
        case 5:
            lerString(cliente.rg, MAX_RG, "Digite o novo RG: ");
            break;
        case 6:
            lerString(cliente.email, MAX_EMAIL, "Digite o novo email: ");
            break;
        case 7:
            lerString(cliente.dataNascimento, MAX_DATA, "Digite a nova data de nascimento (DD/MM/AAAA): "); // Novo campo
            break;
        default:
            printf("Opção inválida! Nenhum campo foi atualizado.\n");
            fclose(dataFile);
            return;
        }

        // Posiciona o ponteiro de volta para a posição do cliente e escreve os dados atualizados
        fseek(dataFile, posicao, SEEK_SET);
        fwrite(&cliente, sizeof(Cliente), 1, dataFile);
        SetConsoleTextAttribute(hConsole, 10);
        printf("\nDados do cliente atualizados com sucesso!\n");
        getchar();
        mostrarBoasVindas();
        SetConsoleTextAttribute(hConsole, 7); // Reseta para a cor padrão
    } else {
        printf("Cliente com ID %d não encontrado.\n", idEditar);
    }

    fclose(dataFile);
}

// Função para cadastrar um cliente


bool validarDataNascimento(const char *data) {
    // Verifica se a data está no formato DD/MM/AAAA
    if (strlen(data) != 10 || data[2] != '/' || data[5] != '/') {
        return false;
    }

    for (int i = 0; i < 10; i++) {
        if ((i == 2 || i == 5) && data[i] == '/') continue;
        if (!isdigit(data[i])) return false;
    }

    return true;
}

void cadastrarCliente(int *quantidade) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    FILE *dataFile = fopen("clientes.dat", "ab+");
    FILE *indexFile = fopen("indice.dat", "ab+");

    if (!dataFile || !indexFile) {
        printf("Erro ao abrir os arquivos de dados ou índice!\n");
        if (dataFile) fclose(dataFile);
        if (indexFile) fclose(indexFile);
        return;
    }

    char continuar = 'S';

    do {
        Cliente novoCliente;
        bool idExistente = false;

        printf("Digite o ID do cliente: ");
        scanf("%d", &novoCliente.id);
        getchar(); // Limpa o buffer após scanf

        // Verificar se o ID já existe (implementação do índice necessária)
        // ...

        // Lê os dados do cliente
        lerString(novoCliente.nome, MAX_NOME, "Digite o nome: ");
        lerString(novoCliente.telefone, MAX_TELEFONE, "Digite o telefone: ");
        lerString(novoCliente.endereco, MAX_ENDERECO, "Digite o endereço: ");
        lerString(novoCliente.cpf, MAX_CPF, "Digite o CPF: ");
        lerString(novoCliente.rg, MAX_RG, "Digite o RG: ");
        lerString(novoCliente.email, MAX_EMAIL, "Digite o email: ");

        // Lê a data de nascimento e valida
        do {
            lerString(novoCliente.dataNascimento, MAX_DATA, "Digite a data de nascimento (DD/MM/AAAA): ");
            if (!validarDataNascimento(novoCliente.dataNascimento)) {
                printf("Data inválida! Por favor, insira no formato DD/MM/AAAA.\n");
            }
        } while (!validarDataNascimento(novoCliente.dataNascimento));

        long posicao = ftell(dataFile);
        fwrite(&novoCliente, sizeof(Cliente), 1, dataFile);

        // Criar nova entrada de índice (implementação necessária)
        // ...

        fclose(dataFile);
        fclose(indexFile);

        (*quantidade)++;
        SetConsoleTextAttribute(hConsole, 10);
        printf("Cliente cadastrado com sucesso!\n\n");
        SetConsoleTextAttribute(hConsole, 7);

        // Pergunta se deseja continuar cadastrando
        printf("Deseja continuar cadastrando? (S/N): ");
        char buffer[10];
        fgets(buffer, sizeof(buffer), stdin);
        continuar = toupper(buffer[0]);

        // Limpa o buffer novamente para evitar problemas
        while (getchar() != '\n'); // Limpa o restante do buffer
        mostrarBoasVindas();
    } while (continuar == 'S');
}

// Função para listar clientes
void listarClientes() {
    int quantidade = contarClientes();
    if (quantidade == 0) {
        printf("Nenhum cliente cadastrado no sistema.\n");
        return;
    }

    FILE *dataFile = fopen(DATA_FILE, "rb");
    if (!dataFile) {
        printf("Erro ao abrir o arquivo de dados!\n");
        return;
    }

    Cliente cliente;
    char nome[MAX_NOME], cpf[MAX_CPF], rg[MAX_RG], telefone[MAX_TELEFONE], endereco[MAX_ENDERECO], email[MAX_EMAIL], dataNascimento[MAX_DATA];

    printf("+-------+---------------------------------+-----------------+--------------+-----------------+------------------------------+-------------------------+-----------------+\n");
    printf("| ID    | Nome                            | CPF             | RG           | TEL             | ENDEREÇO                     | EMAIL                   | DATA NASCIMENTO |\n");
    printf("+-------+---------------------------------+-----------------+--------------+-----------------+------------------------------+-------------------------+-----------------+\n");

    for (int i = 0; i < quantidade; i++) {
        fseek(dataFile, i * sizeof(Cliente), SEEK_SET);
        fread(&cliente, sizeof(Cliente), 1, dataFile);

        if (cliente.id > 0) { // Exibe apenas clientes válidos
            // Trunca os campos para garantir que caibam na largura da coluna
            truncarString(nome, cliente.nome, sizeof(nome));
            truncarString(cpf, cliente.cpf, sizeof(cpf));
            truncarString(rg, cliente.rg, sizeof(rg));
            truncarString(telefone, cliente.telefone, sizeof(telefone));
            truncarString(endereco, cliente.endereco, sizeof(endereco));
            truncarString(email, cliente.email, sizeof(email));
            truncarString(dataNascimento, cliente.dataNascimento, sizeof(dataNascimento));

            printf("| %-5d | %-31s | %-15s | %-12s | %-15s | %-28s | %-23s | %-15s |\n",
                   cliente.id, nome, cpf, rg, telefone, endereco, email, dataNascimento);
        }
    }

    printf("+-------+---------------------------------+-----------------+--------------+-----------------+------------------------------+-------------------------+-----------------+\n");
    getchar();
    getchar();
    getchar();
    fclose(dataFile);
}

void removerCliente(int *quantidade) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    FILE *dataFile = fopen(DATA_FILE, "rb+");
    if (!dataFile) {
        printf("Erro ao abrir o arquivo de dados de clientes!\n");
        return;
    }

    int idRemover;
    printf("Digite o ID do cliente a ser removido: ");
    scanf("%d", &idRemover);

    Cliente cliente;
    bool clienteEncontrado = false;

    // Percorre o arquivo de dados para encontrar o cliente
    while (fread(&cliente, sizeof(Cliente), 1, dataFile)) {
        if (cliente.id == idRemover) {
            clienteEncontrado = true;
            cliente.id = -1; // Marcar como removido

            long posicaoAtual = ftell(dataFile);
            if (posicaoAtual >= sizeof(Cliente)) {
                fseek(dataFile, -sizeof(Cliente), SEEK_CUR);
                fwrite(&cliente, sizeof(Cliente), 1, dataFile);
                SetConsoleTextAttribute(hConsole, 10);
                printf("Cliente com ID %d removido com sucesso!\n\n", idRemover);
                SetConsoleTextAttribute(hConsole, 7);
                (*quantidade)--;

            } else {
                printf("Erro: posição do arquivo inválida para a operação.\n");
            }
            break;
        }
    }

    if (!clienteEncontrado) {
        printf("Cliente com ID %d não encontrado.\n", idRemover);
    }

    fclose(dataFile);
}




