#include "client_protocol.h"

#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <string>

ClientProtocol::ClientProtocol(Socket& skt): Protocol(skt, false) {}

void ClientProtocol::send_username(const std::string& username) {
    uint16_t length_username = static_cast<uint16_t>(username.length());

    send_uint8(EXPECTED_OPCODE);
    send_uint16(length_username);

    // the socket needs const char* to read so we use .c_str()
    skt.sendall(username.c_str(), length_username);
}

void ClientProtocol::recv_protocol_type() {
    uint8_t protocol_byte = recv_uint8();

    if (protocol_byte == BINARY_CODE) {
        is_binary = true;
    } else if (protocol_byte == TEXT_CODE) {
        is_binary = false;
    } else {
        throw std::runtime_error("Unknown protocol byte");
    }
}

void ClientProtocol::send_command(const CommandInfo& cmd_info) {
    if (is_binary) {
        send_uint8(static_cast<uint8_t>(cmd_info.type));

        if (cmd_info.type == Command::BUY || cmd_info.type == Command::SELL) {
            std::string object_name = cmd_info.object_name.value();
            std::transform(object_name.begin(), object_name.end(), object_name.begin(),
                           [](unsigned char c) { return std::tolower(c); });
            send_uint8(static_cast<uint8_t>(map_name_id(object_name)));
        }
    } else {
        std::string message = map_cmd_text(cmd_info);
        send_str(message);
    }
}

std::vector<Item> ClientProtocol::recv_store_binary() {
    std::vector<Item> items;

    uint8_t opcode = recv_uint8();

    if (opcode != static_cast<uint8_t>(Command::STORE)) {
        throw std::runtime_error("Wrong Opcode in recv_store");
    }

    uint16_t n_items = recv_uint16();

    for (uint16_t i = 0; i < n_items; i++) {
        Item item;
        item.code = static_cast<ItemCode>(recv_uint8());
        item.stock = recv_uint16();
        item.buy_price = recv_uint16();
        item.sell_price = recv_uint16();
        item.name = map_id_name(item.code);

        if (!item.name.empty()) {
            item.name[0] = std::toupper(item.name[0]);
        }

        items.push_back(item);
    }

    return items;
}


std::vector<Item> ClientProtocol::recv_store_text() {
    std::vector<Item> items;
    std::string line = recv_str();

    while (!line.empty()) {
        Item item;

        size_t open_parenthesis_pos = line.find('(');
        size_t close_parenthesis_pos = line.find(')');
        size_t first_comma = line.find(',');
        size_t second_comma = line.find(',', first_comma + 1);

        item.name = line.substr(0, open_parenthesis_pos);

        if (!item.name.empty()) {
            item.name[0] = std::toupper(item.name[0]);
        }

        std::string stock_str = line.substr(open_parenthesis_pos + 1,
                                            close_parenthesis_pos - open_parenthesis_pos - 1);
        std::string buy_price_str = line.substr(first_comma + 1, second_comma - first_comma - 1);
        std::string sell_price_str = line.substr(second_comma + 1);

        item.stock = std::stoi(stock_str);
        item.buy_price = std::stoi(buy_price_str);
        item.sell_price = std::stoi(sell_price_str);

        items.push_back(item);

        line = recv_str();
    }

    return items;
}

std::vector<Item> ClientProtocol::recv_store() {
    if (is_binary) {
        return recv_store_binary();
    } else {
        return recv_store_text();
    }
}

void ClientProtocol::recv_inventory_binary(uint16_t& gold, std::vector<Item>& inventory) {
    uint8_t opcode = recv_uint8();

    if (opcode != static_cast<uint8_t>(Command::INVENTORY)) {
        throw std::runtime_error("Wrong Opcode in recv_inventory");
    }

    gold = recv_uint16();
    uint16_t n_items = recv_uint16();

    for (uint16_t i = 0; i < n_items; ++i) {
        Item item;
        item.code = static_cast<ItemCode>(recv_uint8());
        item.stock = recv_uint16();
        item.name = map_id_name(item.code);

        if (!item.name.empty()) {
            item.name[0] = std::toupper(item.name[0]);
        }

        inventory.push_back(item);
    }
}

void ClientProtocol::recv_inventory_text(uint16_t& gold, std::vector<Item>& inventory) {
    std::string line = recv_str();
    size_t gold_pos = line.find(':');
    std::string gold_str = line.substr(gold_pos + 1);
    gold = std::stoi(gold_str);

    line = recv_str();

    while (!line.empty()) {
        Item item;

        size_t open_parenthesis_pos = line.find('(');
        size_t close_parenthesis_pos = line.find(')');

        item.name = line.substr(0, open_parenthesis_pos);

        if (!item.name.empty()) {
            item.name[0] = std::toupper(item.name[0]);
        }

        std::string stock_str = line.substr(open_parenthesis_pos + 1,
                                            close_parenthesis_pos - open_parenthesis_pos - 1);

        item.stock = std::stoi(stock_str);

        inventory.push_back(item);

        line = recv_str();
    }
}

void ClientProtocol::recv_inventory(uint16_t& gold, std::vector<Item>& inventory) {
    if (is_binary) {
        recv_inventory_binary(gold, inventory);
    } else {
        recv_inventory_text(gold, inventory);
    }
}
