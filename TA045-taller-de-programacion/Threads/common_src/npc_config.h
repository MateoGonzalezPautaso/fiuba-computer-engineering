#ifndef NPC_CONFIG_H
#define NPC_CONFIG_H

#include <cstdint>
#include <map>
#include <string>

enum class NPCCode : uint8_t {
    ORC = 0x01,
    WOLF = 0x02,
    DRAGON = 0x03,
    SKELETON = 0x04,
    INVALID = 0xFF
};

class NPCConfig {
public:
    NPCConfig();

    NPCCode map_name_code(const std::string& name) const;
    std::string map_code_name(NPCCode code) const;
    uint8_t map_code_ticks(NPCCode code) const;

private:
    std::map<std::string, NPCCode> name_to_code;
    std::map<NPCCode, std::string> code_to_name;
    std::map<NPCCode, uint8_t> code_to_ticks;
};

#endif
