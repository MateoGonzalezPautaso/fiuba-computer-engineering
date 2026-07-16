#ifndef PLAYER_COMMAND_H
#define PLAYER_COMMAND_H

#include <string>

#include "../common_src/command.h"

struct PlayerCommand {
    std::string username;
    CommandInfo info;

    PlayerCommand(const std::string& username, const CommandInfo& cmd_info):
            username(username), info(cmd_info) {}
};

#endif
