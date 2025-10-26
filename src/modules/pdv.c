#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <locale.h>
#include <time.h>
#include "vendas.h"
#include "produto.h"
#include "link.h"
#include "carrinho.h" // Inclua o cabeçalho do carrinho

void definirCorPdv(int texto, int fundo) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, texto | (fundo << 4));
}

void mostrarBoasVindasPdv() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    system("cls");
    definirCorPdv(12, 0); // Azul escuro
    printf("+==  ::##  Bem-Vindo  ##::  ====  : Ver Beta 1.5.0 :==+\n");
    definirCorPdv(12, 0);
    printf("|  _   _            _   _ _____           _   _       |\n");
    definirCorPdv(6, 0);
    printf("| | | | | ___  _ __| |_(_)  ___| __ _   _| |_(_)      |\n");
    definirCorPdv(14, 0);
    printf("| | |_| |/ _ \\| '__| __| | |_ | '__| | | | __| |      |\n");
    definirCorPdv(10, 0);
    printf("| |  _  | (_) | |  | |_| |  _|| |  | |_| | |_| |      |\n");
    definirCorPdv(9, 0);
    printf("| |_| |_|\\___/|_|   \\__|_|_|  |_|   \\__,_|\\__|_|      |\n");
    definirCorPdv(12, 0);
    printf("+-----------------------------------------------------+\n");
    printf("| Data: %02d/%02d/%04d                                    |\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    printf("| Hora: %02d:%02d:%02d                                      |\n", tm.tm_hour, tm.tm_min, tm.tm_sec);
    printf("+---------------------:: Solutions Copyright 2024  :: +\n\n");
    definirCorPdv(7, 0); // Reseta a cor para o padrão (branco)
}

void mostrarMenuVendasPDV() {
    definirCorPdv(15, 0); // Define a cor do texto e fundo
    printf("\n");
    printf("+--- ##     ::PDV::     ## ------------------------------------+\n");
    printf("|    [1] Adicionar Produto ao Carrinho    [3] Finalizar Venda  |\n");
    printf("|    [2] Visualizar Carrinho              [4] Consultar Venda   |\n");
    printf("|    [5] Cancelar Venda                   [0] Sair...          |\n");
    printf("+--------------------------------------------------------------+\n");
    definirCorPdv(7, 0); // Reseta para a cor padrão
}

void gerenciarVendas() {
    int opcaoMenuVendas;
    Carrinho carrinho;
    inicializarCarrinho(&carrinho); // Inicializa o carrinho

    do {
        mostrarMenuVendasPDV(); // Chama a função que mostra o menu do PDV
        printf("Escolha uma opção: ");
        scanf("%d", &opcaoMenuVendas);
        getchar(); // Limpa o buffer

        switch (opcaoMenuVendas) {
        case 1: {
            char nomeOuId[50]; // Buffer para o nome ou ID do produto
            int porNome; // Variável para armazenar a escolha do usuário

            printf("Deseja adicionar o produto pelo:\n");
            printf("[1] Nome\n");
            printf("[2] ID\n");
            printf("Escolha uma opção: ");
            scanf("%d", &porNome);
            getchar(); // Limpa o buffer após a leitura do inteiro

            if (porNome == 1) {
                printf("Digite o nome do produto: ");
            } else if (porNome == 2) {
                printf("Digite o ID do produto: ");
            } else {
                printf("Opção inválida! Retornando ao menu.\n");
                break;
            }

            fgets(nomeOuId, sizeof(nomeOuId), stdin);
            nomeOuId[strcspn(nomeOuId, "\n")] = 0; // Remove o newline

            // Chama a função com os parâmetros apropriados
            if (adicionarProdutoAoCarrinho(&carrinho, nomeOuId, porNome == 1)) {
                printf("Produto adicionado ao carrinho!\n");
            } else {
                printf("Erro ao adicionar produto ao carrinho.\n");
            }
            break;
        }
        case 2:
            visualizarCarrinho(&carrinho); // Função para visualizar o carrinho
            break;
        case 3:
            realizarVendaComCarrinho(&carrinho); // Função para finalizar a venda
            inicializarCarrinho(&carrinho); // Reinicializa o carrinho após a venda
            break;
        case 4:
            consultarVendas(); // Função para consultar vendas
            break;
        case 5: {
            int idVenda;
            printf("Digite o ID da venda que deseja cancelar: ");
            if (scanf("%d", &idVenda) == 1) {
                cancelarVenda(idVenda); // Chama a função com o ID da venda
            } else {
                printf("Entrada inválida!\n");
            }
            break;
        }
        case 0:
            printf("Saindo do PDV...\n");
            break;
        default:
            printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcaoMenuVendas != 0);
}

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");
    mostrarBoasVindasPdv(); // Exibe a mensagem de boas-vindas
    gerenciarVendas(); // Inicia o gerenciamento de vendas

    return 0;
}