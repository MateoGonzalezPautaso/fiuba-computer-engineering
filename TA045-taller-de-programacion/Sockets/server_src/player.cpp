#include "player.h"

#include <algorithm>
#include <stdexcept>

Player::Player(): gold(500) {}

uint16_t Player::get_gold() const { return this->gold; }

void Player::add_gold(uint16_t amount) { this->gold += amount; }

void Player::remove_gold(uint16_t amount) {
    if (amount > this->gold) {
        throw std::runtime_error("Not enough gold available.");  // just in case of underflow
    }
    this->gold -= amount;
}

const std::vector<std::pair<ItemCode, uint16_t>>& Player::get_inventory() const {
    return this->inventory;
}

void Player::add_item(ItemCode code) {
    auto it = std::find_if(inventory.begin(), inventory.end(),
                           [code](const auto& pair) { return pair.first == code; });

    if (it != inventory.end()) {
        it->second++;
    } else {
        inventory.push_back({code, 1});
    }
}

void Player::remove_item(ItemCode code) {
    auto it = std::find_if(inventory.begin(), inventory.end(),
                           [code](const auto& pair) { return pair.first == code; });

    if (it != inventory.end()) {
        it->second--;

        if (it->second == 0)
            inventory.erase(it);
    }
}

bool Player::has_item(ItemCode code) const {
    return std::any_of(inventory.begin(), inventory.end(),
                       [code](const auto& pair) { return pair.first == code && pair.second > 0; });
}

bool Player::has_enough_gold(uint16_t amount) const { return this->gold >= amount; }
