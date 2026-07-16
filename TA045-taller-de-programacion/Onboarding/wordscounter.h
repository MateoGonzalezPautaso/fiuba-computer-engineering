#ifndef __WORDSCOUNTER_H__
#define __WORDSCOUNTER_H__

#include <fstream>

// Tipo wordscounter_t: procesa cantidad de palabras dentro de un archivo.
class Wordscounter {

public:
    Wordscounter();

    // Retorna la cantidad de palabras procesadas
    size_t get_words();

    // Procesa el contenido de text_file, contando sus palabras.
    void process(std::istream& text_file);


private:
    size_t words;

    // Compara el caracter leído c y define el nuevo estado. From returning char to void due to enum
    void change_state(char c);

    // Different states for the word counting process
    enum wc_state {
        STATE_WAITING,     // 0: waiting for a word
        STATE_PROCESSING,  // 1: inside the word counting
        STATE_END          // 2: end of file
    };

    // Tracks the current state of the word counting process
    wc_state current_state;
};

#endif
