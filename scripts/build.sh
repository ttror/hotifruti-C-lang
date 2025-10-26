#!/bin/bash
# Script de Build para Linux/macOS
# Sistema ERP Hortifruti
# Desenvolvido por ttror - Copyright 2024

echo "========================================"
echo "Sistema ERP Hortifruti - Build Script"
echo "========================================"
echo ""

# Criar diretórios se não existirem
mkdir -p build/core build/modules data

echo "Compilando PimModulos..."
gcc -Wall -Wextra -Iinclude -Iinclude/core -Iinclude/modules -Iinclude/utils \
    src/core/main.c src/core/login.c src/core/link.c \
    src/modules/produto.c src/modules/vendas.c src/modules/carrinho.c \
    src/modules/cliente.c src/modules/funcionario.c src/modules/fornecedor.c \
    src/modules/financeiro.c src/modules/contas.c src/modules/pdv.c \
    -o PimModulos -lpdcurses -lzint -lfmt

if [ $? -ne 0 ]; then
    echo "Erro ao compilar PimModulos!"
    exit 1
fi

echo "PimModulos compilado com sucesso!"
echo ""

echo "Compilando Balanca..."
gcc -Wall -Wextra -Iinclude -Iinclude/core -Iinclude/modules \
    src/balanca.c src/modules/produto.c src/core/link.c \
    -o balanca -lpdcurses

if [ $? -ne 0 ]; then
    echo "Erro ao compilar Balanca!"
    exit 1
fi

echo "Balanca compilado com sucesso!"
echo ""
echo "========================================"
echo "Build concluído com sucesso!"
echo "========================================"
echo ""
echo "Executáveis gerados:"
echo "  - PimModulos"
echo "  - balanca"
echo ""

