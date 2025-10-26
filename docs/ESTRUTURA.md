# Estrutura do Projeto

Este documento descreve a organização modular do Sistema ERP Hortifruti.

## 📁 Estrutura de Diretórios

```
hortifruti/
│
├── src/                          # Código-fonte (.c)
│   ├── core/                     # Núcleo do sistema
│   │   ├── main.c               # Ponto de entrada do PimModulos
│   │   ├── login.c              # Sistema de autenticação
│   │   └── link.c               # Funções auxiliares
│   │
│   ├── modules/                  # Módulos de negócio
│   │   ├── produto.c            # Gerenciamento de produtos
│   │   ├── vendas.c             # Gerenciamento de vendas
│   │   ├── carrinho.c           # Sistema de carrinho
│   │   ├── cliente.c            # Cadastro de clientes
│   │   ├── funcionario.c        # Cadastro de funcionários
│   │   ├── fornecedor.c         # Cadastro de fornecedores
│   │   ├── financeiro.c         # Módulo financeiro
│   │   ├── contas.c             # Contas a pagar/receber
│   │   └── pdv.c                # Ponto de venda
│   │
│   ├── utils/                    # Utilitários (futuro)
│   └── balanca.c                 # Módulo da balança
│
├── include/                      # Headers (.h)
│   ├── core/                     # Headers do núcleo
│   │   ├── main.h
│   │   ├── login.h
│   │   └── link.h
│   │
│   ├── modules/                  # Headers dos módulos
│   │   ├── produto.h
│   │   ├── vendas.h
│   │   ├── carrinho.h
│   │   ├── cliente.h
│   │   ├── funcionario.h
│   │   ├── fornecedor.h
│   │   ├── financeiro.h
│   │   ├── contas.h
│   │   └── pdv.h
│   │
│   ├── utils/                    # Headers de utilitários (futuro)
│   └── balanca.h                 # Header da balança
│
├── build/                        # Arquivos compilados (.o)
│   ├── core/
│   └── modules/
│
├── data/                         # Arquivos de dados
│   ├── *.dat                     # Dados binários
│   └── *.idx                     # Índices
│
├── docs/                         # Documentação
│   └── ESTRUTURA.md             # Este arquivo
│
├── scripts/                      # Scripts de build
│   ├── build.sh                 # Build para Linux/macOS
│   └── build.bat                # Build para Windows
│
├── Makefile                      # Makefile para compilação
├── PimModulos.pro               # Projeto Qt Creator
├── vcpkg.json                   # Dependências
├── .gitignore                   # Arquivos ignorados
└── README.md                    # Documentação principal
```

## 🔧 Módulos do Sistema

### Core (Núcleo)

Contém os componentes essenciais do sistema:

- **main.c/h**: Ponto de entrada e menu principal
- **login.c/h**: Sistema de autenticação e controle de acesso
- **link.c/h**: Funções auxiliares compartilhadas

### Modules (Módulos de Negócio)

Contém a lógica de negócio do sistema:

- **produto.c/h**: CRUD de produtos, controle de estoque
- **vendas.c/h**: Registro e consulta de vendas
- **carrinho.c/h**: Carrinho de compras do PDV
- **cliente.c/h**: Cadastro de clientes
- **funcionario.c/h**: Cadastro de funcionários
- **fornecedor.c/h**: Cadastro de fornecedores
- **financeiro.c/h**: Gestão financeira
- **contas.c/h**: Contas a pagar e receber
- **pdv.c/h**: Interface do ponto de venda

### Balança

Módulo independente para pesagem de produtos:

- **balanca.c/h**: Sistema da balança analógica

## 🔨 Compilação

### Usando Makefile

```bash
# Compilar tudo
make

# Compilar e executar PimModulos
make run-pim

# Compilar e executar Balança
make run-balanca

# Limpar arquivos compilados
make clean

# Ver ajuda
make help
```

### Usando Scripts

**Linux/macOS:**
```bash
./scripts/build.sh
```

**Windows:**
```cmd
scripts\build.bat
```

### Usando Qt Creator

1. Abra o arquivo `PimModulos.pro`
2. Configure o kit de compilação
3. Build → Build Project

## 📦 Arquivos de Dados

Os arquivos `.dat` e `.idx` são armazenados no diretório `data/`:

- `produto.dat` / `produto.idx`
- `usuarios.dat` / `usuarios.idx`
- `vendas.dat`
- `clientes.dat`
- `fornecedores.dat` / `fornecedores.idx`
- `fluxo_caixa.dat`
- `contas_pagar.dat`
- `despesas.dat`

## 🎯 Benefícios da Estrutura Modular

1. **Organização**: Código separado por responsabilidade
2. **Manutenibilidade**: Fácil localizar e modificar funcionalidades
3. **Escalabilidade**: Simples adicionar novos módulos
4. **Reusabilidade**: Módulos podem ser reutilizados
5. **Colaboração**: Múltiplos desenvolvedores podem trabalhar simultaneamente
6. **Testabilidade**: Módulos podem ser testados isoladamente

## 📝 Convenções de Código

- Arquivos `.c` em `src/`
- Arquivos `.h` em `include/`
- Nomes de arquivos em minúsculas
- Um módulo = um par `.c` + `.h`
- Includes relativos ao diretório `include/`

## 🚀 Próximos Passos

1. Adicionar testes unitários em `tests/`
2. Criar módulo de logs em `src/utils/`
3. Implementar sistema de configuração
4. Adicionar documentação Doxygen
5. Criar CMakeLists.txt como alternativa ao Makefile

