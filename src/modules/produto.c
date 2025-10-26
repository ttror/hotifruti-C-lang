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
#include "link.h" // Inclua o cabe�alho que cont�m as fun��es de interface

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

    return (tamanho / sizeof(Produto)); // Retorna o n�mero de produtos
}

int obterNovoIdProduto() {
    if (idManagerProduto.count > 0) {
        return idManagerProduto.ids[--idManagerProduto.count]; // Retorna um ID dispon�vel
    }
    return contarProdutos() + 1; // Retorna o pr�ximo ID
}

// Fun��o para ler o peso do produto
bool lerPeso(float *peso) {
    char input[20]; // Buffer para a entrada do usu�rio
    printf("Digite o peso do produto (em kg ou g): ");
    fgets(input, sizeof(input), stdin);

    // Substitui a v�rgula por um ponto para convers�o
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
        // Atualiza a quantidade de produto ap�s a venda
        if (produto.quantidade >= quantidadeVendida) {
            produto.quantidade -= quantidadeVendida; // Subtrai a quantidade vendida
        } else {
            printf("Erro: Quantidade insuficiente em estoque para realizar a venda.\n");
            fclose(dataFile);
            return;
        }

        // Posiciona o ponteiro de volta para a posi��o do produto e escreve os dados atualizados
        fseek(dataFile, posicao, SEEK_SET);
        if (fwrite(&produto, sizeof(Produto), 1, dataFile) != 1) {
            printf("Erro ao salvar as atualiza��es do produto!\n");
        } else {
            printf("Produto atualizado com sucesso! Estoque reduzido.\n");
        }
    } else {
        printf("Produto n�o encontrado com o ID fornecido.\n");
    }

    fclose(dataFile);
}


