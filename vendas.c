#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include <locale.h>
#include <time.h>
#include "vendas.h"
#include "financeiro.h"
#include "link.h"

void consultarVendas() {
    FILE *vendaFile = fopen(DATA_FILE_VENDA, "rb");
    if (!vendaFile) {
        printf("Erro ao abrir o arquivo de vendas!\n");
        return;
    }

    Venda venda;
    Produto produto;

    char buffer[20]; // Buffer para armazenar a data formatada
    struct tm *tm_info; // Estrutura para armazenar informações da data e hora

    printf("+--------------+------------------------------------+------------+---------------+---------------------+\n");
    printf("|  ID Produto  |          Nome do Produto           | Quantidade |  Valor Total  |   Data/Hora         |\n");
    printf("+--------------+------------------------------------+------------+---------------+---------------------+\n");

    while (fread(&venda, sizeof(Venda), 1, vendaFile) == 1) {
        tm_info = localtime(&venda.dataHora);
        strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", tm_info); // Formata a data e hora

        if (buscarProdutoPorId(venda.idProduto, &produto)) {
            printf("| %-11d  | %-30s     | %-10d | R$%-11.2f | %-16s |\n",
                   venda.idProduto, produto.nome, venda.quantidade, venda.valorTotal, buffer);
        } else {
            printf("| %-11d  | %-30s     | %-10d | R$%-11.2f | %-16s |\n",
                   venda.idProduto, "Produto não encontrado", venda.quantidade, venda.valorTotal, buffer);
        }
    }

    printf("+--------------+------------------------------------+------------+---------------+---------------------+\n");

    fclose(vendaFile);
}

void cancelarVenda(int idVenda) {
    FILE *vendaFile = fopen(DATA_FILE_VENDA, "rb");
    if (!vendaFile) {
        printf("Erro ao abrir o arquivo de vendas!\n");
        return;
    }

    FILE *tempFile = fopen("temp.dat", "wb");
    if (!tempFile) {
        printf("Erro ao criar arquivo temporário!\n");
        fclose(vendaFile);
        return;
    }

    Venda venda;
    Produto produto;
    int vendaEncontrada = 0;

    while (fread(&venda, sizeof(Venda), 1, vendaFile) == 1) {
        if (venda.idProduto == idVenda) {
            vendaEncontrada = 1;
            printf("Venda cancelada: ID Produto: %d | Quantidade: %d | Valor Total: R$%.2f\n",
                   venda.idProduto, venda.quantidade, venda.valorTotal);

            // Reverter a quantidade de produtos no estoque
            if (buscarProdutoPorId(venda.idProduto, &produto)) {
                produto.quantidade += venda.quantidade;
                FILE *dataFile = fopen(DATA_FILE_PRODUTO, "r+b");
                if (dataFile) {
                    fseek(dataFile, (venda.idProduto - 1) * sizeof(Produto), SEEK_SET);
                    fwrite(&produto, sizeof(Produto), 1, dataFile);
                    fclose(dataFile);
                }
            }

            // Registrar a transação de saída no módulo financeiro
            registrarTransacao('S', venda.valorTotal, "Cancelamento de Venda");

            continue;
        }
        fwrite(&venda, sizeof(Venda), 1, tempFile);
    }

    fclose(vendaFile);
    fclose(tempFile);
    remove(DATA_FILE_VENDA);
    rename("temp.dat", DATA_FILE_VENDA);

    if (!vendaEncontrada) {
        printf("Venda com ID %d não encontrada!\n", idVenda);
    }
}
