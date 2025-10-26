#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>
#include <stdbool.h>
#include "funcionario.h"
#include "main.h"
//macro para uso no listar usuario, nao faz referencia ao usuario.h
#define MAX_NOME       32
#define MAX_CPF        16 // Considerando o formato XXX.XXX.XXX-XX
#define MAX_RG         15 // Considerando o formato XX.XXX.XXX-X
#define MAX_TELEFONE   16 // Considerando o formato (XX) XXXXX-XXXX
#define MAX_ENDERECO   31
#define MAX_EMAIL      25



extern void definiCor();
extern void lerString();
extern void mostrarBoasVindas();
// Fun��o para contar usu�rios
int contarUsuarios() {
      FILE *dataFile = fopen(FUNCIONARIO_DATA_FILE, "rb");
    if (!dataFile) {
        return 0;
    }

    fseek(dataFile, 0, SEEK_END);
    long tamanho = ftell(dataFile);
    fclose(dataFile);

    return tamanho / sizeof(Usuario);
}

// Fun��o para editar um usu�rio pelo ID
void editarUsuario() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    FILE *dataFile = fopen(FUNCIONARIO_DATA_FILE, "rb+");
    if (!dataFile) {
        printf("Erro ao abrir o arquivo de dados de usu�rios!\n");
        return;
    }

    int idEditar;
    printf("Digite o ID do funcion�rio a ser editado: ");
    scanf("%d", &idEditar);
    getchar(); // Limpar o buffer

    Usuario usuario;
    bool usuarioEncontrado = false;
    long posicao;

    // Percorre o arquivo de dados para encontrar o funcion�rio
    while (fread(&usuario, sizeof(Usuario), 1, dataFile)) {
        if (usuario.id == idEditar) {
            usuarioEncontrado = true;
            posicao = ftell(dataFile) - sizeof(Usuario);
            break;
        }
    }

    if (usuarioEncontrado) {
        // Exibe os dados do funcion�rio em uma �nica linha, conforme o formato desejado
        printf("\nDados atuais do funcion�rio:\n");
        printf("+-------+---------------------------------+-----------------+--------------+-----------------+------------------------------+-------------------------+\n");
        printf("| ID    | Nome                            | CPF             | RG           | TEL             | ENDERE�O                     | EMAIL                   |\n");
        printf("+-------+---------------------------------+-----------------+--------------+-----------------+------------------------------+-------------------------+\n");
        printf("| %-5d | %-31s | %-15s | %-12s | %-15s | %-28s | %-23s |\n",
               usuario.id, usuario.nome, usuario.cpf, usuario.rg, usuario.telefone, usuario.endereco, usuario.email);
        printf("+-------+---------------------------------+-----------------+--------------+-----------------+------------------------------+-------------------------+\n\n");

        // Exibe o menu de edi��o
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
        printf("+---:: Editar  ::---------------------------+\n");
        printf("|    [1] Nome     [3] Endere�o  [5] RG      |\n");
        printf("|    [2] Telefone [4] CPF       [6] Email   |\n");
        printf("+-------------------------------------------+\n\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        printf("Escolha uma op��o: ");

        int opcao;
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer

        // Atualiza apenas o campo escolhido
        switch (opcao) {
        case 1:
            lerString(usuario.nome, MAX, "Digite o novo nome: ");
            break;
        case 2:
            lerString(usuario.telefone, MAX, "Digite o novo telefone: ");
            break;
        case 3:
            lerString(usuario.endereco, MAX, "Digite o novo endere�o: ");
            break;
        case 4:
            lerString(usuario.cpf, MAX, "Digite o novo CPF: ");
            break;
        case 5:
            lerString(usuario.rg, MAX, "Digite o novo RG: ");
            break;
        case 6:
            lerString(usuario.email, MAX, "Digite o novo email: ");
            break;
        default:
            printf("Op��o inv�lida! Nenhum campo foi atualizado.\n");
            fclose(dataFile);
            return;
        }

        // Posiciona o ponteiro para a posi��o do funcion�rio e escreve os dados atualizados
        fseek(dataFile, posicao, SEEK_SET);
        fwrite(&usuario, sizeof(Usuario), 1, dataFile);
        SetConsoleTextAttribute(hConsole, 10);
        printf("\nDados do funcion�rio atualizados com sucesso!\n");
        getchar();
        mostrarBoasVindas();
        SetConsoleTextAttribute(hConsole, 7); // Reseta para a cor padr�o
    } else {
        printf("Funcion�rio com ID %d n�o encontrado.\n", idEditar);
    }

    fclose(dataFile);
}




