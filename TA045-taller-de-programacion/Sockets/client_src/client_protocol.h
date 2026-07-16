#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <string>
#include <vector>

#include "../common_src/item.h"
#include "../common_src/protocol.h"

class ClientProtocol: public Protocol {
private:
    std::vector<Item> recv_store_binary();
    std::vector<Item> recv_store_text();

    void recv_inventory_binary(uint16_t& gold, std::vector<Item>& inventory);
    void recv_inventory_text(uint16_t& gold, std::vector<Item>& inventory);

public:
    // is_binary = false until reception
    explicit ClientProtocol(Socket& skt);

    void send_username(const std::string& username);
    void recv_protocol_type();

    void send_command(const CommandInfo& cmd_info);

    std::vector<Item> recv_store();
    void recv_inventory(uint16_t& gold, std::vector<Item>& inventory);
};

#endif
