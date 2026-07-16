#ifndef STORE_H
#define STORE_H

#include <string>
#include <vector>

#include "../common_src/item.h"

class Store {
private:
    std::vector<Item> items;

    Item parse_line(const std::string& line) const;

public:
    explicit Store(const std::string& file_path);

    const std::vector<Item>& get_items() const;

    uint16_t get_buy_price(ItemCode code) const;
    uint16_t get_sell_price(ItemCode code) const;
    void add_item(ItemCode code);
    void remove_item(ItemCode code);
    bool has_item(ItemCode code) const;
};

#endif
