#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <time.h>
#include <math.h>
#include "financeiro.h"
#include "carrinho.h"
#include "produto.h"
#include "vendas.h"
#include "main.h"
#include "link.h"

#define MAX_ITENS_CARRINHO 1000


extern void mostrarBoasVindas();
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Consome até a nova linha ou fim de arquivo
}

void inicializarCarrinho(Carrinho *carrinho) {
    carrinho->itens = malloc(10 * sizeof(ItemCarrinho));
    carrinho->totalItens = 0;
    carrinho->capacidade = 10;
}

bool buscarProdutoPorCodigoBarras(const char *codigoBarras, Produto *produto) {
    FILE *dataFile = fopen(DATA_FILE_PRODUTO, "rb");
    if (!dataFile) {
        printf("Erro ao abrir o arquivo de dados dos produtos!\n");
        return false;
    }

    Produto tempProduto;
    while (fread(&tempProduto, sizeof(Produto), 1, dataFile)) {
        if (strcmp(tempProduto.codigoBarras, codigoBarras) == 0) {
            *produto = tempProduto;
            fclose(dataFile);
            return true; // Produto encontrado
        }
    }

    fclose(dataFile);
    return false; // Produto não encontrado
}

bool buscarProdutoPorNome(const char *nome, Produto *produto) {
    FILE *dataFile = fopen(DATA_FILE_PRODUTO, "rb");
    if (!dataFile) {
        printf("Erro ao abrir o arquivo de dados dos produtos!\n");
        return false;
    }

    Produto tempProduto;
    while (fread(&tempProduto, sizeof(Produto), 1, dataFile)) {
        if (tempProduto.id > 0 && strcasecmp(tempProduto.nome, nome) == 0) {
            *produto = tempProduto;
            fclose(dataFile);
            return true;  // Produto encontrado
        }
    }

    fclose(dataFile);
    return false;  // Produto não encontrado
}

bool buscarProdutoPorId(int id, Produto *produto) {
    FILE *dataFile = fopen(DATA_FILE_PRODUTO, "rb");
    if (!dataFile) {
        printf("Erro ao abrir o arquivo de dados dos produtos!\n");
        return false;
    }

    Produto tempProduto;
    while (fread(&tempProduto, sizeof(Produto), 1, dataFile)) {
        if (tempProduto.id == id) {
            *produto = tempProduto;
            fclose(dataFile);
            return true;  // Produto encontrado
        }
    }

    fclose(dataFile);
    return false;  // Produto não encontrado
}

