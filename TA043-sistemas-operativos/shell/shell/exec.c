#include "exec.h"
#include <string.h>
#include <wait.h>

// sets "key" with the key part of "arg"
// and null-terminates it
//
// Example:
//  - KEY=value
//  arg = ['K', 'E', 'Y', '=', 'v', 'a', 'l', 'u', 'e', '\0']
//  key = "KEY"
//
static void
get_environ_key(char *arg, char *key)
{
	int i;
	for (i = 0; arg[i] != '='; i++)
		key[i] = arg[i];

	key[i] = END_STRING;
}

// sets "value" with the value part of "arg"
// and null-terminates it
// "idx" should be the index in "arg" where "=" char
// resides
//
// Example:
//  - KEY=value
//  arg = ['K', 'E', 'Y', '=', 'v', 'a', 'l', 'u', 'e', '\0']
//  value = "value"
//
static void
get_environ_value(char *arg, char *value, int idx)
{
	size_t i, j;
	for (i = (idx + 1), j = 0; i < strlen(arg); i++, j++)
		value[j] = arg[i];

	value[j] = END_STRING;
}

// sets the environment variables received
// in the command line
//
// Hints:
// - use 'block_contains()' to
// 	get the index where the '=' is
// - 'get_environ_*()' can be useful here
static void
set_environ_vars(char **eargv, int eargc)
{
	char *key;
	char *value;

	for (int i = 0; i < eargc; i++) {
		int pos_separador = block_contains(eargv[i], '=');
		key = malloc(pos_separador + 1);
		value = malloc(strlen(eargv[i]) - pos_separador);

		if (!key || !value) {
			free(key);
			free(value);
			continue;
		}

		get_environ_key(eargv[i], key);
		get_environ_value(eargv[i], value, pos_separador);
		setenv(key, value, 1);

		free(key);
		free(value);
	}
}

// opens the file in which the stdin/stdout/stderr
// flow will be redirected, and returns
// the file descriptor
//
// Find out what permissions it needs.
// Does it have to be closed after the execve(2) call?
//
// Hints:
// - if O_CREAT is used, add S_IWUSR and S_IRUSR
// 	to make it a readable normal file
static int
open_redir_fd(char *file, int flags)
{
	// Si O_CREAT esta en las flags, le pasa el mode. Sino solo
	int fd;

	if ((flags & O_CREAT) > 0) {
		// Si O_CREAT estaba en las flags entra al if. Sino el flags AND O_CREAT = 0
		fd = open(file,
		          flags,
		          S_IRUSR | S_IWUSR);  // Prendes los bits de S_IRUSR y S_IWUSR.
	} else {
		// O_CREAT no estaba en las flags
		fd = open(file, flags);
	}

	if (fd < 0) {
		perror("Error abriendo archivo de redireccion");
		exit(-1);
	}

	return fd;
}

// executes a command - does not return
//
// Hint:
// - check how the 'cmd' structs are defined
// 	in types.h
// - casting could be a good option
void
exec_cmd(struct cmd *cmd)
{
	// To be used in the different cases
	struct execcmd *e;
	struct backcmd *b;
	struct execcmd *r;
	struct pipecmd *p;

	switch (cmd->type) {
	case EXEC:
		e = (struct execcmd *) cmd;

		set_environ_vars(e->eargv, e->eargc);
		execvp(e->argv[0], e->argv);

		perror("Error en exec_cmd en execvp()\n");
		free_command(cmd);
		exit(-1);
		break;

	case BACK: {
		// runs a command in background
		b = (struct backcmd *) cmd;
		exec_cmd(b->c);
		exit(-1);
	}

	case REDIR: {
		// changes the input/output/stderr flow
		//
		// To check if a redirection has to be performed
		// verify if file name's length (in the execcmd struct)
		// is greater than zero
		//
		r = (struct execcmd *) cmd;

		if (strlen(r->out_file) > 0) {
			// Redireccion stdout
			int destino = open_redir_fd(r->out_file,
			                            O_CREAT | O_WRONLY | O_TRUNC);
			dup2(destino, STDOUT_FILENO);
			close(destino);
		}

		if (strlen(r->in_file) > 0) {
			// Redireccion del stdin
			int fuente = open_redir_fd(r->in_file, O_RDONLY);
			dup2(fuente, STDIN_FILENO);
			close(fuente);
		}

		if (strlen(r->err_file) > 0) {
			// Redireccion stderr
			if (strcmp(r->err_file, "&1") == 0) {
				// Redirigir el stderr al stdout
				dup2(STDOUT_FILENO, STDERR_FILENO);
			} else {
				int destino = open_redir_fd(r->err_file,
				                            O_CREAT | O_WRONLY |
				                                    O_TRUNC);
				dup2(destino, STDERR_FILENO);
				close(destino);
			}
		}

		r->type = EXEC;
		exec_cmd((struct cmd *) r);

		break;
	}

	case PIPE: {
		// pipes two commands

		p = (struct pipecmd *) cmd;
		struct cmd *proceso_izquierdo = p->leftcmd;
		struct cmd *proceso_derecho = p->rightcmd;

		int fds[2];

		if (pipe(fds) < 0) {
			perror("Error en el pipe()");
			exit(-1);
		}

		pid_t primer_fork = fork();

		if (primer_fork < 0) {
			perror("Fallo en fork");
			close(fds[0]);
			close(fds[1]);
			exit(-1);
		} else if (primer_fork == 0) {
			// Proceso izquierdo
			close(fds[0]);  // No lee en el pipe
			dup2(fds[1],
			     STDOUT_FILENO);  // El stdout se redirige al extremo de escritura del pipe
			close(fds[1]);

			// Se cambia el pgid porque hereda el del padre, como es foreground deberia ser unico.
			setpgid(primer_fork, 0);

			exec_cmd(proceso_izquierdo);
		}


		int segundo_fork = fork();
		if (segundo_fork < 0) {
			perror("Fallo en fork");
			close(fds[0]);
			close(fds[1]);
			exit(-1);
		} else if (segundo_fork == 0) {
			// Proceso derecho
			close(fds[1]);  // No escribe en el pipe
			dup2(fds[0], STDIN_FILENO);
			close(fds[0]);
			setpgid(segundo_fork, 0);
			exec_cmd(proceso_derecho);
		}


		close(fds[0]);
		close(fds[1]);

		waitpid(primer_fork, NULL, 0);   // Espera al proceso izquierdo
		waitpid(segundo_fork, NULL, 0);  // Espera al proceso derecho

		free_command(parsed_pipe);
		exit(0);
		break;
	}
	}
}
