#include "store.h"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>

#define DELIM_CHAR ','

Item Store::parse_line(const std::string& line) const {
    std::stringstream ss(line);
    std::string word;  // temporary string to hold extracted data
    Item new_item;

    std::getline(ss, word, DELIM_CHAR);
    new_item.code = static_cast<ItemCode>(std::stoi(word, nullptr, 16));  // hexadecimal to decimal

    std::getline(ss, new_item.name, DELIM_CHAR);

    std::getline(ss, word, DELIM_CHAR);
    new_item.stock = static_cast<uint16_t>(std::stoi(word));

    std::getline(ss, word, DELIM_CHAR);
    new_item.buy_price = static_cast<uint16_t>(std::stoi(word));

    std::getline(ss, word);  // read until the end, not until next DELIM_CHAR
    new_item.sell_price = static_cast<uint16_t>(std::stoi(word));

    return new_item;
}

Store::Store(const std::string& file_path) {
    std::ifstream file(file_path);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file from path: " + file_path);
    }

    std::string line;

    while (std::getline(file, line)) {
        if (line.empty())
            continue;

        items.push_back(parse_line(line));
    }

    std::sort(items.begin(), items.end(),
              [](const Item& a, const Item& b) { return a.name < b.name; });
}

const std::vector<Item>& Store::get_items() const { return items; }

uint16_t Store::get_buy_price(ItemCode code) const {
    auto it = std::find_if(items.begin(), items.end(),
                           [code](const Item& item) { return item.code == code; });

    if (it != items.end())
        return it->buy_price;

    throw std::runtime_error("The item is not available in the Store");
}

uint16_t Store::get_sell_price(ItemCode code) const {
    auto it = std::find_if(items.begin(), items.end(),
                           [code](const Item& item) { return item.code == code; });

    if (it != items.end())
        return it->sell_price;

    throw std::runtime_error("The item is not available in the Store");
}

void Store::add_item(ItemCode code) {
    auto it = std::find_if(items.begin(), items.end(),
                           [code](const Item& item) { return item.code == code; });

    if (it != items.end()) {
        it->stock++;
        return;
    }

    throw std::runtime_error("The item could not be added to the Store");
}

void Store::remove_item(ItemCode code) {
    auto it = std::find_if(items.begin(), items.end(), [code](const Item& item) {
        return item.code == code && item.stock > 0;
    });

    if (it != items.end()) {
        it->stock--;
        return;
    }

    throw std::runtime_error("The item could not be removed from the Store");
}

bool Store::has_item(ItemCode code) const {
    return std::any_of(items.begin(), items.end(),
                       [code](const Item& item) { return item.code == code && item.stock > 0; });
}