bool adicionarProdutoAoCarrinho(Carrinho *carrinho, const char *nomeOuId, bool porNome) {
    if (carrinho->totalItens >= MAX_ITENS_CARRINHO) {
        printf("Carrinho cheio! Não é possível adicionar mais produtos.\n");
        return false;
    }

    Produto produto;
    bool encontrado = false;
    char codigoBarrasLimpo[20];  // Array para armazenar o código de barras sem quebras de linha

    // Se não for busca por nome, trata o código de barras
    if (!porNome) {
        // Copia o código de barras recebido e limpa as quebras de linha
        strncpy(codigoBarrasLimpo, nomeOuId, sizeof(codigoBarrasLimpo) - 1);
        codigoBarrasLimpo[sizeof(codigoBarrasLimpo) - 1] = '\0';  // Garante o fim da string

        // Remove quebras de linha
        for (int i = 0; i < strlen(codigoBarrasLimpo); i++) {
            if (codigoBarrasLimpo[i] == '\n' || codigoBarrasLimpo[i] == '\r') {
                codigoBarrasLimpo[i] = '\0';  // Substitui a quebra de linha por fim de string
                break;
            }
        }

        // Busca o produto usando o código de barras limpo
        encontrado = buscarProdutoPorCodigoBarras(codigoBarrasLimpo, &produto);
    } else {
        // Busca o produto pelo nome
        encontrado = buscarProdutoPorNome(nomeOuId, &produto);
    }

    if (!encontrado) {
        printf("Produto não encontrado!\n");
        return false;
    }

    // Exibe informações do produto
    printf("+---------------------------------+-----------------------+-----------------------+\n");
    printf("| Nome do Produto                 | Quantidade Disponível | Preço de Venda        |\n");
    printf("+---------------------------------+-----------------------+-----------------------+\n");
    printf("| %-31s | %-18d    | R$%-19.2f |\n", produto.nome, produto.quantidade, produto.precoVenda);
    printf("+---------------------------------+-----------------------+-----------------------+\n");

    if (produto.vendidoAGranela) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        float peso;
        char input[20]; // Array para armazenar a entrada do usuário
        SetConsoleTextAttribute(hConsole, 12);
        printf("Digite o peso (em KG) a ser adicionado ao carrinho (0,000 para gramas): ");
        SetConsoleTextAttribute(hConsole, 7);
        fgets(input, sizeof(input), stdin); // Ler a entrada do usuário

        // Verificar se a entrada pode ser convertida para float
        if (sscanf(input, "%f", &peso) != 1 || peso <= 0) {
            printf("Peso inválido! O peso deve ser maior que zero.\n");
            return false;
        }

        // Verificar se o peso desejado excede a quantidade disponível
        if (peso > produto.quantidade) {
            printf("Peso solicitado maior que a quantidade disponível!\n");
            return false;
        }

        // Verifica se o produto já está no carrinho
        for (int i = 0; i < carrinho->totalItens; i++) {
            if (carrinho->itens[i].produto.id == produto.id) {
                // Atualiza a quantidade e calcula o preço total se o produto já estiver no carrinho
                if (carrinho->itens[i].quantidade + peso > produto.quantidade) {
                    printf("Quantidade total no carrinho excede a disponível!\n");
                    return false;
                }
                carrinho->itens[i].quantidade += peso; // Atualiza o peso
                // Atualiza o preço total com base no peso
                carrinho->itens[i].precoTotal = carrinho->itens[i].quantidade * produto.precoPorKilo; // Alteração aqui
                printf("Peso e preço total atualizados no carrinho.\n");
                visualizarCarrinho(carrinho);
                return true;
            }
        }

        // Adiciona um novo item ao carrinho
        carrinho->itens[carrinho->totalItens].produto = produto;
        carrinho->itens[carrinho->totalItens].quantidade = peso; // Armazena o peso
        // Calcula o preço total com base no peso
        carrinho->itens[carrinho->totalItens].precoTotal = peso * produto.precoPorKilo;
        carrinho->totalItens++;
    } else {
        // Lógica para produtos não vendidos a granel (quantidade em unidades)
        int quantidadeVenda;
        printf("Digite a quantidade a ser adicionada ao carrinho: ");
        if (scanf("%d", &quantidadeVenda) != 1 || quantidadeVenda <= 0) {
            printf("Quantidade inválida!\n");
            return false;
        }
        getchar(); // Consome o newline

        // Verifica se a quantidade desejada excede a disponível
        if (quantidadeVenda > produto.quantidade) {
            printf("Quantidade solicitada maior que a disponível!\n");
            return false;
        }

        // Verifica se o produto já está no carrinho
        for (int i = 0; i < carrinho->totalItens; i++) {
            if (carrinho->itens[i].produto.id == produto.id) {
                // Atualiza a quantidade e calcula o preço total se o produto já estiver no carrinho
                if (carrinho->itens[i].quantidade + quantidadeVenda > produto.quantidade) {
                    printf("Quantidade total no carrinho excede a disponível!\n");
                    return false;
                }
                carrinho->itens[i].quantidade += quantidadeVenda; // Atualiza a quantidade
                // Atualiza o preço total com base na quantidade
                carrinho->itens[i].precoTotal = carrinho->itens[i].quantidade * produto.precoVenda;
                printf("Quantidade e preço total atualizados no carrinho.\n");
                visualizarCarrinho(carrinho);
                return true;
            }
        }

        // Adiciona um novo item ao carrinho
        carrinho->itens[carrinho->totalItens].produto = produto;
        carrinho->itens[carrinho->totalItens].quantidade = quantidadeVenda; // Armazena a quantidade
        // Calcula o preço total com base na quantidade
        carrinho->itens[carrinho->totalItens].precoTotal = quantidadeVenda * produto.precoVenda;
        carrinho->totalItens++;
    }

    visualizarCarrinho(carrinho);
    return true;
}

void visualizarCarrinho(const Carrinho *carrinho) {
    if (carrinho->totalItens == 0) {
        printf("Carrinho vazio!\n");
        return;
    }

    printf("\n=== Cupom Fiscal ===\n");
    printf("+-------+-----------------------------+------------+------------------+------------------+\n");
    printf("| ID    | Nome                        | Quantidade | Preço Unitário   | Preço Total      |\n");
    printf("+-------+-----------------------------+------------+------------------+------------------+\n");

    float valorTotal = 0.0f;
    for (int i = 0; i < carrinho->totalItens; i++) {
        Produto produto = carrinho->itens[i].produto;
        float quantidade = carrinho->itens[i].quantidade;
        float precoTotal = quantidade * produto.precoVenda;
        valorTotal += precoTotal;

        printf("| %-5d | %-27s | %-10.3f | R$%-14.2f | R$%-14.2f |\n",
               produto.id, produto.nome, (float)quantidade, produto.precoVenda, precoTotal);
    }
    printf("+-------+-----------------------------+------------+------------------+------------------+\n");
    printf("                                                   |  Valor Total : R$%.2f                \n", valorTotal);
    printf("                                                   +-------------------------------------+\n");
}



