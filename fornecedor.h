#ifndef FORNECEDOR_H
#define FORNECEDOR_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FORNECEDOR_DATA_FILE "fornecedores.dat"
#define FORNECEDOR_INDEX_FILE "fornecedores.idx"

#define MAX_NOME_EMPRESA 50
#define MAX_NOME_FANTASIA 50
#define MAX_CNPJ 18
#define MAX_INSCRICAO_ESTADUAL 15
#define MAX_INSCRICAO_MUNICIPAL 15
#define MAX_ENDERECO 100
#define MAX_TELEFONE 16
#define MAX_EMAIL 50
#define MAX_ATIVIDADE 50
#define MAX_RESPONSAVEL 50

typedef struct {
    int id;
    char nome_empresa[MAX_NOME_EMPRESA];
    char nome_fantasia[MAX_NOME_FANTASIA];
    char cnpj[MAX_CNPJ];
    char inscricao_estadual[MAX_INSCRICAO_ESTADUAL];
    char inscricao_municipal[MAX_INSCRICAO_MUNICIPAL];
    char endereco[MAX_ENDERECO];
    char telefone[MAX_TELEFONE];
    char email[MAX_EMAIL];
    char atividade_principal[MAX_ATIVIDADE];
    char responsavel_setor[MAX_RESPONSAVEL];
} Fornecedor;

typedef struct {
    int id;
    long posicao;
} IndexEntryFornecedor;

void cadastrarFornecedor(int *quantidade);
void listarFornecedores();
void editarFornecedor();
void removerFornecedor(int *quantidade);
int contarFornecedores();

#endif // FORNECEDOR_H
