#ifndef OPTPARSER
#define OPTPARSER

#include <stdbool.h>

typedef enum valid_tests
{
    INT_TEST = 0,
    STRING_TEST,
    ARRAY_TEST,
    LIST_TEST,
    CARD_TEST,
    GAME_TEST
} valid_tests_t;

typedef struct test_run_s
{
    bool testcases[GAME_TEST + 1];
    char *file;
} test_run_t;

extern test_run_t test_run;

void parse_cli(int argc, char **argv);

#endif /* OPTPARSER */
