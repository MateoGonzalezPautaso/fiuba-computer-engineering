#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <string>
#include <utility>
#include <vector>

#include "../common_src/item.h"
#include "../common_src/protocol.h"

class ServerProtocol: public Protocol {
private:
    CommandInfo recv_command_binary();
    CommandInfo recv_command_text();

    void send_store_binary(const std::vector<Item>& items);
    void send_store_text(const std::vector<Item>& items);

    void send_inventory_binary(uint16_t gold, const std::vector<Item>& items_to_send);
    void send_inventory_text(uint16_t gold, const std::vector<Item>& items_to_send);

    std::vector<Item> prepare_inventory(
            const std::vector<std::pair<ItemCode, uint16_t>>& inventory) const;

public:
    ServerProtocol(Socket& skt, bool is_binary);

    std::string recv_username();
    void send_protocol_type();

    CommandInfo recv_command();

    void send_store(const std::vector<Item>& items);
    void send_inventory(uint16_t gold, const std::vector<std::pair<ItemCode, uint16_t>>& inventory);
};

#endif
