@echo off
REM Script de Build para Windows
REM Sistema ERP Hortifruti
REM Desenvolvido por ttror - Copyright 2024

echo ========================================
echo Sistema ERP Hortifruti - Build Script
echo ========================================
echo.

REM Criar diretórios se não existirem
if not exist "build" mkdir build
if not exist "build\core" mkdir build\core
if not exist "build\modules" mkdir build\modules
if not exist "data" mkdir data

echo Compilando PimModulos...
gcc -Wall -Wextra -Iinclude -Iinclude\core -Iinclude\modules -Iinclude\utils ^
    src\core\main.c src\core\login.c src\core\link.c ^
    src\modules\produto.c src\modules\vendas.c src\modules\carrinho.c ^
    src\modules\cliente.c src\modules\funcionario.c src\modules\fornecedor.c ^
    src\modules\financeiro.c src\modules\contas.c src\modules\pdv.c ^
    -o PimModulos.exe -lpdcurses -lzint -lfmt

if %errorlevel% neq 0 (
    echo Erro ao compilar PimModulos!
    exit /b 1
)

echo PimModulos compilado com sucesso!
echo.

echo Compilando Balanca...
gcc -Wall -Wextra -Iinclude -Iinclude\core -Iinclude\modules ^
    src\balanca.c src\modules\produto.c src\core\link.c ^
    -o balanca.exe -lpdcurses

if %errorlevel% neq 0 (
    echo Erro ao compilar Balanca!
    exit /b 1
)

echo Balanca compilado com sucesso!
echo.
echo ========================================
echo Build concluído com sucesso!
echo ========================================
echo.
echo Executáveis gerados:
echo   - PimModulos.exe
echo   - balanca.exe
echo.

pause

