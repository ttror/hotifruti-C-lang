#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

#include <stdbool.h>

// Definições de tamanhos máximos para campos de usuário
#define FUNCIONARIO_DATA_FILE "usuarios.dat"  // Nome do arquivo de dados dos usuários
#define INDEX_FILE "usuarios.idx"  // Nome do arquivo de índice dos usuários
#define MAX 80                     // Tamanho máximo para strings
#define MAX_IDS 1000                // Máximo de IDs permitidos

// Estrutura para representar um usuário
typedef struct {
    int id;                        // Identificador único do usuário
    char nome[MAX];                // Nome do usuário
    char telefone[MAX];            // Telefone do usuário
    char endereco[MAX];            // Endereço do usuário
    char cpf[MAX];                 // CPF do usuário
    char rg[MAX];                  // RG do usuário
    char email[MAX];               // E-mail do usuário
} Usuario;

// Estrutura para entradas de índice
typedef struct {
    int id;                        // ID do usuário
    long posicao;                  // Posição do usuário no arquivo
} IndexEntry;

// Estrutura para gerenciar IDs
typedef struct {
    int ids[MAX_IDS];              // Array de IDs
    int count;                     // Contagem de IDs gerenciados
} IdManager;


// Declaração de funções relacionadas a usuários
void lerString(char *buffer, int tamanho, const char *prompt);   // Função para ler strings com segurança
void cadastrarUsuario(int *quantidade);                         // Função para cadastrar um usuário
void editarUsuario();
void removerUsuario(int *quantidade);
void truncarString(char *destino, const char *origem, int largura);    // Função para remover um usuário pelo ID
int contarUsuarios();                                           // Função para contar o número de usuários cadastrados

#endif // FUNCIONARIO_H
