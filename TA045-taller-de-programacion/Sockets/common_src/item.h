#ifndef ITEM_H
#define ITEM_H

#include <cstdint>
#include <string>

enum class ItemCode : uint8_t {
    SWORD = 0x00,
    BOW = 0x11,
    FLUTE = 0x29,
    BRANCH = 0x30,
    ARMOR = 0x44,
    INVALID = 0xFF
};

struct Item {
    ItemCode code = ItemCode::INVALID;
    std::string name = "";
    uint16_t stock = 0;
    uint16_t buy_price = 0;
    uint16_t sell_price = 0;

    // initialize everything due to cpplint and cppcheck
    Item() = default;
};

#endif
