#ifndef PLAYER_H
#define PLAYER_H

#include <cstdint>
#include <utility>
#include <vector>

#include "../common_src/item.h"

class Player {
private:
    uint16_t gold;
    std::vector<std::pair<ItemCode, uint16_t>> inventory;

public:
    Player();

    uint16_t get_gold() const;
    void add_gold(uint16_t amount);
    void remove_gold(uint16_t amount);
    const std::vector<std::pair<ItemCode, uint16_t>>& get_inventory() const;
    void add_item(ItemCode code);
    void remove_item(ItemCode code);
    bool has_item(ItemCode code) const;
    bool has_enough_gold(uint16_t amount) const;
};

#endif
