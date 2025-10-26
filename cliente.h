#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdbool.h>

#define DATA_FILE "clientes.dat" // Defina o nome do arquivo de dados
#define INDEX_FILE "clientes_index.dat" // Defina o nome do arquivo de �ndice

// Estrutura para representar um cliente
typedef struct {
    int id;
    char nome[32];
    char telefone[16];
    char endereco[31];
    char cpf[16];
    char rg[15];
    char email[25];
    char dataNascimento[11]; // Formato DD/MM/AAAA
} Cliente;

// Estrutura para entrada de �ndice
typedef struct {
    int id;
    long posicao; // Posi��o do cliente no arquivo
} IndexEntry;

// Fun��es para gerenciar clientes
void editarCliente();
void cadastrarCliente(int *quantidade);
void listarClientes();
void removerCliente(int *quantidade);
int contarClientes();
void truncarString(char *destino, const char *origem, size_t tamanho);

#endif // CLIENTE_H
