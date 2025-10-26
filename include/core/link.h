#ifndef LINK_H
#define LINK_H

// Defini��es de caminhos para arquivos de dados
#define DATA_FILE_PRODUTO "C:\\Users\\win\\Desktop\\PimModulos\\PimModulos\\build\\Desktop_Qt_6_7_2_MinGW_64_bit-Debug\\produto.dat" // Nome do arquivo de dados dos produtos
#define INDEX_FILE_PRODUTO "C:\\Users\\win\\Desktop\\PimModulos\\PimModulos\\build\\Desktop_Qt_6_7_2_MinGW_64_bit-Debug\\produto.idx" // Nome do arquivo de �ndice dos produtos



// Fun��es auxiliares
void lerStringBalanca(char *str, int maxLen, const char *prompt);
void definirCorConsole(int texto, int fundo);
void definirCorBalanca(int texto, int fundo);
void mostrarBoasVindasBalanca();
void mostrarBoasVindasPdv(); // Declara��o da fun��o de boas-vindas para o PDV

#endif // LINK_H
