#ifndef LOGIN_H
#define LOGIN_H
#ifndef MOUSE_MOVED
#define MOUSE_MOVED (Mouse_status.changes & PDC_MOUSE_MOVED)
#endif

// Defini��o de constantes para tamanhos de dados
#define USERNAME_MAX_LENGTH 50
#define PASSWORD_MAX_LENGTH 50

// Estrutura para armazenar informa��es de login do usu�rio
typedef struct {
    char username[USERNAME_MAX_LENGTH]; // Nome de usu�rio
    char password[PASSWORD_MAX_LENGTH]; // Senha do usu�rio
    int tipoUsuario;                     // 1 para admin, 2 USUARIO
} UsuarioLogin;

// Fun��es para valida��o e realiza��o de login
/**
 * @brief Valida as credenciais de login do usu�rio.
 *
 * @param username Nome de usu�rio a ser validado.
 * @param password Senha a ser validada.
 * @return int Retorna o tipo de usu�rio se as credenciais forem v�lidas, 0 caso contr�rio.
 */
int validarLogin(const char *username, const char *password);

/**
 * @brief Fun��o que realiza o login do usu�rio.
 *
 * Esta fun��o solicita as credenciais do usu�rio e verifica se s�o v�lidas.
 *
 * @return int Retorna o tipo de usu�rio ap�s um login bem-sucedido.
 */
int fazerLogin();

/**
 * @brief Inicializa a biblioteca curses.
 *
 * Esta fun��o configura a tela e as op��es de entrada para uso com curses.
 */
void inicializarCurses();

/**
 * @brief Finaliza a biblioteca curses.
 *
 * Esta fun��o restaura o terminal ao seu estado original.
 */
void finalizarCurses();

#endif // LOGIN_H
