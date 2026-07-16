#include <fstream>
#include <iostream>
#include <string>

#include "wordscounter.h"

#define SUCCESS 0
#define ERROR 1
#define FILE_ARG argv[1]

int main(int argc, const char* argv[]) {
    /*
        counter and input are small, fised-size objects
        it is better to use them as stack objects
        counter only holds a single size_t words
        input is always the same size regardless of the file
    */

    Wordscounter counter;

    if (argc > 1) {
        std::ifstream input;
        input.open(FILE_ARG);

        // invalid file
        if (!input) {
            return ERROR;
        }

        counter.process(input);

    } else {
        counter.process(std::cin);
    }

    size_t words = counter.get_words();
    std::cout << words << std::endl;

    return SUCCESS;
}
