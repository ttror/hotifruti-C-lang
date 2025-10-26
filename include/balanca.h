#ifndef BALANCA_H
#define BALANCA_H

#include <stdbool.h>
#include "modules/produto.h"

// Funções do módulo Balança

/**
 * @brief Testa o acesso ao arquivo de dados dos produtos
 */
void testarAcessoAoArquivo();

/**
 * @brief Busca um produto por ID no banco de dados
 * @param id ID do produto a ser buscado
 * @param produto Ponteiro para a estrutura onde o produto será armazenado
 * @return true se o produto foi encontrado, false caso contrário
 */
bool buscarProdutoPorId(int id, Produto *produto);

/**
 * @brief Salva o recibo da pesagem em arquivo
 * @param peso Peso do produto em kg
 * @param nomeProduto Nome do produto
 * @param precoPorKilo Preço por kg do produto
 * @param codigoBarras Código de barras do produto
 */
void salvarRecibo(float peso, const char *nomeProduto, float precoPorKilo, const char *codigoBarras);

/**
 * @brief Menu para buscar produto na balança
 * Permite ao operador digitar o ID do produto e registrar o peso
 */
void menuBuscarProdutoBalanca();

#endif // BALANCA_H

