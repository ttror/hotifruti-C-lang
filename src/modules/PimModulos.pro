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


# Lista de arquivos que devem ser inclu�dos no pacote de distribui��o
DISTFILES += \
    vcpkg.json

# Definindo a raiz do vcpkg
VCPKG_ROOT = D:/vcpkg

# Adicionando diret�rios de inclus�o
INCLUDEPATH += $$VCPKG_ROOT/installed/x64-windows/include

# Adicionando diret�rios de bibliotecas e as bibliotecas necess�rias
LIBS += -L$$VCPKG_ROOT/installed/x64-windows/lib -lpdcurses -lzint

