#include "game.h"

#include <utility>
#include <vector>

Game::Game(const std::string& file_path): player(), store(file_path) {}

const std::vector<Item>& Game::get_store_items() const { return store.get_items(); }

const std::vector<std::pair<ItemCode, uint16_t>>& Game::get_inventory() const {
    return player.get_inventory();
}

uint16_t Game::get_gold() const { return player.get_gold(); }

BuyResult Game::process_buy(ItemCode item_code) {
    if (!store.has_item(item_code)) {
        return BuyResult::NO_STOCK;
    }

    uint16_t buy_price = store.get_buy_price(item_code);

    if (!player.has_enough_gold(buy_price)) {
        return BuyResult::NOT_ENOUGH_GOLD;
    }

    player.remove_gold(buy_price);
    store.remove_item(item_code);
    player.add_item(item_code);

    return BuyResult::SUCCESS;
}

SellResult Game::process_sell(ItemCode item_code) {
    if (!player.has_item(item_code)) {
        return SellResult::ITEM_NOT_IN_INVENTORY;
    }

    uint16_t sell_price = store.get_sell_price(item_code);

    player.remove_item(item_code);
    store.add_item(item_code);
    player.add_gold(sell_price);

    return SellResult::SUCCESS;
}
