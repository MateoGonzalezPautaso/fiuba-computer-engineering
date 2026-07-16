#include "client_parser.h"

#include "../common_src/npc_config.h"

CommandInfo Parser::parse_input(const std::string& line, const NPCConfig& npc_config) const {
    CommandInfo cmd_info;
    cmd_info.type = Command::INVALID;

    std::stringstream ss(line);
    std::string action;

    // Reads the first word -> Command type
    if (!(ss >> action))
        return cmd_info;

    if (action == "Exit") {
        cmd_info.type = Command::EXIT;
    } else if (action == "Read") {
        parse_read(cmd_info, ss);
    } else if (action == "Defeat") {
        parse_defeat(cmd_info, ss, npc_config);
    }

    return cmd_info;
}

void Parser::parse_read(CommandInfo& cmd_info, std::stringstream& ss) const {
    uint16_t n;

    // Reads the number after "Read"
    if (ss >> n) {
        cmd_info.n_msg = n;
        cmd_info.type = Command::READ;
    }
}

void Parser::parse_defeat(CommandInfo& cmd_info, std::stringstream& ss,
                          const NPCConfig& npc_config) const {
    std::string npc_name;

    // Reads the name after "Defeat"
    if (ss >> npc_name) {
        try {
            NPCCode code = npc_config.map_name_code(npc_name);
            cmd_info.npc_code = code;
            cmd_info.type = Command::DEFEAT;
        } catch (const std::invalid_argument&) {
            // cmd_info.type is INVALID by default
        }
    }
}
