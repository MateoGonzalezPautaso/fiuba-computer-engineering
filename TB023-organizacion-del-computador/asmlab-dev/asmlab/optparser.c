#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <argp.h>
#include <argz.h>
#include "optparser.h"

int can_create_file(const char *file_name);
int is_valid_test(char *word);

struct arguments
{
    char *argz;
    size_t argz_len;
};

test_run_t test_run = {{0}, NULL};

const char *valid_tests_str[] = {
    "int",
    "string",
    "array",
    "list",
    "card",
    "game"};

static int
parse_opt(int key, char *arg, struct argp_state *state)
{
    struct arguments *a = state->input;
    size_t count;

    switch (key)
    {
    case 'o':
        test_run.file = arg;
        if (!can_create_file(test_run.file))
        {
            argp_failure(state, 1, 0, "Invalid input file");
        }
        break;
    case ARGP_KEY_ARG:
        argz_add(&a->argz, &a->argz_len, arg);
        break;
    case ARGP_KEY_INIT:
        a->argz = 0;
        a->argz_len = 0;
        break;
    case ARGP_KEY_END:
        count = argz_count(a->argz, a->argz_len);
        if (count > (sizeof(test_run.testcases) / sizeof(test_run.testcases[0])))
            argp_failure(state, 1, 0, "Demasiados argumentos");
        if (count < 1)
            argp_failure(state, 1, 0, "Faltan argumentos");

        break;
    }
    return 0;
}

// Validate if the file can be created
int can_create_file(const char *file_name)
{
    FILE *file = fopen(file_name, "w");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Cannot create file %s\n", file_name);
        return 0;
    }
    fclose(file);
    remove(file_name); // Remove the file after creation check
    return 1;
}

// Validate test number
int is_valid_test(char *word)
{
    for (int i = 0; i < GAME_TEST + 1; i++)
    {
        if (strcmp(word, valid_tests_str[i]) == 0)
        {
            return i;
        }
    }
    return -1;
}

void parse_cli(int argc, char **argv)
{
    // default arguments

    test_run.file = NULL;

    struct argp_option options[] = {
        {"output", 'o', "FILE", 0, "Archivo de salida", 0},
        {0}};

    char help_str[200] = "Valores posibles para TESTCASE:";
    for (int i = 0; i < GAME_TEST + 1; i++)
    {
        strcat(strcat(help_str, " "), valid_tests_str[i]);
    }

    struct argp argp = {options, parse_opt, "TESTCASE [TESTCASE]...", help_str};

    struct arguments arguments;

    if (argp_parse(&argp, argc, argv, 0, 0, &arguments) == 0)
    {
        const char *prev = NULL;
        char *word;
        int testcase;

        while ((word = argz_next(arguments.argz, arguments.argz_len, prev)))
        {
            if ((testcase = is_valid_test(word)) == -1)
            {
                fprintf(stderr, "Invalid test name: %s\n", word);
                free(arguments.argz);
                exit(1);
            }
            else
            {
                test_run.testcases[testcase] = true;
            }
            prev = word;
        }
        free(arguments.argz);
    }
}