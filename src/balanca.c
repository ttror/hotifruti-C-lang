#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <time.h>
#include "link.h"
#include "produto.h" // Inclua seu cabeçalho de produtos

// Declarações de funções
void testarAcessoAoArquivo(); 
bool buscarProdutoPorId(int id, Produto *produto);
void salvarRecibo(float peso, const char *nomeProduto, float precoPorKilo, const char *codigoBarras);
void menuBuscarProdutoBalanca();


void testarAcessoAoArquivo() {
    FILE *dataFile = fopen(DATA_FILE_PRODUTO, "rb");
    if (!dataFile) {
        printf("Erro ao acessar o arquivo de dados dos produtos! Caminho: %s\n", DATA_FILE_PRODUTO);
    } else {
        printf("Arquivo acessado com sucesso!\n");
        fclose(dataFile);
    }
}

bool buscarProdutoPorId(int id, Produto *produto) {
    FILE *dataFile = fopen(DATA_FILE_PRODUTO, "rb");
    if (!dataFile) {
        printf("Erro ao abrir o arquivo de dados dos produtos!\n");
        return false;
    }

    bool encontrado = false;
    while (fread(produto, sizeof(Produto), 1, dataFile)) {
        if (produto->id == id) {
            encontrado = true; // Produto encontrado
            printf("Produto encontrado: %s, Preço por kg: R$ %.2f\n", produto->nome, produto->precoVenda); // Debug
            break;
        }
    }

    fclose(dataFile);
    return encontrado; // Retorna verdadeiro se encontrado
}


void salvarRecibo(float peso, const char *nomeProduto, float precoPorKilo, const char *codigoBarras) {
    float total = peso * precoPorKilo;
    time_t agora = time(NULL);
    struct tm *tm_info = localtime(&agora);
    char dataHora[26];
    strftime(dataHora, sizeof(dataHora), "%d/%m/%Y %H:%M", tm_info);

    FILE *file = fopen("C:\\Temp\\recibo.txt", "w");
    if (!file) {
        printf("Erro ao abrir o arquivo para salvar o recibo.\n");
        return;
    }

    fprintf(file, "            CUPOM FISCAL\n");
    fprintf(file, "========================================\n");
    fprintf(file, "Produto: %s\n", nomeProduto);
    fprintf(file, "Código de Barras: %s\n", codigoBarras); // Adiciona o código de barras ao recibo
    fprintf(file, "Peso: %.2f kg\n", peso);
    fprintf(file, "Preço por kg: R$ %.2f\n", precoPorKilo);
    fprintf(file, "Total: R$ %.2f\n", total);
    fprintf(file, "Data e Hora: %s\n", dataHora);
    fprintf(file, "========================================\n");

    fclose(file);
    printf("Recibo salvo em: C:\\Temp\\recibo.txt\n");
}

void menuBuscarProdutoBalanca() {
    int id;
    char input[10]; // Buffer para a entrada do usuário

    lerStringBalanca(input, sizeof(input), "Digite o ID do produto: ");
    id = atoi(input); // Converte a string para inteiro

    Produto produto;
    if (buscarProdutoPorId(id, &produto)) {
        printf("\nProduto encontrado:\n");
        printf("+-------------------------------+\n");
        printf("| Nome:        %s\n", produto.nome);
        printf("| Código de Barras: %s\n", produto.codigoBarras);
        printf("| Preço por kg: R$ %.2f\n", produto.precoVenda); // Aqui deve ser produto.precoVenda
        printf("| Quantidade disponível: %d\\KG\n", produto.quantidade);
        printf("+-------------------------------+\n");

        float peso;
        lerStringBalanca(input, sizeof(input), "Digite o peso do produto em kg: ");
        peso = atof(input); // Converte a string para float

        if (peso <= produto.quantidade) {
            salvarRecibo(peso, produto.nome, produto.precoVenda, produto.codigoBarras); // Passando produto.precoVenda
            printf("Produto registrado. O débito do estoque ocorrerá no PDV.\n");
        } else {
            printf("Peso solicitado maior que a quantidade disponível!\n");
        }
    } else {
        printf("Produto com ID %d não encontrado.\n", id);
    }
}




int main(void) {
    setlocale(LC_ALL, "Portuguese_Brazil"); // Define o idioma
    mostrarBoasVindasBalanca(); // Exibe a mensagem de boas-vindas

    char input[10]; // Buffer para a entrada do usuário
    char opcao; // Declaração da variável opcao

    do {
        // Exibe o menu em formato de grid
        printf("\n+---------------------------------+\n");
        printf("|      BALANÇA ANALÓGICA          |\n");
        printf("+---------------------------------+\n");
        printf("| [A] Digite o ID do produto      |\n");
        printf("| [S] Sair                        |\n");
        printf("+---------------------------------+\n");

        // Solicita que o usuário escolha uma opção
        printf("Escolha uma opção [A] para ID, [S] para sair: ");
        lerStringBalanca(input, sizeof(input), "Escolha: "); // Lê a entrada do usuário

        // Converte a entrada para minúsculas para facilitar a comparação
        opcao = tolower(input[0]);

        switch (opcao) {
        case 'a': // Opção para consultar produto por ID
            menuBuscarProdutoBalanca();
            break;
        case 's': // Opção para sair
            printf("Saindo da balança analógica. O controle de estoque será feito no PDV.\n");
            break;
        default: // Opção inválida
            printf("Opção inválida! Tente novamente.\n");
            break;
        }
    } while (opcao != 's'); // Continua até que a opção 'S' ou 's' seja escolhida

    return 0;
}
