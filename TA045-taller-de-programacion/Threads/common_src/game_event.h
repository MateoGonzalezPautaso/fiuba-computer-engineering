#ifndef GAME_EVENT_H
#define GAME_EVENT_H

#include <optional>
#include <string>

#include "npc_config.h"

enum class EventType : uint8_t { NPC_DEFEATED = 0x00, NPC_APPEARED = 0x01, NONE = 0xFF };

struct GameEvent {
    EventType type = EventType::NONE;
    NPCCode npc_code = NPCCode::INVALID;

    // only exists when EventType is NPC_DEFEATED
    std::optional<std::string> player_name;
};

#endif
