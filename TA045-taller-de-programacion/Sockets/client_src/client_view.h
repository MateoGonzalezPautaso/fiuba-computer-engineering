#ifndef CLIENT_VIEW_H
#define CLIENT_VIEW_H

#include <vector>

#include "../common_src/item.h"

class ClientView {
public:
    void show_store(const std::vector<Item>& items) const;
    void show_inventory(uint16_t gold, const std::vector<Item>& items) const;
    void show_invalid_operation() const;
    void show_invalid_object_error() const;
};

#endif
