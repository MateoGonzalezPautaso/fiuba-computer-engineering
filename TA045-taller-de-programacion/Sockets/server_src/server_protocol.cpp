#include "server_protocol.h"

#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <string>

ServerProtocol::ServerProtocol(Socket& skt, bool is_binary): Protocol(skt, is_binary) {}

std::string ServerProtocol::recv_username() {
    uint8_t opcode = recv_uint8();

    if (opcode != EXPECTED_OPCODE) {
        throw std::runtime_error("Wrong Opcode in recv_username");
    }

    uint16_t length_username = recv_uint16();

    // creates a string with length_username * '\0'
    std::string username(length_username, '\0');

    // the socket needs char* to write so we use .data()
    skt.recvall(username.data(), length_username);

    return username;
}

void ServerProtocol::send_protocol_type() {
    uint8_t protocol_byte = is_binary ? BINARY_CODE : TEXT_CODE;
    send_uint8(protocol_byte);
}

CommandInfo ServerProtocol::recv_command_binary() {
    CommandInfo cmd_info;

    uint8_t opcode;

    if (skt.recvall(&opcode, sizeof(opcode)) == 0) {
        cmd_info.type = Command::QUIT;
        return cmd_info;
    }

    cmd_info.type = validate_binary_cmd(opcode);

    if (cmd_info.type == Command::BUY || cmd_info.type == Command::SELL) {
        cmd_info.item_code = recv_uint8();
        cmd_info.object_name = map_id_name(static_cast<ItemCode>(cmd_info.item_code.value()));
        std::string& name = cmd_info.object_name.value();

        if (!name.empty()) {
            name[0] = std::tolower(name[0]);
        }
    }

    return cmd_info;
}

CommandInfo ServerProtocol::recv_command_text() {
    CommandInfo cmd_info;

    std::string command_str = recv_str();

    if (command_str.empty()) {
        cmd_info.type = Command::QUIT;
        return cmd_info;
    }

    cmd_info = map_text_cmd(command_str);

    if (cmd_info.type == Command::BUY || cmd_info.type == Command::SELL) {
        cmd_info.item_code = static_cast<uint8_t>(map_name_id(cmd_info.object_name.value()));
    }

    return cmd_info;
}

CommandInfo ServerProtocol::recv_command() {
    if (is_binary) {
        return recv_command_binary();
    } else {
        return recv_command_text();
    }
}

void ServerProtocol::send_store_binary(const std::vector<Item>& items) {
    send_uint8(static_cast<uint8_t>(Command::STORE));

    // implicit narrowing conversion from size_t to uint16_t
    send_uint16(static_cast<uint16_t>(items.size()));  // Amount of different items

    for (const Item& item: items) {
        send_uint8(static_cast<uint8_t>(item.code));
        send_uint16(item.stock);
        send_uint16(item.buy_price);
        send_uint16(item.sell_price);
    }
}

void ServerProtocol::send_store_text(const std::vector<Item>& items) {
    for (const Item& item: items) {
        std::string message = item.name + "(" + std::to_string(item.stock) + ")," +
                              std::to_string(item.buy_price) + "," +
                              std::to_string(item.sell_price) + "\n";
        send_str(message);
    }

    send_str("\n");
}

void ServerProtocol::send_store(const std::vector<Item>& items) {
    if (is_binary) {
        send_store_binary(items);
    } else {
        send_store_text(items);
    }
}

void ServerProtocol::send_inventory_binary(uint16_t gold, const std::vector<Item>& items_to_send) {
    send_uint8(static_cast<uint8_t>(Command::INVENTORY));
    send_uint16(gold);

    // implicit narrowing conversion from size_t to uint16_t
    send_uint16(static_cast<uint16_t>(items_to_send.size()));  // Amount of different items

    for (const Item& item: items_to_send) {
        send_uint8(static_cast<uint8_t>(item.code));
        send_uint16(item.stock);
    }
}

void ServerProtocol::send_inventory_text(uint16_t gold, const std::vector<Item>& items_to_send) {
    std::string gold_str = "oro:" + std::to_string(gold) + "\n";
    send_str(gold_str);

    for (const Item& item: items_to_send) {
        std::string message = item.name + "(" + std::to_string(item.stock) + ")" + "\n";
        send_str(message);
    }

    send_str("\n");
}

std::vector<Item> ServerProtocol::prepare_inventory(
        const std::vector<std::pair<ItemCode, uint16_t>>& inventory) const {
    std::vector<Item> items_to_send;

    for (const auto& pair: inventory) {
        Item item;
        item.code = pair.first;
        item.stock = pair.second;
        item.name = map_id_name(item.code);
        items_to_send.push_back(item);
    }

    // sort before sending
    std::sort(items_to_send.begin(), items_to_send.end(),
              [](const Item& a, const Item& b) { return a.name < b.name; });

    return items_to_send;
}

void ServerProtocol::send_inventory(uint16_t gold,
                                    const std::vector<std::pair<ItemCode, uint16_t>>& inventory) {
    std::vector<Item> items_to_send = prepare_inventory(inventory);

    if (is_binary) {
        send_inventory_binary(gold, items_to_send);
    } else {
        send_inventory_text(gold, items_to_send);
    }
}