void cadastrarProduto(int *quantidade) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    FILE *dataFile, *indexFile;
    char continuar = 'S'; // Declara��o da vari�vel 'continuar'

    do {
        dataFile = fopen(DATA_FILE_PRODUTO, "ab+");
        indexFile = fopen(INDEX_FILE_PRODUTO, "ab+");

        if (!dataFile || !indexFile) {
            printf("Erro ao abrir os arquivos de dados ou �ndice!\n");
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
                    printf("ID j� existe! Por favor, escolha outro ID: ");
                } else {
                    break; // ID � v�lido e n�o existe
                }
            } else {
                printf("Entrada inv�lida! Por favor, digite um n�mero positivo.\n");
                while (getchar() != '\n'); // Limpa o buffer at� a nova linha
            }
        }
        getchar(); // Limpa o buffer ap�s a leitura do ID

        // L� os dados do produto
        lerStringBalanca(novoProduto.nome, MAX, "Digite o nome do produto: ");
        lerStringBalanca(novoProduto.codigoBarras, MAX_CODIGO_BARRAS, "Digite o c�digo de barras do produto: ");

        // Perguntar se o produto � vendido a granel
        char resposta[10];
        printf("O produto � vendido a granel? (S/N): ");
        fgets(resposta, sizeof(resposta), stdin);
        novoProduto.vendidoAGranela = (toupper(resposta[0]) == 'S');

        // Captura de pre�os e quantidade
        if (novoProduto.vendidoAGranela) {
            while (1) {
                printf("Digite o pre�o de custo por quilo: ");
                if (scanf("%lf", &novoProduto.precoCusto) == 1 && novoProduto.precoCusto > 0) {
                    break; // Sai do loop se a leitura foi bem-sucedida
                } else {
                    printf("Entrada inv�lida! Por favor, digite um n�mero v�lido.\n");
                    while (getchar() != '\n'); // Limpa o buffer at� a nova linha
                }
            }

            while (1) {
                printf("Digite o pre�o de venda por quilo: ");
                if (scanf("%lf", &novoProduto.precoVenda) == 1 && novoProduto.precoVenda > 0) {
                    break; // Sai do loop se a leitura foi bem-sucedida
                } else {
                    printf("Entrada inv�lida! Por favor, digite um n�mero v�lido.\n");
                    while (getchar() != '\n'); // Limpa o buffer at� a nova linha
                }
            }
        } else {
            // Para produtos n�o vendidos a granel, apenas pre�o normal
            while (1) {
                printf("Digite o pre�o de custo: ");
                if (scanf("%lf", &novoProduto.precoCusto) == 1 && novoProduto.precoCusto > 0) {
                    break; // Sai do loop se a leitura foi bem-sucedida
                } else {
                    printf("Entrada inv�lida! Por favor, digite um n�mero v�lido.\n");
                    while (getchar() != '\n'); // Limpa o buffer at� a nova linha
                }
            }

            while (1) {
                printf("Digite o pre�o de venda: ");
                if (scanf("%lf", &novoProduto.precoVenda) == 1 && novoProduto.precoVenda > 0) {
                    break; // Sai do loop se a leitura foi bem-sucedida
                } else {
                    printf("Entrada inv�lida! Por favor, digite um n�mero v�lido.\n");
                    while (getchar() != '\n'); // Limpa o buffer at� a nova linha
                }
            }
        }

        while (1) {
            printf("Digite a quantidade: ");
            if (scanf("%d", &novoProduto.quantidade) == 1 && novoProduto.quantidade >= 0) {
                break; // Sai do loop se a leitura foi bem-sucedida
            } else {
                printf("Entrada inv�lida! Por favor, digite um n�mero inteiro positivo.\n");
                while (getchar() != '\n'); // Limpa o buffer at� a nova linha
            }
        }
        getchar(); // Limpa o buffer ap�s a leitura da quantidade

        lerStringBalanca(novoProduto.tipo, MAX, "Digite o tipo do produto: ");
        lerStringBalanca(novoProduto.descricao, MAX, "Digite a descri��o do produto: ");

        // Escreve o novo produto no arquivo de dados
        if (fwrite(&novoProduto, sizeof(Produto), 1, dataFile) != 1) {
            printf("Erro ao salvar o produto no arquivo!\n");
        }

        // Cria a entrada do �ndice
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
    int quantidade = contarProdutos(); // Chame a fun��o para obter o n�mero atual de produtos
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
    bool algumProduto = false;  // Para verificar se h� algum produto v�lido

    printf("+-------+-----------------------------+------------+------------------+------------------+----------------------+------------------------------------------+\n");
    printf("| ID    | Nome                        | Quantidade | Pre�o de Custo   | Pre�o de Venda   | Tipo                 | Descri��o                                |\n");
    printf("+-------+-----------------------------+------------+------------------+------------------+----------------------+------------------------------------------+\n");

    for (int i = 0; i < quantidade; i++) {
        if (fread(&produto, sizeof(Produto), 1, dataFile) != 1) {
            printf("Erro ao ler o produto na posi��o %d.\n", i);
            continue; // Pula para a pr�xima itera��o se a leitura falhar
        }

        if (produto.id > 0 && strlen(produto.nome) > 0) { // Verifique se o ID � maior que 0 e o nome n�o est� vazio
            algumProduto = true;

            // Verifica se o produto � a granel e ajusta a exibi��o
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
        printf("\nNenhum produto v�lido encontrado.\n");
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

            // Posi��o atual do ponteiro do arquivo
            long posicaoAtual = ftell(dataFile);
            if (posicaoAtual == -1) {
                printf("Erro ao obter a posi��o do arquivo.\n");
                break; // Saia se n�o conseguir obter a posi��o
            }

            // Retrocede a posi��o para onde o produto est�
            fseek(dataFile, (long)-sizeof(Produto), SEEK_CUR);
            // Escreve o produto modificado de volta no arquivo
            fwrite(&produto, sizeof(Produto), 1, dataFile);

            // Mensagem de sucesso
            printf("Produto com ID %d removido com sucesso!\n", idRemover);
            (*quantidade)--; // Decrementar a contagem de produtos

            // Adiciona o ID removido � lista
            if (idManagerProduto.count < MAX_IDS_PRODUTO) {
                idManagerProduto.ids[idManagerProduto.count++] = idRemover;
            } else {
                printf("Limite de IDs removidos atingido!\n");
            }

            break; // Produto encontrado e processado
        }
    }

    if (!produtoEncontrado) {
        printf("Produto com ID %d n�o encontrado.\n", idRemover);
    }

    fclose(dataFile);
}
