#ifndef CLIENT_PARSER_H
#define CLIENT_PARSER_H

#include <sstream>
#include <string>

#include "../common_src/command.h"

class Parser {
public:
    CommandInfo parse_input(const std::string& line, const NPCConfig& npc_config) const;

private:
    void parse_read(CommandInfo& cmd_info, std::stringstream& ss) const;
    void parse_defeat(CommandInfo& cmd_info, std::stringstream& ss,
                      const NPCConfig& npc_config) const;
};

#endif
