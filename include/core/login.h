#ifndef LOGIN_H
#define LOGIN_H
#ifndef MOUSE_MOVED
#define MOUSE_MOVED (Mouse_status.changes & PDC_MOUSE_MOVED)
#endif

// Definição de constantes para tamanhos de dados
#define USERNAME_MAX_LENGTH 50
#define PASSWORD_MAX_LENGTH 50

// Estrutura para armazenar informações de login do usuário
typedef struct {
    char username[USERNAME_MAX_LENGTH]; // Nome de usuário
    char password[PASSWORD_MAX_LENGTH]; // Senha do usuário
    int tipoUsuario;                     // 1 para admin, 2 USUARIO
} UsuarioLogin;

// Funções para validação e realização de login
/**
 * @brief Valida as credenciais de login do usuário.
 *
 * @param username Nome de usuário a ser validado.
 * @param password Senha a ser validada.
 * @return int Retorna o tipo de usuário se as credenciais forem válidas, 0 caso contrário.
 */
int validarLogin(const char *username, const char *password);

/**
 * @brief Função que realiza o login do usuário.
 *
 * Esta função solicita as credenciais do usuário e verifica se são válidas.
 *
 * @return int Retorna o tipo de usuário após um login bem-sucedido.
 */
int fazerLogin();

/**
 * @brief Inicializa a biblioteca curses.
 *
 * Esta função configura a tela e as opções de entrada para uso com curses.
 */
void inicializarCurses();

/**
 * @brief Finaliza a biblioteca curses.
 *
 * Esta função restaura o terminal ao seu estado original.
 */
void finalizarCurses();

#endif // LOGIN_H
