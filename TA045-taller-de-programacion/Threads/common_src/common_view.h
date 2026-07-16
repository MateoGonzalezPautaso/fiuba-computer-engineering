#ifndef COMMON_VIEW_H
#define COMMON_VIEW_H

#include <string>

#include "game_event.h"

class CommonView {
public:
    void show_event(const GameEvent& event, const NPCConfig& npc_config) const;

private:
    void show_npc_defeat(const std::string& player_name, const std::string& npc_name) const;
    void show_npc_appearance(const std::string& npc_name) const;
};

#endif
