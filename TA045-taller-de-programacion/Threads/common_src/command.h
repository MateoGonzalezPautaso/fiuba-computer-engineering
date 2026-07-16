#ifndef COMMAND_H
#define COMMAND_H

#include <cstdint>
#include <optional>

#include "npc_config.h"

enum class Command : uint8_t { READ = 0x10, DEFEAT = 0x0A, EXIT = 0x00, INVALID = 0xFF };

struct CommandInfo {
    Command type = Command::INVALID;

    // only exists when Command is DEFEAT
    std::optional<NPCCode> npc_code;

    // only exists when Command is READ
    std::optional<uint16_t> n_msg;
};

#endif
