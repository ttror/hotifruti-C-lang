# Makefile para Sistema ERP Hortifruti
# Desenvolvido por ttror - Copyright 2024

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -Iinclude/core -Iinclude/modules -Iinclude/utils
LDFLAGS = -lpdcurses -lzint -lfmt

# Diretórios
SRC_DIR = src
CORE_DIR = $(SRC_DIR)/core
MODULES_DIR = $(SRC_DIR)/modules
BUILD_DIR = build
DATA_DIR = data

# Arquivos fonte
CORE_SRC = $(CORE_DIR)/main.c $(CORE_DIR)/login.c $(CORE_DIR)/link.c
MODULES_SRC = $(MODULES_DIR)/produto.c $(MODULES_DIR)/vendas.c $(MODULES_DIR)/carrinho.c \
              $(MODULES_DIR)/cliente.c $(MODULES_DIR)/funcionario.c $(MODULES_DIR)/fornecedor.c \
              $(MODULES_DIR)/financeiro.c $(MODULES_DIR)/contas.c $(MODULES_DIR)/pdv.c
BALANCA_SRC = $(SRC_DIR)/balanca.c $(MODULES_DIR)/produto.c $(CORE_DIR)/link.c

# Arquivos objeto
CORE_OBJ = $(CORE_SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
MODULES_OBJ = $(MODULES_SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
BALANCA_OBJ = $(BALANCA_SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Executáveis
PIMMODULOS = PimModulos
BALANCA = balanca

# Adicionar .exe no Windows
ifeq ($(OS),Windows_NT)
    PIMMODULOS := $(PIMMODULOS).exe
    BALANCA := $(BALANCA).exe
endif

# Regra padrão
all: $(BUILD_DIR) $(DATA_DIR) $(PIMMODULOS) $(BALANCA)

# Criar diretórios se não existirem
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)/core $(BUILD_DIR)/modules

$(DATA_DIR):
	mkdir -p $(DATA_DIR)

# Compilar PimModulos
$(PIMMODULOS): $(CORE_OBJ) $(MODULES_OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)
	@echo "PimModulos compilado com sucesso!"

# Compilar Balanca
$(BALANCA): $(BALANCA_OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)
	@echo "Balanca compilado com sucesso!"

# Regras para compilar arquivos objeto
$(BUILD_DIR)/core/%.o: $(CORE_DIR)/%.c
	mkdir -p $(BUILD_DIR)/core
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/modules/%.o: $(MODULES_DIR)/%.c
	mkdir -p $(BUILD_DIR)/modules
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpar arquivos compilados
clean:
	rm -rf $(BUILD_DIR)
	rm -f $(PIMMODULOS) $(BALANCA)
	@echo "Arquivos de build removidos!"

# Limpar tudo incluindo dados
cleanall: clean
	rm -rf $(DATA_DIR)/*.dat $(DATA_DIR)/*.idx
	@echo "Todos os arquivos removidos!"

# Executar PimModulos
run-pim: $(PIMMODULOS)
	./$(PIMMODULOS)

# Executar Balanca
run-balanca: $(BALANCA)
	./$(BALANCA)

# Instalar dependências (vcpkg)
deps:
	@echo "Instalando dependências com vcpkg..."
	vcpkg install pdcurses zint fmt

# Ajuda
help:
	@echo "Makefile do Sistema ERP Hortifruti"
	@echo ""
	@echo "Alvos disponíveis:"
	@echo "  all          - Compila todos os executáveis (padrão)"
	@echo "  clean        - Remove arquivos compilados"
	@echo "  cleanall     - Remove arquivos compilados e dados"
	@echo "  run-pim      - Compila e executa PimModulos"
	@echo "  run-balanca  - Compila e executa Balanca"
	@echo "  deps         - Instala dependências com vcpkg"
	@echo "  help         - Exibe esta mensagem"

.PHONY: all clean cleanall run-pim run-balanca deps help

