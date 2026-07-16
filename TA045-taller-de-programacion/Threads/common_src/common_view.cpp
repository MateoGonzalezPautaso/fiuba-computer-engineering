#include "common_view.h"

#include <iostream>
#include <sstream>

#include "npc_config.h"

void CommonView::show_event(const GameEvent& event, const NPCConfig& npc_config) const {
    std::string npc_name = npc_config.map_code_name(event.npc_code);

    if (event.type == EventType::NPC_DEFEATED) {
        // player_name safe to use because event is NPC_DEFEATED
        std::string player_name = event.player_name.value();
        show_npc_defeat(player_name, npc_name);
    } else if (event.type == EventType::NPC_APPEARED) {
        show_npc_appearance(npc_name);
    }
}

void CommonView::show_npc_defeat(const std::string& player_name,
                                 const std::string& npc_name) const {
    std::ostringstream oss;
    oss << player_name << " defeated " << npc_name << std::endl;
    std::cout << oss.str();
}

void CommonView::show_npc_appearance(const std::string& npc_name) const {
    std::ostringstream oss;
    oss << "A new " << npc_name << " has appeared" << std::endl;
    std::cout << oss.str();
}
