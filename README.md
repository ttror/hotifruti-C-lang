# Sistema de ERP para Hortifruti em Linguagem C

Este repositório contém o código-fonte de um sistema de gestão (ERP) para um hortifruti de pequeno porte, desenvolvido em linguagem C. O sistema é dividido em dois módulos principais: `PimModulos.exe`, que engloba as funcionalidades de Ponto de Venda (PDV) e o painel administrativo, e `balanca.exe`, um sistema independente para pesagem de produtos.

## Arquitetura do Sistema

O sistema foi construído utilizando a linguagem C e a biblioteca `PDCurses` para a criação da interface de usuário em modo texto no console. A persistência dos dados é realizada através de arquivos binários com as extensões `.dat` para os dados e `.idx` para os índices, simulando um sistema de banco de dados.

### Módulos Principais

O sistema é composto pelos seguintes módulos:

- **PimModulos.exe**: O coração do sistema, que inclui:
    - **Painel Administrativo (ADMIN)**: Permite o gerenciamento de usuários, estoque, campanhas e acesso ao financeiro.
    - **Ponto de Venda (PDV)**: Utilizado para realizar as vendas, adicionar produtos ao carrinho, finalizar e consultar vendas.
- **balanca.exe**: Um executável à parte que simula uma balança analógica. Ele consulta o banco de dados de produtos para obter informações e gerar um ticket (recibo) com o peso e o valor do item.

### Banco de Dados

O sistema utiliza um método de armazenamento de dados baseado em arquivos binários. Cada tipo de dado (produtos, usuários, vendas, etc.) é armazenado em um arquivo `.dat`, e para otimizar as buscas, são utilizados arquivos de índice `.idx`.

## Telas do Sistema

A seguir, são apresentadas as principais telas do sistema:

### Tela da Balança

Esta tela pertence ao `balanca.exe` e é utilizada para pesar os produtos. O operador digita o ID do produto, o sistema o localiza no banco de dados e, em seguida, o peso é inserido para gerar um recibo.

![Tela da Balança](pasted_file_mSY0Kt_image.png)

### Tela de Login

A tela de login é a porta de entrada para os módulos de PDV e ADMIN do `PimModulos.exe`.

- **Login PDV**: `admin` / `admin`
- **Login ADMIN**: `admin` / `admin`

![Tela de Login](pasted_file_6NMXTM_image.png)

### Menu Administrativo

Após o login como administrador, o usuário tem acesso ao menu principal do painel administrativo, onde pode gerenciar as diversas áreas do sistema.

![Menu Administrativo](pasted_file_QKlweM_image.png)

### Ponto de Venda (PDV)

Esta é a tela principal do Ponto de Venda, onde o operador pode adicionar produtos ao carrinho, visualizar o carrinho, finalizar a venda, consultar vendas anteriores e cancelar uma venda em andamento.

![Ponto de Venda (PDV)](pasted_file_uBiguN_image.png)

## Compilação e Execução

Para compilar o projeto, é necessário ter um compilador C (como o GCC/MinGW) e as seguintes bibliotecas de desenvolvimento instaladas:

- `pdcurses`
- `zint`
- `fmt`

Após a configuração do ambiente de compilação, o projeto pode ser compilado utilizando o arquivo de projeto do Qt Creator (`PimModulos.pro`) ou manualmente, linkando as bibliotecas necessárias.

