#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

#include <stdbool.h>

// Defini��es de tamanhos m�ximos para campos de usu�rio
#define FUNCIONARIO_DATA_FILE "usuarios.dat"  // Nome do arquivo de dados dos usu�rios
#define INDEX_FILE "usuarios.idx"  // Nome do arquivo de �ndice dos usu�rios
#define MAX 80                     // Tamanho m�ximo para strings
#define MAX_IDS 1000                // M�ximo de IDs permitidos

// Estrutura para representar um usu�rio
typedef struct {
    int id;                        // Identificador �nico do usu�rio
    char nome[MAX];                // Nome do usu�rio
    char telefone[MAX];            // Telefone do usu�rio
    char endereco[MAX];            // Endere�o do usu�rio
    char cpf[MAX];                 // CPF do usu�rio
    char rg[MAX];                  // RG do usu�rio
    char email[MAX];               // E-mail do usu�rio
} Usuario;

// Estrutura para entradas de �ndice
typedef struct {
    int id;                        // ID do usu�rio
    long posicao;                  // Posi��o do usu�rio no arquivo
} IndexEntry;

// Estrutura para gerenciar IDs
typedef struct {
    int ids[MAX_IDS];              // Array de IDs
    int count;                     // Contagem de IDs gerenciados
} IdManager;


// Declara��o de fun��es relacionadas a usu�rios
void lerString(char *buffer, int tamanho, const char *prompt);   // Fun��o para ler strings com seguran�a
void cadastrarUsuario(int *quantidade);                         // Fun��o para cadastrar um usu�rio
void editarUsuario();
void removerUsuario(int *quantidade);
void truncarString(char *destino, const char *origem, int largura);    // Fun��o para remover um usu�rio pelo ID
int contarUsuarios();                                           // Fun��o para contar o n�mero de usu�rios cadastrados

#endif // FUNCIONARIO_H
