#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <time.h>
#include "link.h"
#include "produto.h" // Inclua seu cabe�alho de produtos

// Declara��es de fun��es
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
            printf("Produto encontrado: %s, Pre�o por kg: R$ %.2f\n", produto->nome, produto->precoVenda); // Debug
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
    fprintf(file, "C�digo de Barras: %s\n", codigoBarras); // Adiciona o c�digo de barras ao recibo
    fprintf(file, "Peso: %.2f kg\n", peso);
    fprintf(file, "Pre�o por kg: R$ %.2f\n", precoPorKilo);
    fprintf(file, "Total: R$ %.2f\n", total);
    fprintf(file, "Data e Hora: %s\n", dataHora);
    fprintf(file, "========================================\n");

    fclose(file);
    printf("Recibo salvo em: C:\\Temp\\recibo.txt\n");
}

void menuBuscarProdutoBalanca() {
    int id;
    char input[10]; // Buffer para a entrada do usu�rio

    lerStringBalanca(input, sizeof(input), "Digite o ID do produto: ");
    id = atoi(input); // Converte a string para inteiro

    Produto produto;
    if (buscarProdutoPorId(id, &produto)) {
        printf("\nProduto encontrado:\n");
        printf("+-------------------------------+\n");
        printf("| Nome:        %s\n", produto.nome);
        printf("| C�digo de Barras: %s\n", produto.codigoBarras);
        printf("| Pre�o por kg: R$ %.2f\n", produto.precoVenda); // Aqui deve ser produto.precoVenda
        printf("| Quantidade dispon�vel: %d\\KG\n", produto.quantidade);
        printf("+-------------------------------+\n");

        float peso;
        lerStringBalanca(input, sizeof(input), "Digite o peso do produto em kg: ");
        peso = atof(input); // Converte a string para float

        if (peso <= produto.quantidade) {
            salvarRecibo(peso, produto.nome, produto.precoVenda, produto.codigoBarras); // Passando produto.precoVenda
            printf("Produto registrado. O d�bito do estoque ocorrer� no PDV.\n");
        } else {
            printf("Peso solicitado maior que a quantidade dispon�vel!\n");
        }
    } else {
        printf("Produto com ID %d n�o encontrado.\n", id);
    }
}




int main(void) {
    setlocale(LC_ALL, "Portuguese_Brazil"); // Define o idioma
    mostrarBoasVindasBalanca(); // Exibe a mensagem de boas-vindas

    char input[10]; // Buffer para a entrada do usu�rio
    char opcao; // Declara��o da vari�vel opcao

    do {
        // Exibe o menu em formato de grid
        printf("\n+---------------------------------+\n");
        printf("|      BALAN�A ANAL�GICA          |\n");
        printf("+---------------------------------+\n");
        printf("| [A] Digite o ID do produto      |\n");
        printf("| [S] Sair                        |\n");
        printf("+---------------------------------+\n");

        // Solicita que o usu�rio escolha uma op��o
        printf("Escolha uma op��o [A] para ID, [S] para sair: ");
        lerStringBalanca(input, sizeof(input), "Escolha: "); // L� a entrada do usu�rio

        // Converte a entrada para min�sculas para facilitar a compara��o
        opcao = tolower(input[0]);

        switch (opcao) {
        case 'a': // Op��o para consultar produto por ID
            menuBuscarProdutoBalanca();
            break;
        case 's': // Op��o para sair
            printf("Saindo da balan�a anal�gica. O controle de estoque ser� feito no PDV.\n");
            break;
        default: // Op��o inv�lida
            printf("Op��o inv�lida! Tente novamente.\n");
            break;
        }
    } while (opcao != 's'); // Continua at� que a op��o 'S' ou 's' seja escolhida

    return 0;
}
