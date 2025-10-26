#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <ctype.h>
#include <windows.h>
#include <locale.h>
#include <time.h>
#include "financeiro.h"
#include "funcionario.h"
#include "produto.h"
#include "fornecedor.h"
#include "vendas.h"
#include "login.h"
#include "carrinho.h"
#include "login.h"
#include "link.h"

extern void menuPrincipalContasPagar();
extern void menuDespesas();
extern void menuRelatorios();
extern void mostrarMenuRelatorio();
extern void finalizarCurses();
extern void inicializarCurses();
extern void exibirMenuPrincipalLogin();
void mostrarBoasVindas();
void menuCadastros();
void gerenciarVendas();
int quantidadeUsuarios = 0; // Inicializa a variável quantidadeUsuarios
int quantidadeProdutos = 0; // Inicializa a variável quantidadeProdutos
int quantidadeFornecedores = 0; // Inicializa a variável quantidadeFornecedores

void definirCor(int texto, int fundo) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, texto | (fundo << 4));
}

void mostrarBoasVindas() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    system("cls");
    definirCor(12, 0); // Azul escuro
    printf("+==  ::##  Bem-Vindo  ##::  ====  : Ver Beta 1.5.0 :==+\n");
    definirCor(12, 0);
    printf("|  _   _            _   _ _____           _   _       |\n");
    definirCor(6, 0);
    printf("| | | | | ___  _ __| |_(_)  ___| __ _   _| |_(_)      |\n");
    definirCor(14, 0);
    printf("| | |_| |/ _ \\| '__| __| | |_ | '__| | | | __| |      |\n");
    definirCor(10, 0);
    printf("| |  _  | (_) | |  | |_| |  _|| |  | |_| | |_| |      |\n");
    definirCor(9, 0);
    printf("| |_| |_|\\___/|_|   \\__|_|_|  |_|   \\__,_|\\__|_|      |\n");
    definirCor(12, 0);
    printf("+-----------------------------------------------------+\n");
    printf("| Data: %02d/%02d/%04d                                    |\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    printf("| Hora: %02d:%02d:%02d                                      |\n", tm.tm_hour, tm.tm_min, tm.tm_sec);
    printf("+---------------------:: Solutions Copyright 2024  :: +\n\n");
    definirCor(7, 0); // Reseta a cor para o padrão (branco)
}

void mostrarMenuPrincipal() {
    definirCor(15, 0);
    printf("+--- ## MENU ADM ## ---------------------------------------------------+\n");
    printf("|    [1] Gerenciar Usuários          [4] Abrir PDV                     |\n");
    printf("|    [2] Gerenciar Estoque           [5] Financeiro                    |\n");
    printf("|    [3] Campanhas                   [0] Sair.                         |\n");
    printf("+----------------------------------------------------------------------+\n");
    definirCor(7, 0);
}

void mostrarMenuFinanceiro() {
    definirCor(15, 0);
    printf("+--- ## Gerenciar Financeiro ## --------------------------------+\n");
    printf("|    [1] Gerenciar Despesas Loja     [0] Voltar                 |\n");
    printf("|    [2] Gerenciar Relatorios                                   |\n");
    printf("|    [3] Contas a Pagar/Receber                                 |\n");
    printf("+---------------------------------------------------------------+\n");
    definirCor(7, 0);
}

void mostrarMenuRelatorio() {
    definirCor(15, 0);
    printf("+--- ## Gerenciar Relatorio ## ---------------------------------+\n");
    printf("|    [1] Caixa                      [3] Despesas                |\n");
    printf("|    [2] Lucros/perdas              [4] Graficos                |\n");
    printf("|    [0] Voltar                                                 |\n");
    printf("+---------------------------------------------------------------+\n");
    definirCor(7, 0);
}

void mostrarMenuCadastros() {
    definirCor(15, 0);
    printf("+--- ## Cadastramento de Usuarios ## -----------+\n");
    printf("|    [1] Funcionario      [3] Fornecedor        |\n");
    printf("|    [2] Cliente          [0] Voltar            |\n");
    printf("+-----------------------------------------------+\n");
    definirCor(7, 0);
}

