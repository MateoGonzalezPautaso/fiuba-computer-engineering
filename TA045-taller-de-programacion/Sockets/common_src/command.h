#ifndef COMMAND_H
#define COMMAND_H

#include <cstdint>
#include <optional>
#include <string>

enum class Command : uint8_t {
    STORE = 0x10,
    INVENTORY = 0x20,
    BUY = 0x11,
    SELL = 0x12,
    QUIT = 0x00,
    INVALID = 0xFF
};

struct CommandInfo {
    Command type;

    // only exist when Command is BUY or SELL
    std::optional<std::string> object_name;
    std::optional<uint8_t> item_code;
};

#endif
