# hotifruti-C-lang

Este é um projeto em linguagem C que simula um **Sistema de Gestão Empresarial (ERP)** completo para um hortifruti.

## 🎯 Visão Geral do Sistema

O sistema é dividido em dois executáveis principais:

1.  **`hortifruti.exe` (Módulo Principal):** Contém o Ponto de Venda (PDV), o Menu Administrativo e todos os módulos de gestão (Produtos, Clientes, Financeiro, etc.).
2.  **`balanca.exe` (Módulo de Balança):** Um módulo separado para operações de pesagem e geração de recibos.

### 🔑 Credenciais de Acesso Padrão

O módulo principal (`hortifruti.exe`) requer login. Use as seguintes credenciais:

| Módulo | Usuário | Senha |
|--------|---------|-------|
| **ADMIN** | `admin` | `admin` |
| **PDV** | `pdv` | `pdv` |

### 🏗️ Arquitetura e Dependências

O sistema utiliza:
*   **Linguagem C** para o desenvolvimento.
*   **PDCurses** para a interface de utilizador em modo texto (console).
*   **Arquivos Binários** (`.dat` e `.idx`) para persistência de dados (simulando um banco de dados).

---

## 💻 Compilação e Execução para Windows

## 💻 Compilação e Execução para Windows

Para compilar e executar este projeto no Windows, é necessário instalar um ambiente de desenvolvimento que inclua o compilador C e as ferramentas de build (`make`).

### 1. Preparação do Ambiente (Instalação do MinGW-w64 via MSYS2)

A forma mais fácil de obter todas as ferramentas necessárias é através do **MSYS2**.

1.  **Baixe e Instale o MSYS2:**
    *   Vá para o site oficial do [MSYS2](https://www.msys2.org/).
    *   Baixe o instalador e siga os passos de instalação padrão.

2.  **Instale as Ferramentas de Compilação:**
    *   Após a instalação, abra o **MSYS2 MinGW 64-bit** (este é o terminal que você usará para todos os comandos seguintes).
    *   Instale o compilador C/C++ (`toolchain`) e o utilitário `make`:
        ```bash
        pacman -S mingw-w64-x86_64-toolchain make --noconfirm
        ```

3.  **Instale o Git (Opcional, mas Recomendado):**
    *   Para clonar este repositório, instale o Git no ambiente MSYS2:
        ```bash
        pacman -S git --noconfirm
        ```

### 2. Configuração do Projeto (PDCurses)

O projeto utiliza a biblioteca **PDCurses** para criar a interface de texto. Esta biblioteca precisa ser compilada primeiro.

1.  **Clone o PDCursesMod:**
    *   No terminal **MSYS2 MinGW 64-bit**, navegue para o diretório onde você quer guardar o projeto (ex: `cd /c/Users/SeuUsuario/Documents`).
    *   Clone o PDCursesMod (uma versão ativa e compatível com MinGW) no **diretório pai** do seu projeto `hotifruti-C-lang`:
        ```bash
        git clone https://github.com/Bill-Gray/PDCursesMod.git
        ```

2.  **Compile o PDCurses:**
    *   Compile a biblioteca estática (`curses.a`) do PDCursesMod:
        ```bash
        cd PDCursesMod/wincon
        make -f Makefile curses.a
        cd ../..
        ```
    *   *Este passo criará o arquivo `curses.a` e o `pdcurses.dll` necessários para a compilação e execução do seu projeto.*

### 3. Compilação do Projeto Principal

1.  **Clone o Repositório Principal:**
    *   Se você ainda não o fez, clone o projeto `hotifruti-C-lang`:
        ```bash
        git clone https://github.com/ttror/hotifruti-C-lang.git
        ```

2.  **Compile o Projeto:**
    *   Navegue até o diretório raiz do projeto:
        ```bash
        cd hotifruti-C-lang
        ```
    *   Execute o `make` para compilar:
        ```bash
        make
        ```

Isso irá gerar os executáveis:
-   `hortifruti.exe` (Programa principal)
-   `balanca.exe` (Programa de balança)

### 4. Execução

Para executar o programa, você precisa que a biblioteca dinâmica (`pdcurses.dll`) esteja no mesmo diretório do executável.

1.  **Copie a DLL:**
    ```bash
    cp ../PDCursesMod/wincon/pdcurses.dll .
    ```

2.  **Execute o Programa:**
    ```bash
    ./hortifruti.exe
    ```

**Observação:** O arquivo `balanca.exe` também precisará do `pdcurses.dll` para funcionar.

---
## ⚠️ Informações Adicionais

- **Executáveis Gerados:** O `make` gera `hortifruti.exe` e `balanca.exe`.
- **Credenciais de Acesso Padrão:**
    - **PDV:** `admin` / `admin`
    - **ADMIN:** `admin` / `admin`
- **Estrutura de Arquivos:** O projeto utiliza arquivos binários (`.dat` e `.idx`) para persistência de dados. Esses arquivos serão criados automaticamente na primeira execução.

