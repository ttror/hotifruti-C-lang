TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        carinho.c \
        cliente.c \
        contas.c \
        financeiro.c \
        fornecedor.c \
        funcionario.c \
        link.c  \
        login.c \
        main.c \
        produto.c \
        vendas.c

HEADERS += \
    carrinho.h \
    cliente.h \
    contas.h \
    financeiro.h \
    fornecedor.h \
    funcionario.h \
    link.h \
    login.h \
    main.h \
    produto.h \
    vendas.h


# Lista de arquivos que devem ser incluídos no pacote de distribuição
DISTFILES += \
    vcpkg.json

# Definindo a raiz do vcpkg
VCPKG_ROOT = D:/vcpkg

# Adicionando diretórios de inclusão
INCLUDEPATH += $$VCPKG_ROOT/installed/x64-windows/include

# Adicionando diretórios de bibliotecas e as bibliotecas necessárias
LIBS += -L$$VCPKG_ROOT/installed/x64-windows/lib -lpdcurses -lzint

