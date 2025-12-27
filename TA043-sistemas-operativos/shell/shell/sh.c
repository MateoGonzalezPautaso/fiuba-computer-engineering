#include "defs.h"
#include "types.h"
#include "readline.h"
#include "runcmd.h"
#include <unistd.h>

char prompt[PRMTLEN] = { 0 };

void preparar_handler(void);
int write_number(int n);
void sigchild_handler(int signum);

// runs a shell command
static void
run_shell()
{
	char *cmd;

	while ((cmd = read_line(prompt)) != NULL)
		if (run_cmd(cmd) == EXIT_SHELL)
			return;
}

// initializes the shell
// with the "HOME" directory
static void
init_shell()
{
	char buf[BUFLEN] = { 0 };
	char *home = getenv("HOME");

	if (chdir(home) < 0) {
		snprintf(buf, sizeof buf, "cannot cd to %s ", home);
		perror(buf);
	} else {
		snprintf(prompt, sizeof prompt, "(%s)", home);
	}
}

int
write_number(int n)
{
	char buffer[12];
	int i = 11;
	buffer[i] = '\0';

	if (n == 0) {
		char c = '0';
		return write(1, &c, 1);
	}

	while (n > 0) {
		i--;
		buffer[i] = (n % 10) + '0';
		n /= 10;
	}

	return write(1, &buffer[i], 11 - i);
}


void
sigchild_handler(int signum)
{
	pid_t pid;
	int status;

	// Espera por los procesos con el mismo pgid que el padre. Como se
	// cambiaron los pgid de los foreground, solo espera por backgrouds
	pid = waitpid(0, &status, WNOHANG);

	if (pid > 0) {
		char parte1[] = "PID: ";
		char parte2[] = ", STATUS: ";
		char parte3[] = "\n";

		int s1 = write(STDOUT_FILENO, parte1, strlen(parte1));
		int s2 = write_number(pid);
		int s3 = write(STDOUT_FILENO, parte2, strlen(parte2));
		int s4 = write_number(status);
		int s5 = write(STDOUT_FILENO, parte3, strlen(parte3));

		if ((s1 | s2 | s3 | s4 | s5) < 0) {
			perror("Error en write");
			exit(-1);
		}
	}
}

void
preparar_handler()
{
	struct sigaction estructura;
	memset(&estructura, 0, sizeof(struct sigaction));

	estructura.sa_handler = sigchild_handler;
	estructura.sa_flags = SA_RESTART;

	if (sigaction(SIGCHLD, &estructura, NULL) != 0) {
		perror("Error al ejecutar sigaction");
		exit(-1);
	}
}

int
main(void)
{
	init_shell();
	preparar_handler();


	run_shell();

	return 0;
}
