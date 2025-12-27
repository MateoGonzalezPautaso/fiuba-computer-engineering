#include "builtin.h"

extern char prompt[PRMTLEN];
extern int status;

// returns true if the 'exit' call
// should be performed
//
// (It must not be called from here)
int
exit_shell(char *cmd)
{
	return strcmp(cmd, "exit") == 0 ? true : false;
}

// returns true if "chdir" was performed
//  this means that if 'cmd' contains:
// 	1. $ cd directory (change to 'directory')
// 	2. $ cd (change to $HOME)
//  it has to be executed and then return true
//
//  Remember to update the 'prompt' with the
//  	new directory.
//
// Examples:
//  1. cmd = ['c','d', ' ', '/', 'b', 'i', 'n', '\0']
//  2. cmd = ['c','d', '\0']
int
cd(char *cmd)
{
	if (cmd[0] == 'c' && cmd[1] == 'd') {
		if (cmd[2] == '\0') {
			char *home = getenv("HOME");

			if (chdir(home) < 0) {
				perror("Error en ir a HOME");
				status = 1;  // 1 igual que bash
			}
			snprintf(prompt, sizeof(prompt), "(%s)", home);
			return true;
		} else if (cmd[2] == ' ' && cmd[3] != 0) {
			if (chdir(cmd + 3) < 0) {
				perror("Directorio no existe");
				status = 1;  // Igual que bash
			}
			char *nuevo_prompt = getcwd(NULL, 0);
			snprintf(prompt, sizeof(prompt), "(%s)", nuevo_prompt);
			free(nuevo_prompt);
			return true;
		}
	}

	return false;
}

// returns true if 'pwd' was invoked
// in the command line
//
// (It has to be executed here and then
// 	return true)
int
pwd(char *cmd)
{
	if (strcmp(cmd, "pwd") == 0) {
		char *directorio_actual = getcwd(NULL, 0);
		if (!directorio_actual)
			return false;

		printf("%s\n", directorio_actual);
		free(directorio_actual);

		return true;
	}

	return false;
}

// returns true if `history` was invoked
// in the command line
//
// (It has to be executed here and then
// 	return true)

int
history(char *cmd)
{
	// Your code here

	return 0;
}
