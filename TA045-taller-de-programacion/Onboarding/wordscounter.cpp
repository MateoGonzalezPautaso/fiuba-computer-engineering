#include "wordscounter.h"

#include <fstream>
#include <string>

// cstring is the C++ way of including C headers
#include <cstring>

#define DELIM_WORDS " ,.;:\n"


Wordscounter::Wordscounter() {
    this->words = 0;
    this->current_state = STATE_WAITING;
}

size_t Wordscounter::get_words() { return this->words; }

void Wordscounter::process(std::istream& text_file) {
    do {
        char c = text_file.get();
        change_state(c);
    } while (current_state != STATE_END);
}

void Wordscounter::change_state(char c) {
    // works directly with enum wc_state values
    if (current_state == STATE_WAITING) {
        if (c == EOF) {
            current_state = STATE_END;
        } else if (strchr(DELIM_WORDS, c) == NULL) {
            current_state = STATE_PROCESSING;
        }

    } else if (current_state == STATE_PROCESSING) {
        if (c == EOF) {
            current_state = STATE_END;
            words++;
        } else if (strchr(DELIM_WORDS, c) != NULL) {
            words++;
            current_state = STATE_WAITING;
        }
    }
}