void mostrarMenuFuncionarios() {
    definirCor(15, 0);
    printf("+--- ## Gerenciamento de Usuários ## ---------------------------+\n");
    printf("|    [1] Cadastrar Funcionario       [3] Remover Funcionari     |\n");
    printf("|    [2] Listar Funcionario          [4] Editar Funcionario     |\n");
    printf("|    [0] Voltar                                                 |\n");
    printf("+---------------------------------------------------------------+\n");
    definirCor(7, 0);
}

void mostrarMenuProdutos() {
    definirCor(15, 0);
    printf("+--- ## Gerenciamento de Produtos ##  -------------------------+\n");
    printf("|    [1] Cadastrar Produto        [3] Remover Produto          |\n");
    printf("|    [2] Listar Produtos          [4] Editar Produto           |\n");
    printf("|    [0] Voltar                                                |\n");
    printf("+--------------------------------------------------------------+\n");
    definirCor(7, 0);
}



void mostrarMenuClientes() {
    definirCor(15, 0);
    printf("+--- ## Gerenciamento de Fornecedores ##  ---------------------+\n");
    printf("|    [1] Cadastrar Cliente            [3] Remover Cliente      |\n");
    printf("|    [2] Listar Cliente               [4] Editar Cliente       |\n");
    printf("|    [0] Voltar                                                |\n");
    printf("+--------------------------------------------------------------+\n");
    definirCor(7, 0);

}


void mostrarMenuFornecedores() {
    definirCor(15, 0);
    printf("+--- ## Gerenciamento de Fornecedores ##  ---------------------+\n");
    printf("|    [1] Cadastrar Fornecedor      [3] Remover Fornecedor      |\n");
    printf("|    [2] Listar Fornecedores       [4] Editar Fornecedor       |\n");
    printf("|    [0] Voltar                                                |\n");
    printf("+--------------------------------------------------------------+\n");
    definirCor(7, 0);

}

void mostrarMenuVendas() {
    definirCor(15, 0);
    printf("\n");
    printf("+--- ##     ::PDV::     ## ------------------------------------+\n");
    printf("|    [1] Adicionar Produto ao Carrinho    [3] Finalizar Venda  |\n");
    printf("|    [2] Visualizar Carrinho              [4] Consultar Venda  |\n");
    printf("|    [5] Cancelar Venda                   [0] Sair...          |\n");
    printf("+--------------------------------------------------------------+\n");
    definirCor(7, 0);

}