void realizarVendaComCarrinho(Carrinho *carrinho) {
    if (carrinho->totalItens == 0) {
        printf("Carrinho vazio! Adicione produtos antes de realizar a venda.\n");
        return;
    }

    FILE *dataFile = fopen(DATA_FILE_PRODUTO, "r+b");
    FILE *vendaFile = fopen(DATA_FILE_VENDA, "ab");
    bool erro = false;
    int estado = 0; // Variável de controle para identificar o erro

    // Verifica abertura dos arquivos
    if (!dataFile) {
        estado = 1; // Erro ao abrir arquivo de produtos
    } else if (!vendaFile) {
        estado = 2; // Erro ao abrir arquivo de vendas
    }

    switch (estado) {
    case 1:
        printf("Erro ao abrir o arquivo de dados dos produtos!\n");
        return; // Sai da função se o arquivo de produtos não foi aberto
    case 2:
        printf("Erro ao abrir o arquivo de vendas!\n");
        fclose(dataFile); // Fecha o arquivo de produtos que foi aberto com sucesso
        return; // Sai da função se o arquivo de vendas não foi aberto
    default:
        break; // Continua se ambos os arquivos foram abertos com sucesso
    }

    float valorTotalVenda = 0.0f;

    // Processa os itens do carrinho
    for (int i = 0; i < carrinho->totalItens; i++) {
        Produto produto = carrinho->itens[i].produto;
        float quantidadeVendida = carrinho->itens[i].quantidade;

        // Verifica se há estoque suficiente para o produto
        if (produto.quantidade < quantidadeVendida) {
            printf("Estoque insuficiente para o produto: %s\n", produto.nome);
            continue; // Ignora este produto e passa para o próximo item
        }

        // Debita a quantidade do produto
        produto.quantidade -= quantidadeVendida;

        // Atualiza o produto no arquivo
        // Percorre os produtos no arquivo até encontrar o produto correto
        fseek(dataFile, 0, SEEK_SET);
        Produto tempProduto;
        bool produtoEncontrado = false;

        while (fread(&tempProduto, sizeof(Produto), 1, dataFile) == 1) {
            if (tempProduto.id == produto.id) {
                // Encontrou o produto, atualiza a quantidade
                fseek(dataFile, -sizeof(Produto), SEEK_CUR); // Volta para o início do produto
                if (fwrite(&produto, sizeof(Produto), 1, dataFile) != 1) {
                    estado = 3; // Erro ao atualizar o produto no arquivo
                    break;
                }
                produtoEncontrado = true;
                break;
            }
        }

        if (!produtoEncontrado) {
            estado = 5; // Produto não encontrado no arquivo
            break;
        }

        // Registra a venda no arquivo de vendas
        Venda novaVenda = { produto.id, quantidadeVendida, produto.precoVenda, time(NULL) };
        if (fwrite(&novaVenda, sizeof(Venda), 1, vendaFile) != 1) {
            estado = 4; // Erro ao registrar a venda
            break;
        }

        // Acumula o valor da venda
        valorTotalVenda += quantidadeVendida * produto.precoVenda;
    }

    fclose(dataFile);
    fclose(vendaFile);

    switch (estado) {
    case 3:
        printf("Erro ao atualizar o produto no arquivo. Venda não realizada.\n");
        break;
    case 4:
        printf("Erro ao registrar a venda. Venda não realizada.\n");
        break;
    case 5:
        printf("Produto não encontrado no arquivo. Venda não realizada.\n");
        break;
    default:
        // Se não houve erro, conclui a venda com sucesso
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 10); // Define a cor verde
        printf("Venda realizada com sucesso!\nValor total: R$%.2f\n", valorTotalVenda);

        // Registrar a transação no fluxo de caixa
        registrarTransacao('E', valorTotalVenda, "Venda Realizada");

        getchar();
        getchar();
        mostrarBoasVindas();
        SetConsoleTextAttribute(hConsole, 7); // Reseta para a cor padrão
        inicializarCarrinho(carrinho);
        break;
    }
}




