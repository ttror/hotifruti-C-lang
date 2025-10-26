#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <conio.h>
#include <ctype.h>
#include <locale.h>
#include <math.h>
#include "produto.h"
#include "financeiro.h"
#include "link.h" // Inclua o cabeçalho que contém as funções de interface

IdManagerProduto idManagerProduto = {.count = 0};


int contarProdutos() {
    FILE *dataFile = fopen(DATA_FILE_PRODUTO, "rb");
    if (!dataFile) {
        printf("Erro ao abrir o arquivo de dados dos produtos!\n");
        return 0; // Retorna 0 se houver erro
    }

    fseek(dataFile, 0, SEEK_END);
    long tamanho = ftell(dataFile);
    fclose(dataFile);

    return (tamanho / sizeof(Produto)); // Retorna o número de produtos
}

int obterNovoIdProduto() {
    if (idManagerProduto.count > 0) {
        return idManagerProduto.ids[--idManagerProduto.count]; // Retorna um ID disponível
    }
    return contarProdutos() + 1; // Retorna o próximo ID
}

// Função para ler o peso do produto
bool lerPeso(float *peso) {
    char input[20]; // Buffer para a entrada do usuário
    printf("Digite o peso do produto (em kg ou g): ");
    fgets(input, sizeof(input), stdin);

    // Substitui a vírgula por um ponto para conversão
    for (int i = 0; input[i]; i++) {
        if (input[i] == ',') {
            input[i] = '.';
        }
    }

    *peso = atof(input); // Converte a string para float
    return *peso > 0; // Retorna verdadeiro se o peso for positivo
}

void atualizarProduto(int id, int quantidadeVendida) {
    FILE *dataFile = fopen(DATA_FILE_PRODUTO, "rb+");
    if (!dataFile) {
        printf("Erro ao abrir o arquivo de dados de produtos!\n");
        return;
    }

    Produto produto;
    bool produtoEncontrado = false;
    long posicao = -1;

    // Percorre o arquivo de dados para encontrar o produto
    while (fread(&produto, sizeof(Produto), 1, dataFile) == 1) {
        if (produto.id == id) {
            produtoEncontrado = true;
            posicao = ftell(dataFile) - sizeof(Produto);
            break;
        }
    }

    if (produtoEncontrado) {
        // Atualiza a quantidade de produto após a venda
        if (produto.quantidade >= quantidadeVendida) {
            produto.quantidade -= quantidadeVendida; // Subtrai a quantidade vendida
        } else {
            printf("Erro: Quantidade insuficiente em estoque para realizar a venda.\n");
            fclose(dataFile);
            return;
        }

        // Posiciona o ponteiro de volta para a posição do produto e escreve os dados atualizados
        fseek(dataFile, posicao, SEEK_SET);
        if (fwrite(&produto, sizeof(Produto), 1, dataFile) != 1) {
            printf("Erro ao salvar as atualizações do produto!\n");
        } else {
            printf("Produto atualizado com sucesso! Estoque reduzido.\n");
        }
    } else {
        printf("Produto não encontrado com o ID fornecido.\n");
    }

    fclose(dataFile);
}


