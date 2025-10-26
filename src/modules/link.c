#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

// Função para definir a cor do texto e fundo no console
void definirCorConsole(int texto, int fundo) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, texto | (fundo << 4));
}

// Função para ler uma string do usuário
void lerStringBalanca(char *str, int maxLen, const char *prompt) {
    printf("%s", prompt);
    fgets(str, maxLen, stdin);
    str[strcspn(str, "\n")] = 0; // Remove o newline
}

// Função para definir a cor específica para a balança
void definirCorBalanca(int texto, int fundo) {
    definirCorConsole(texto, fundo);
}

// Função para mostrar uma mensagem de boas-vindas
void mostrarBoasVindasBalanca() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    system("cls"); // Limpa a tela do console
    definirCorBalanca(12, 0); // Azul escuro
    printf("+==  ::##  Bem-Vindo  ##::  ====  : Ver Beta 1.5.0 :==+\n");
    definirCorBalanca(12, 0);
    printf("|  _   _            _   _ _____           _   _       |\n");
    definirCorBalanca(6, 0);
    printf("| | | | | ___  _ __| |_(_)  ___| __ _   _| |_(_)      |\n");
    definirCorBalanca(14, 0);
    printf("| | |_| |/ _ \\| '__| __| | |_ | '__| | | | __| |      |\n");
    definirCorBalanca(10, 0);
    printf("| |  _  | (_) | |  | |_| |  _|| |  | |_| | |_| |      |\n");
    definirCorBalanca(9, 0);
    printf("| |_| |_|\\___/|_|   \\__|_|_|  |_|   \\__,_|\\__|_|      |\n");
    definirCorBalanca(12, 0);
    printf("+-----------------------------------------------------+\n");
    printf("| Data: %02d/%02d/%04d                                    |\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    printf("| Hora: %02d:%02d:%02d                                      |\n", tm.tm_hour, tm.tm_min, tm.tm_sec);
    printf("+---------------------:: Solutions Copyright 2024  :: +\n\n");
    definirCorBalanca(15, 0);
}
