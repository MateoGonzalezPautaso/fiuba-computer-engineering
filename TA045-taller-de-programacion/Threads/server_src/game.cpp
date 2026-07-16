#include "game.h"

#include <string>

Game::Game(const NPCConfig& npc_config): npc_config(npc_config) {
    npcs.emplace(NPCCode::ORC, NPC(npc_config.map_code_ticks(NPCCode::ORC)));
    npcs.emplace(NPCCode::WOLF, NPC(npc_config.map_code_ticks(NPCCode::WOLF)));
    npcs.emplace(NPCCode::DRAGON, NPC(npc_config.map_code_ticks(NPCCode::DRAGON)));
    npcs.emplace(NPCCode::SKELETON, NPC(npc_config.map_code_ticks(NPCCode::SKELETON)));
}

std::vector<GameEvent> Game::run_one_tick() {
    std::vector<GameEvent> appearance_events;

    for (auto& pair: npcs) {
        if (pair.second.tick()) {
            GameEvent event;
            event.type = EventType::NPC_APPEARED;
            event.npc_code = pair.first;
            appearance_events.push_back(event);
        }
    }

    return appearance_events;
}

std::optional<GameEvent> Game::defeat_npc(const std::string& player_name, NPCCode npc_code) {
    auto it = npcs.find(npc_code);

    // only kills the npc if it is found and alive
    if (it != npcs.end() && it->second.is_alive()) {
        it->second.kill();

        GameEvent event;
        event.type = EventType::NPC_DEFEATED;
        event.npc_code = npc_code;
        event.player_name = player_name;
        return event;
    }

    return std::nullopt;
}