void cadastrarProduto(int *quantidade) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    FILE *dataFile, *indexFile;
    char continuar = 'S'; // Declaração da variável 'continuar'

    do {
        dataFile = fopen(DATA_FILE_PRODUTO, "ab+");
        indexFile = fopen(INDEX_FILE_PRODUTO, "ab+");

        if (!dataFile || !indexFile) {
            printf("Erro ao abrir os arquivos de dados ou índice!\n");
            if (dataFile) fclose(dataFile);
            if (indexFile) fclose(indexFile);
            return;
        }

        Produto novoProduto;
        printf("Digite o ID do produto: ");
        while (1) {
            if (scanf("%d", &novoProduto.id) == 1 && novoProduto.id > 0) {
                bool idExistente = false;
                Produto produto;
                fseek(dataFile, 0, SEEK_SET);
                while (fread(&produto, sizeof(Produto), 1, dataFile) == 1) {
                    if (produto.id == novoProduto.id) {
                        idExistente = true;
                        break;
                    }
                }
                if (idExistente) {
                    printf("ID já existe! Por favor, escolha outro ID: ");
                } else {
                    break; // ID é válido e não existe
                }
            } else {
                printf("Entrada inválida! Por favor, digite um número positivo.\n");
                while (getchar() != '\n'); // Limpa o buffer até a nova linha
            }
        }
        getchar(); // Limpa o buffer após a leitura do ID

        // Lê os dados do produto
        lerStringBalanca(novoProduto.nome, MAX, "Digite o nome do produto: ");
        lerStringBalanca(novoProduto.codigoBarras, MAX_CODIGO_BARRAS, "Digite o código de barras do produto: ");

        // Perguntar se o produto é vendido a granel
        char resposta[10];
        printf("O produto é vendido a granel? (S/N): ");
        fgets(resposta, sizeof(resposta), stdin);
        novoProduto.vendidoAGranela = (toupper(resposta[0]) == 'S');

        // Captura de preços e quantidade
        if (novoProduto.vendidoAGranela) {
            while (1) {
                printf("Digite o preço de custo por quilo: ");
                if (scanf("%lf", &novoProduto.precoCusto) == 1 && novoProduto.precoCusto > 0) {
                    break; // Sai do loop se a leitura foi bem-sucedida
                } else {
                    printf("Entrada inválida! Por favor, digite um número válido.\n");
                    while (getchar() != '\n'); // Limpa o buffer até a nova linha
                }
            }

            while (1) {
                printf("Digite o preço de venda por quilo: ");
                if (scanf("%lf", &novoProduto.precoVenda) == 1 && novoProduto.precoVenda > 0) {
                    break; // Sai do loop se a leitura foi bem-sucedida
                } else {
                    printf("Entrada inválida! Por favor, digite um número válido.\n");
                    while (getchar() != '\n'); // Limpa o buffer até a nova linha
                }
            }
        } else {
            // Para produtos não vendidos a granel, apenas preço normal
            while (1) {
                printf("Digite o preço de custo: ");
                if (scanf("%lf", &novoProduto.precoCusto) == 1 && novoProduto.precoCusto > 0) {
                    break; // Sai do loop se a leitura foi bem-sucedida
                } else {
                    printf("Entrada inválida! Por favor, digite um número válido.\n");
                    while (getchar() != '\n'); // Limpa o buffer até a nova linha
                }
            }

            while (1) {
                printf("Digite o preço de venda: ");
                if (scanf("%lf", &novoProduto.precoVenda) == 1 && novoProduto.precoVenda > 0) {
                    break; // Sai do loop se a leitura foi bem-sucedida
                } else {
                    printf("Entrada inválida! Por favor, digite um número válido.\n");
                    while (getchar() != '\n'); // Limpa o buffer até a nova linha
                }
            }
        }

        while (1) {
            printf("Digite a quantidade: ");
            if (scanf("%d", &novoProduto.quantidade) == 1 && novoProduto.quantidade >= 0) {
                break; // Sai do loop se a leitura foi bem-sucedida
            } else {
                printf("Entrada inválida! Por favor, digite um número inteiro positivo.\n");
                while (getchar() != '\n'); // Limpa o buffer até a nova linha
            }
        }
        getchar(); // Limpa o buffer após a leitura da quantidade

        lerStringBalanca(novoProduto.tipo, MAX, "Digite o tipo do produto: ");
        lerStringBalanca(novoProduto.descricao, MAX, "Digite a descrição do produto: ");

        // Escreve o novo produto no arquivo de dados
        if (fwrite(&novoProduto, sizeof(Produto), 1, dataFile) != 1) {
            printf("Erro ao salvar o produto no arquivo!\n");
        }

        // Cria a entrada do índice
        IndexEntryProduto indiceNovo = {novoProduto.id, ftell(dataFile) - sizeof(Produto)};
        fwrite(&indiceNovo, sizeof(IndexEntryProduto), 1, indexFile);

        (*quantidade)++;
        SetConsoleTextAttribute(hConsole, 10);
        printf("Produto cadastrado com sucesso!\n");
        SetConsoleTextAttribute(hConsole, 7);

        fclose(dataFile);
        fclose(indexFile);

        // Pergunta se deseja continuar cadastrando
        printf("Deseja continuar cadastrando? (S/N): ");
        char buffer[10];
        fgets(buffer, sizeof(buffer), stdin);
        continuar = toupper(buffer[0]);

    } while (continuar == 'S');
}