void menuAdm() {
    int opcaoPrincipal;

    do {
        mostrarBoasVindas();
        mostrarMenuPrincipal(); // Exibe o menu principal

        printf("\nEscolha uma opção: ");
        if (scanf("%d", &opcaoPrincipal) != 1) {
            printf("Entrada inválida! Tente novamente.\n");
            while (getchar() != '\n'); // Limpa o buffer de entrada
            continue;
        }

        switch (opcaoPrincipal) {
        case 1:
            mostrarBoasVindas();
            menuCadastros();  // Chama o menu de cadastros
            break;
        case 2: {
            int opcaoGerenciamentoProdutos;
            mostrarBoasVindas();
            do {
                mostrarMenuProdutos(); // Exibe menu de gerenciamento de produtos
                printf("\nEscolha uma opção: ");
                if (scanf("%d", &opcaoGerenciamentoProdutos) != 1) {
                    printf("Entrada inválida! Tente novamente.\n");
                    while (getchar() != '\n'); // Limpa o buffer
                    continue;
                }

                switch (opcaoGerenciamentoProdutos) {
                case 1:
                    // Chama a função para cadastrar produto
                    // O fluxo retorna aqui se o usuário não escolher sair
                    cadastrarProduto(&quantidadeProdutos);
                    break;

                case 2:
                    mostrarBoasVindas();
                    listarProdutos();  // Chama função para listar produtos
                    break;

                case 3:
                    removerProduto(&quantidadeProdutos);  // Chama função para remover produto
                    break;

                case 4:
                    // Solicita o ID do produto e a quantidade vendida ao usuário
                    printf("Digite o ID do produto que deseja atualizar: ");
                    int idProduto;
                    scanf("%d", &idProduto);  // Lê o ID do produto

                    printf("Digite a quantidade vendida: ");
                    int quantidadeVendida;
                    scanf("%d", &quantidadeVendida);  // Lê a quantidade vendida

                    // Chama a função para atualizar o produto com os parâmetros fornecidos
                    atualizarProduto(idProduto, quantidadeVendida);
                    break;

                case 0:
                    printf("Voltando ao menu principal...\n");
                    break;

                default:
                    printf("Opção inválida! Tente novamente.\n");
                }
            } while (opcaoGerenciamentoProdutos != 0);  // Continua até a opção 0 ser escolhida
            break;
        } // Fechar o bloco do case 2.

        case 3: {
            int opcaoGerenciamentoClientes;
            mostrarBoasVindas();
            // ... (código do case 3)
            break;
        } // Fechar o bloco do case 3.

        case 4:
            gerenciarVendas();  // Chama a função para gerenciar vendas
            break;

        case 5: {
            int opcaoFinanceiro;
            do {
                mostrarBoasVindas();
                mostrarMenuFinanceiro(); // Exibe o menu financeiro
                printf("\nEscolha uma opção: ");
                if (scanf("%d", &opcaoFinanceiro) != 1) {
                    printf("Entrada inválida! Tente novamente.\n");
                    while (getchar() != '\n'); // Limpa o buffer de entrada
                    continue;
                }

                switch (opcaoFinanceiro) {
                case 1:
                    menuDespesas();  // Chama o menu de despesas
                    break;
                case 2:
                    menuRelatorios();  // Chama o menu de relatórios
                    break;
                case 3:
                    menuPrincipalContasPagar();  // Chama o menu de contas a pagar
                    break;
                case 0:
                    printf("Voltando ao menu principal...\n");
                    break;  // O loop irá parar naturalmente
                default:
                    printf("Opção inválida! Tente novamente.\n");
                }
            } while (opcaoFinanceiro != 0); // Continua até que a opção 3 seja escolhida
            break;  // Sai do case 5
        }

        case 8:
            exibirMenuPrincipalLogin();  // Retorna ao menu de login
            break;

        default:
            printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcaoPrincipal != 0);  // Ajuste a condição aqui se necessário
}


void gerenciarVendas() {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    mostrarBoasVindas();
    Carrinho carrinho;
    inicializarCarrinho(&carrinho);

    int opcaoMenuVendas;
    do {
        mostrarMenuVendas();
        printf("\nEscolha uma opção: ");
        if (scanf("%d", &opcaoMenuVendas) != 1) {
            printf("Entrada inválida! Tente novamente.\n");
            while (getchar() != '\n'); // Limpa o buffer
            continue;
        }

        switch (opcaoMenuVendas) {
        case 1: {
            char nomeOuId[50];
            int porNome;
            char continuarAdicionando = 'S';  // Variável para controlar o loop de adição de produtos

            do {
                do {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
                    printf("\n");
                    printf("+--:: Adicione ao Carrinho ::--------------------------+\n");
                    printf("|    [1] Nome do Produto     [2] ID do Produto        |\n");
                    printf("|    [3] Código de Barras    [0] Voltar                |\n");
                    printf("+------------------------------------------------------+\n\n");
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    if (scanf(" %d", &porNome) != 1 || (porNome < 0 || porNome > 3)) {
                        printf("Entrada inválida! Digite 1 para nome, 2 para ID ou 3 para Código de Barras.\n");
                        while (getchar() != '\n'); // Limpa o buffer
                    } else {
                        break;
                    }
                } while (1);

                // Limpar o buffer antes de ler a string
                while (getchar() != '\n'); // Limpa o buffer

                if (porNome == 1) {
                    printf("Digite o nome do produto: ");
                } else if (porNome == 2) {
                    printf("Digite o ID do produto: ");
                } else if (porNome == 3) {
                    printf("Digite o código de barras do produto: ");
                } else {
                    break; // Volta ao menu se a opção for 0
                }

                fgets(nomeOuId, sizeof(nomeOuId), stdin);
                nomeOuId[strcspn(nomeOuId, "\n")] = 0;  // Remove o newline

                if (adicionarProdutoAoCarrinho(&carrinho, nomeOuId, porNome == 1)) {
                    definirCor(10, 0);
                    printf("Produto adicionado ao carrinho!\n\n");
                    definirCor(7, 0);
                } else {
                    printf("Erro ao adicionar produto ao carrinho.\n");
                }

                // Pergunta ao usuário se ele deseja continuar adicionando
                printf("Deseja adicionar outro produto? (s/n): ");
                scanf(" %c", &continuarAdicionando);  // O espaço antes de %c é necessário para ignorar o newline
                continuarAdicionando = toupper(continuarAdicionando);  // Convertendo a resposta para maiúscula

            } while (continuarAdicionando == 'S');  // Repete enquanto o usuário responder 'S'
            break;
        }
        case 2:
            visualizarCarrinho(&carrinho);
            break;
        case 3:
            realizarVendaComCarrinho(&carrinho);
            inicializarCarrinho(&carrinho);
            break;
        case 4:
            mostrarBoasVindas();
            consultarVendas();
            break;
        case 5: {
            int idVenda;
            printf("Digite o ID da venda que deseja cancelar: ");
            if (scanf("%d", &idVenda) == 1) {
                cancelarVenda(idVenda);
            } else {
                printf("Entrada inválida!\n");
                while (getchar() != '\n'); // Limpa o buffer
            }
            break;
        }
        case 6:
            exibirMenuPrincipalLogin();
            break;
        default:
            printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcaoMenuVendas != 0);
}

void menuCadastros() {
    int opcaoCadastro;

    do {
        mostrarBoasVindas();
        mostrarMenuCadastros();
        printf("\nEscolha uma opção: ");
        if (scanf("%d", &opcaoCadastro) != 1) {
            printf("Entrada inválida! Tente novamente.\n");
            while (getchar() != '\n'); // Limpa o buffer de entrada
            continue;
        }

        switch (opcaoCadastro) {
        case 1: // Gerenciar Funcionários
        {
            int opcaoFuncionario;
            do {
                mostrarBoasVindas();
                mostrarMenuFuncionarios(); // Crie esta função para mostrar o menu de funcionários
                printf("\nEscolha uma opção: ");
                scanf("%d", &opcaoFuncionario);

                switch (opcaoFuncionario) {
                case 1:
                    cadastrarUsuario(&quantidadeUsuarios);
                    break;
                case 2:
                    listarUsuarios();
                    break;
                case 3:
                    removerUsuario(&quantidadeUsuarios);
                    break;
                case 4:
                    editarUsuario();
                    break;
                case 0:
                    printf("Voltando ao menu de cadastros...\n");
                    break;
                default:
                    printf("Opção inválida! Tente novamente.\n");
                }
            } while (opcaoFuncionario != 0);
            break;
        }
        case 2: // Gerenciar Clientes
        {
            int opcaoCliente;
            do {
                mostrarBoasVindas();
                mostrarMenuClientes(); // Crie esta função para mostrar o menu de clientes
                printf("\nEscolha uma opção: ");
                scanf("%d", &opcaoCliente);

                switch (opcaoCliente) {
                case 1:
                    cadastrarCliente(&quantidadeUsuarios); // Ajuste a variável se necessário
                    break;
                case 2:
                    listarClientes();
                    break;
                case 3:
                    removerCliente(&quantidadeUsuarios);
                    break;
                case 4:
                    editarCliente();
                    break;
                case 0:
                    printf("Voltando ao menu de cadastros...\n");
                    break;
                default:
                    printf("Opção inválida! Tente novamente.\n");
                }
            } while (opcaoCliente != 0);
            break;
        }
        case 3: // Gerenciar Fornecedores
        {
            int opcaoFornecedor;
            do {
                mostrarBoasVindas();
                mostrarMenuFornecedores(); // Crie esta função para mostrar o menu de fornecedores
                printf("\nEscolha uma opção: ");
                scanf("%d", &opcaoFornecedor);

                switch (opcaoFornecedor) {
                case 1:
                    cadastrarFornecedor(&quantidadeFornecedores);
                    break;
                case 2:
                    listarFornecedores();
                    break;
                case 3:
                    removerFornecedor(&quantidadeFornecedores);
                    break;
                case 4:
                    editarFornecedor();
                    break;
                case 0:
                    printf("Voltando ao menu de cadastros...\n");
                    break;
                default:
                    printf("Opção inválida! Tente novamente.\n");
                }
            } while (opcaoFornecedor != 0);
            break;
        }
        case 0:
            printf("Voltando ao menu principal...\n");
            break;
        default:
            printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcaoCadastro != 0);
}

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");
    inicializarCurses();
    exibirMenuPrincipalLogin();
    finalizarCurses();

    return 0;
}
