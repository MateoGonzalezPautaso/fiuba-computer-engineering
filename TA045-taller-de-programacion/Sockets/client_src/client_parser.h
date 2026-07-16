#ifndef CLIENT_PARSER_H
#define CLIENT_PARSER_H

#include <string>

#include "../common_src/command.h"

class Parser {
public:
    CommandInfo parse_input(const std::string& line) const;
};

#endif
