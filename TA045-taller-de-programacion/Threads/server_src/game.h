#ifndef GAME_H
#define GAME_H

#include <map>
#include <optional>
#include <string>
#include <vector>

#include "../common_src/game_event.h"
#include "../common_src/npc_config.h"

#include "npc.h"

class Game {
public:
    explicit Game(const NPCConfig& npc_config);

    std::vector<GameEvent> run_one_tick();

    std::optional<GameEvent> defeat_npc(const std::string& player_name, NPCCode npc_code);

private:
    const NPCConfig& npc_config;
    std::map<NPCCode, NPC> npcs;
};

#endif
