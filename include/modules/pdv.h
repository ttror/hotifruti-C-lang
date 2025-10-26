#ifndef PDV_H
#define PDV_H

// Funções do módulo PDV (Ponto de Venda)

/**
 * @brief Define a cor do texto e fundo no console
 * @param texto Cor do texto
 * @param fundo Cor do fundo
 */
void definirCorPdv(int texto, int fundo);

/**
 * @brief Exibe a tela de boas-vindas do PDV
 */
void mostrarBoasVindasPdv();

/**
 * @brief Exibe o menu principal do PDV
 */
void mostrarMenuVendasPDV();

/**
 * @brief Gerencia as operações de vendas do PDV
 * Função principal que controla o fluxo de vendas
 */
void gerenciarVendas();

#endif // PDV_H

