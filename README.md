# hotifruti-C-lang

Este é um projeto em linguagem C que simula um sistema de gestão para um hortifruti.

## Compilação para Windows (MinGW-w64)

Para compilar este projeto no Windows, você precisará do **MinGW-w64** (um conjunto de ferramentas de desenvolvimento para Windows) e da biblioteca **PDCurses** para a interface de terminal.

### 1. Instalação do MinGW-w64

Recomendamos o uso do **MSYS2** para gerenciar o MinGW-w64 e as dependências:

1.  Baixe e instale o **MSYS2** a partir do site oficial.
2.  Após a instalação, abra o **MSYS2 MinGW 64-bit**.
3.  Instale o toolchain do C/C++ e o `make`:
    ```bash
    pacman -S mingw-w64-x86_64-toolchain make
    ```

### 2. Configuração do Projeto (PDCurses)

O projeto depende da biblioteca PDCurses para a interface de terminal.

1.  Clone o repositório do PDCursesMod (uma versão ativa e compatível com MinGW) no **diretório pai** do seu projeto `hotifruti-C-lang`:
    ```bash
    git clone https://github.com/Bill-Gray/PDCursesMod.git
    ```
2.  Compile a biblioteca estática (`curses.a`) do PDCursesMod. **Este passo é crucial para que o `make` do projeto principal funcione.**
    ```bash
    cd PDCursesMod/wincon
    make -f Makefile curses.a
    cd ../..
    ```
    *Isso criará o arquivo `curses.a` e o `curses.h` na pasta correta para a compilação.*

### 3. Compilação do Projeto

1.  Navegue até o diretório raiz do projeto `hotifruti-C-lang`:
    ```bash
    cd hotifruti-C-lang
    ```
2.  Execute o `make` para compilar:
    ```bash
    make
    ```

Isso irá gerar os executáveis:
-   `hortifruti.exe` (Programa principal)
-   `balanca.exe` (Programa de balança)

### 4. Execução

Para executar o programa principal, você precisará copiar o `pdcurses.dll` (que deve estar na pasta `PDCursesMod/wincon` após a compilação do PDCurses) para o mesmo diretório do `hortifruti.exe`.

```bash
# Copie a DLL para o diretório de execução
cp ../PDCursesMod/wincon/pdcurses.dll .

# Execute o programa
./hortifruti.exe
```

**Observação:** O arquivo `balanca.exe` também precisará do `pdcurses.dll` para funcionar.

## ⚠️ Diferença de Executáveis

A versão original do Git usava `PimModulos.exe`. Esta versão corrigida usa `hortifruti.exe` como executável principal, conforme o seu pedido e o código-fonte.