void listarProdutos() {
    int quantidade = contarProdutos(); // Chame a função para obter o número atual de produtos
    if (quantidade == 0) {
        printf("Nenhum produto cadastrado no sistema.\n");
        return;
    }

    FILE *dataFile = fopen(DATA_FILE_PRODUTO, "rb");
    if (!dataFile) {
        printf("Erro ao abrir o arquivo de dados!\n");
        return;
    }

    Produto produto;
    bool algumProduto = false;  // Para verificar se há algum produto válido

    printf("+-------+-----------------------------+------------+------------------+------------------+----------------------+------------------------------------------+\n");
    printf("| ID    | Nome                        | Quantidade | Preço de Custo   | Preço de Venda   | Tipo                 | Descrição                                |\n");
    printf("+-------+-----------------------------+------------+------------------+------------------+----------------------+------------------------------------------+\n");

    for (int i = 0; i < quantidade; i++) {
        if (fread(&produto, sizeof(Produto), 1, dataFile) != 1) {
            printf("Erro ao ler o produto na posição %d.\n", i);
            continue; // Pula para a próxima iteração se a leitura falhar
        }

        if (produto.id > 0 && strlen(produto.nome) > 0) { // Verifique se o ID é maior que 0 e o nome não está vazio
            algumProduto = true;

            // Verifica se o produto é a granel e ajusta a exibição
            if (produto.vendidoAGranela) {
                printf("| %-5d | %-27s | %-4d/KG    | R$%-5.2f/KG       | R$%-5.2f/KG       | %-20s | %-40s |\n",
                       produto.id, produto.nome, produto.quantidade,
                       produto.precoCusto, produto.precoVenda, produto.tipo, produto.descricao);
            } else {
                // Para outros produtos, exibe normalmente
                printf("| %-5d | %-27s | %-10d | R$%-14.2f | R$%-14.2f | %-20s | %-40s |\n",
                       produto.id, produto.nome, produto.quantidade, produto.precoCusto,
                       produto.precoVenda, produto.tipo, produto.descricao);
            }
        }
    }
    printf("+-------+-----------------------------+------------+------------------+------------------+----------------------+------------------------------------------+\n");

    if (!algumProduto) {
        printf("\nNenhum produto válido encontrado.\n");
    }

    fclose(dataFile);
}







void removerProduto(int *quantidade) {
    FILE *dataFile = fopen(DATA_FILE_PRODUTO, "rb+");
    if (!dataFile) {
        printf("Erro ao abrir o arquivo de dados!\n");
        return;
    }

    int idRemover;
    printf("Digite o ID do produto a ser removido: ");
    scanf("%d", &idRemover);
    getchar(); // Limpa o buffer de entrada

    Produto produto;
    bool produtoEncontrado = false;

    // Percorre o arquivo de dados para encontrar o produto
    while (fread(&produto, sizeof(Produto), 1, dataFile) == 1) {
        if (produto.id == idRemover) {
            produtoEncontrado = true;
            produto.id = -1; // Marcar como removido

            // Posição atual do ponteiro do arquivo
            long posicaoAtual = ftell(dataFile);
            if (posicaoAtual == -1) {
                printf("Erro ao obter a posição do arquivo.\n");
                break; // Saia se não conseguir obter a posição
            }

            // Retrocede a posição para onde o produto está
            fseek(dataFile, (long)-sizeof(Produto), SEEK_CUR);
            // Escreve o produto modificado de volta no arquivo
            fwrite(&produto, sizeof(Produto), 1, dataFile);

            // Mensagem de sucesso
            printf("Produto com ID %d removido com sucesso!\n", idRemover);
            (*quantidade)--; // Decrementar a contagem de produtos

            // Adiciona o ID removido à lista
            if (idManagerProduto.count < MAX_IDS_PRODUTO) {
                idManagerProduto.ids[idManagerProduto.count++] = idRemover;
            } else {
                printf("Limite de IDs removidos atingido!\n");
            }

            break; // Produto encontrado e processado
        }
    }

    if (!produtoEncontrado) {
        printf("Produto com ID %d não encontrado.\n", idRemover);
    }

    fclose(dataFile);
}
