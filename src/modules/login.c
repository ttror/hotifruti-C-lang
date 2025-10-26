#include <curses.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <locale.h>
#include "login.h"
#include "main.h"

// Definição dos usuários
UsuarioLogin usuarios[] = {
    {"admin", "admin", 1},
    {"pdv", "pdv", 2}
};

// Função externa para o menu principal
extern void mostrarMenuPrincipal();
extern void gerenciarVendas();
extern void menuAdm();

#define NUM_MENU_ITEMS 2
#define NUM_USUARIOS (sizeof(usuarios) / sizeof(usuarios[0]))
#define USERNAME_MAX_LENGTH 50
#define PASSWORD_MAX_LENGTH 50

// Logo do menu
const char *menu_logo[8] = {
    "##     ##  #######  ########  ######## #### ######## ########  ##     ## ######## #### ",
    "##     ## ##     ## ##     ##    ##     ##  ##       ##     ## ##     ##    ##     ##  ",
    "##     ## ##     ## ##     ##    ##     ##  ##       ##     ## ##     ##    ##     ##  ",
    "######### ##     ## ########     ##     ##  ######   ########  ##     ##    ##     ##  ",
    "##     ## ##     ## ##   ##      ##     ##  ##       ##   ##   ##     ##    ##     ##  ",
    "##     ## ##     ## ##    ##     ##     ##  ##       ##    ##  ##     ##    ##     ##  ",
    "##     ##  #######  ##     ##    ##    #### ##       ##     ##  #######     ##    #### ",
    "Solutions Copyright 2024.                                            Versao Beta 1.5.0 "
};

// Itens do menu
const char *item_login[2] = {
    "-> REALIZAR LOGIN <-",
    "Realizar Login"
};

const char *item_exit[2] = {
    "-> SAIR.. <-",
    "Sair.."
};

// Função para obter o tamanho da string
int str_len(const char* str) {
    int size = 0;
    while (*str++) ++size;
    return size;
}

// Tamanho do logo
int logo_h_size = sizeof(menu_logo) / sizeof(menu_logo[0]);

// Função para obter o tamanho do logo em largura
int get_logo_w_size(void) {
    int logo_w_size = 1;
    for (int i = 0; i < logo_h_size; i++) {
        int len = str_len(menu_logo[i]);
        if (len > logo_w_size) {
            logo_w_size = len;
        }
    }
    return logo_w_size;
}

void inicializarCurses() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_CYAN, COLOR_BLACK);
    init_pair(5, COLOR_BLUE, COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
}

void finalizarCurses() {
    endwin();
}

void exibirLogo() {
    clear();
    int logo_width = get_logo_w_size();
    int start_x = (COLS - logo_width) / 2;

    for (int i = 0; i < logo_h_size; i++) {
        attron(COLOR_PAIR(i % 6 + 1));
        mvprintw(2 + i, start_x, menu_logo[i]);
        attroff(COLOR_PAIR(i % 6 + 1));
    }

    refresh();
}

int validarLogin(const char *username, const char *password) {
    for (unsigned int i = 0; i < NUM_USUARIOS; i++) {
        if (strcmp(usuarios[i].username, username) == 0 &&
            strcmp(usuarios[i].password, password) == 0) {
            return usuarios[i].tipoUsuario;
        }
    }
    return 0;
}

void exibirMensagem(const char *mensagem) {
    mvprintw(15, (COLS - str_len(mensagem)) / 2, "%s", mensagem);
    refresh();
    getch();
}

int fazerLogin() {
    char username[USERNAME_MAX_LENGTH];
    char password[PASSWORD_MAX_LENGTH];

    while (1) {
        clear();
        exibirLogo();
        mvprintw(14, (COLS - 28) / 2, "Digite o nome de usuario: ");
        echo();
        getstr(username);
        noecho();

        if (strlen(username) == 0) {
            exibirMensagem("Usuario nao pode estar vazio.");
            continue;
        }

        mvprintw(15, (COLS - 28) / 2, "Digite a senha: ");
        int i = 0;
        while (1) {
            int ch = getch();
            if (ch == '\n') {
                password[i] = '\0';
                break;
            } else if ((ch == 8 || ch == KEY_BACKSPACE) && i > 0) {
                i--;
                mvdelch(15, (COLS - 28) / 2 + 14 + i);
            } else if (i < PASSWORD_MAX_LENGTH - 1) {
                password[i++] = ch;
                mvprintw(15, (COLS - 28) / 2 + 14 + i - 1, "*");
            }
        }

        if (strlen(password) == 0) {
            exibirMensagem("Senha nao pode estar vazia.");
            continue;
        }

        int tipoUsuario = validarLogin(username, password);
        if (tipoUsuario) {
            clear();
            exibirLogo();
            mvprintw(15, (COLS - 28) / 2, "Login realizado com sucesso!");
            mvprintw(16, (COLS - 28) / 2, "Aperte a tecla [ Enter ] !");
            refresh();
            getch();
            return tipoUsuario;
        } else {
            exibirMensagem("Nome de usuario ou senha incorretos. Tente novamente.");
        }
    }
}

void exibirMenuPrincipalLogin() {
    int menu_item = 0;

    while (1) {
        clear();
        exibirLogo();
        int h, w;
        getmaxyx(stdscr, h, w);

        // Exibir opções de menu
        int select_login = menu_item == 0 ? 0 : 1;
        mvprintw(h / 2 - logo_h_size + 9, w / 2 - str_len(item_login[select_login]) / 2, item_login[select_login]);

        int select_exit = menu_item == 1 ? 0 : 1;
        mvprintw(h / 2 - logo_h_size + 11, w / 2 - str_len(item_exit[select_exit]) / 2, item_exit[select_exit]);

        // Dicas de navegação
        mvprintw(h - 2, 0, "Use as setas para navegar e Enter para selecionar.");

        refresh();
        int key_pressed = getch();

        if (key_pressed == KEY_UP) {
            menu_item = (menu_item - 1 + NUM_MENU_ITEMS) % NUM_MENU_ITEMS;
        } else if (key_pressed == KEY_DOWN) {
            menu_item = (menu_item + 1) % NUM_MENU_ITEMS;
        } else if (key_pressed == '\n') {
            if (menu_item == 0) { // Opção de login
                int tipoUsuario = fazerLogin(); // Tentei o login

                // Redirecionar com base no tipo de usuário
                if (tipoUsuario == 1) { // Administrador
                    finalizarCurses(); // Finaliza o modo curses
                    menuAdm(); // Chama o menu principal para administrador
                    return; // Sai da função para não entrar em loop
                } else if (tipoUsuario == 2) { // Usuário comum
                    finalizarCurses(); // Finaliza o modo curses
                    gerenciarVendas(); // Chama o gerenciamento de vendas
                    return; // Sai da função
                } else { // Caso não reconhecido
                    printw("Tipo de usuário desconhecido. Tente novamente.\n");
                    getch(); // Espera uma tecla para continuar
                }
            } else if (menu_item == 1) { // Opção de sair
                sair(); // Chama a função para sair
                return; // Sai da função
            }
        }
    }
}

void sair() {
    clear();
    mvprintw(10, (COLS - 30) / 2, "Saindo do sistema...");
    refresh();
    napms(2000); // Espera por 2 segundos (2000 milissegundos)
    finalizarCurses();
    exit(0);
}
