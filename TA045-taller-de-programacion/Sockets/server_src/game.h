#ifndef GAME_H
#define GAME_H

#include <string>
#include <utility>
#include <vector>

#include "game_results.h"
#include "player.h"
#include "store.h"

class Game {
private:
    Player player;
    Store store;

public:
    explicit Game(const std::string& file_path);
    const std::vector<Item>& get_store_items() const;
    const std::vector<std::pair<ItemCode, uint16_t>>& get_inventory() const;
    uint16_t get_gold() const;
    BuyResult process_buy(ItemCode item_code);
    SellResult process_sell(ItemCode item_code);
};

#endif
