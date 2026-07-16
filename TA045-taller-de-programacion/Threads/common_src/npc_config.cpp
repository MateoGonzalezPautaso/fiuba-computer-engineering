#include "npc_config.h"

#include <stdexcept>

#define ORC_TICKS 15
#define WOLF_TICKS 10
#define DRAGON_TICKS 25
#define SKELETON_TICKS 15

NPCConfig::NPCConfig():
        name_to_code({{"Orc", NPCCode::ORC},
                      {"Wolf", NPCCode::WOLF},
                      {"Dragon", NPCCode::DRAGON},
                      {"Skeleton", NPCCode::SKELETON}}),
        code_to_name({{NPCCode::ORC, "Orc"},
                      {NPCCode::WOLF, "Wolf"},
                      {NPCCode::DRAGON, "Dragon"},
                      {NPCCode::SKELETON, "Skeleton"}}),
        code_to_ticks({{NPCCode::ORC, ORC_TICKS},
                       {NPCCode::WOLF, WOLF_TICKS},
                       {NPCCode::DRAGON, DRAGON_TICKS},
                       {NPCCode::SKELETON, SKELETON_TICKS}}) {}

NPCCode NPCConfig::map_name_code(const std::string& name) const {
    auto it = name_to_code.find(name);

    if (it != name_to_code.end())
        return it->second;

    throw std::invalid_argument("NPC name not recognized: " + name);
}

std::string NPCConfig::map_code_name(NPCCode code) const {
    auto it = code_to_name.find(code);

    if (it != code_to_name.end())
        return it->second;

    throw std::invalid_argument("NPC code not recognized");
}

uint8_t NPCConfig::map_code_ticks(NPCCode code) const {
    auto it = code_to_ticks.find(code);

    if (it != code_to_ticks.end())
        return it->second;

    throw std::invalid_argument("NPC ticks not found");
}