// Fun��o para cadastrar um usu�rio
void cadastrarUsuario(int *quantidade) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    FILE *dataFile, *indexFile;
    char continuar = 'S';

    do {
        dataFile = fopen(FUNCIONARIO_DATA_FILE, "ab+");
        indexFile = fopen(INDEX_FILE, "ab+");

        if (!dataFile || !indexFile) {
            printf("Erro ao abrir os arquivos de dados ou �ndice!\n");
            if (dataFile) fclose(dataFile);
            if (indexFile) fclose(indexFile);
            return;
        }

        Usuario novoUsuario;
        IndexEntry indice;
        bool idExistente = false;

        printf("Digite o ID do Funcionario: ");
        scanf("%d", &novoUsuario.id);
        getchar(); // Limpa o buffer

        // Verificar se o ID j� existe
        while (fread(&indice, sizeof(IndexEntry), 1, indexFile)) {
            if (indice.id == novoUsuario.id) {
                idExistente = true;
                break;
            }
        }

        if (idExistente) {
            printf("ID %d j� existe! Escolha outro ID.\n", novoUsuario.id);
            fclose(dataFile);
            fclose(indexFile);
            return;
        }

        // L� os dados do usu�rio
        lerString(novoUsuario.nome, MAX, "Digite o nome: ");
        lerString(novoUsuario.telefone, MAX, "Digite o telefone: ");
        lerString(novoUsuario.endereco, MAX, "Digite o endere�o: ");
        lerString(novoUsuario.cpf, MAX, "Digite o CPF: ");
        lerString(novoUsuario.rg, MAX, "Digite o RG: ");
        lerString(novoUsuario.email, MAX, "Digite o email: ");

        long posicao = ftell(dataFile);
        fwrite(&novoUsuario, sizeof(Usuario), 1, dataFile);

        // Criar nova entrada de �ndice
        IndexEntry indiceNovo = {novoUsuario.id, posicao};
        fwrite(&indiceNovo, sizeof(IndexEntry), 1, indexFile);

        fclose(dataFile);
        fclose(indexFile);

        (*quantidade)++;
        SetConsoleTextAttribute(hConsole, 10);
        printf("Usu�rio cadastrado com sucesso!\n\n");
         SetConsoleTextAttribute(hConsole, 7);
        // Pergunta se deseja continuar cadastrando
        printf("Deseja continuar cadastrando? (S/N): ");
        char buffer[10];
        fgets(buffer, sizeof(buffer), stdin);
        continuar = toupper(buffer[0]);
        mostrarBoasVindas();

    } while (continuar == 'S');
}
void truncarString(char *destino, const char *origem, int largura) {
    strncpy(destino, origem, largura - 1); // Copia at� largura-1 caracteres
    destino[largura - 1] = '\0'; // Adiciona o terminador nulo
}

// Fun��o para listar usu�rios
void listarUsuarios() {
    getchar();
    int quantidade = contarUsuarios();
    if (quantidade == 0) {
        printf("Nenhum usu�rio cadastrado no sistema.\n");
        return;
    }

    FILE *dataFile = fopen(FUNCIONARIO_DATA_FILE, "rb");
    if (!dataFile) {
        printf("Erro ao abrir o arquivo de dados!\n");
        return;
    }

    Usuario usuario;
    char nome[MAX_NOME], cpf[MAX_CPF], rg[MAX_RG], telefone[MAX_TELEFONE], endereco[MAX_ENDERECO], email[MAX_EMAIL];

    printf("+-------+---------------------------------+-----------------+--------------+-----------------+------------------------------+-------------------------+\n");
    printf("| ID    | Nome                            | CPF             | RG           | TEL             | ENDERE�O                     | EMAIL                   |\n");
    printf("+-------+---------------------------------+-----------------+--------------+-----------------+------------------------------+-------------------------+\n");

    for (int i = 0; i < quantidade; i++) {
        fseek(dataFile, i * sizeof(Usuario), SEEK_SET);
        fread(&usuario, sizeof(Usuario), 1, dataFile);

        if (usuario.id > 0) { // Exibe apenas usu�rios v�lidos
            // Trunca os campos para garantir que caibam na largura da coluna
            truncarString(nome, usuario.nome, sizeof(nome));
            truncarString(cpf, usuario.cpf, sizeof(cpf));
            truncarString(rg, usuario.rg, sizeof(rg));
            truncarString(telefone, usuario.telefone, sizeof(telefone));
            truncarString(endereco, usuario.endereco, sizeof(endereco));
            truncarString(email, usuario.email, sizeof(email));

            printf("| %-5d | %-31s | %-15s | %-12s | %-15s | %-28s | %-23s |\n",
                   usuario.id, nome, cpf, rg, telefone, endereco, email);
        }
    }

    printf("+-------+---------------------------------+-----------------+--------------+-----------------+------------------------------+-------------------------+\n");
    getchar();
    getchar();
    getchar();
    fclose(dataFile);

}


// Fun��o para remover um usu�rio pelo ID
void removerUsuario(int *quantidade) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    FILE *dataFile = fopen(FUNCIONARIO_DATA_FILE, "rb+");
    if (!dataFile) {
        printf("Erro ao abrir o arquivo de dados!\n");
        return;
    }

    int idRemover;
    printf("Digite o ID do usu�rio a ser removido: ");
    scanf("%d", &idRemover);

    Usuario usuario;
    bool usuarioEncontrado = false;

    // Percorre o arquivo de dados para encontrar o usu�rio
    while (fread(&usuario, sizeof(Usuario), 1, dataFile)) {
        if (usuario.id == idRemover) {
            usuarioEncontrado = true;
            usuario.id = -1; // Marcar como removido

            long posicaoAtual = ftell(dataFile);
            if (posicaoAtual >= sizeof(Usuario)) {
                fseek(dataFile, -sizeof(Usuario), SEEK_CUR);
                fwrite(&usuario, sizeof(Usuario), 1, dataFile);
                SetConsoleTextAttribute(hConsole, 10);
                printf("Usu�rio com ID %d removido com sucesso!\n\n", idRemover);
                SetConsoleTextAttribute(hConsole, 7);
                (*quantidade)--;

            } else {
                printf("Erro: posi��o do arquivo inv�lida para a opera��o.\n");
            }
            break;
        }
    }

    if (!usuarioEncontrado) {
        printf("Usu�rio com ID %d n�o encontrado.\n", idRemover);
    }

    fclose(dataFile);
}







