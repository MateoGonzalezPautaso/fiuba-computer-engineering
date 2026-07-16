#include "protocol.h"

#include <map>
#include <stdexcept>

#include <arpa/inet.h>

Protocol::Protocol(Socket& skt, bool is_binary): skt(skt), is_binary(is_binary) {}

Command Protocol::validate_binary_cmd(uint8_t opcode) const {
    Command cmd = static_cast<Command>(opcode);

    switch (cmd) {
        case Command::STORE:
        case Command::INVENTORY:
        case Command::BUY:
        case Command::SELL:
        case Command::QUIT:
            return cmd;

        default:
            return Command::INVALID;
    }
}

std::string Protocol::map_cmd_text(const CommandInfo& cmd_info) const {
    // not using map or unordered map because return value changes
    // depending on BUY or SELL

    switch (cmd_info.type) {
        case Command::STORE:
            return "tienda.contenido\n";
        case Command::INVENTORY:
            return "inventario.contenido\n";
        case Command::BUY:
            return "tienda.comprar:" + cmd_info.object_name.value() + "\n";
        case Command::SELL:
            return "tienda.vender:" + cmd_info.object_name.value() + "\n";
        default:
            return "Invalid";
    }
}

CommandInfo Protocol::map_text_cmd(const std::string& command_str) const {
    // not using map or unordered map because return value changes
    // depending on BUY or SELL
    CommandInfo cmd_info;

    if (command_str == "tienda.contenido") {
        cmd_info.type = Command::STORE;
    } else if (command_str == "inventario.contenido") {
        cmd_info.type = Command::INVENTORY;
        // cppcheck-suppress stlIfStrFind
    } else if (command_str.find("tienda.comprar:") == 0) {
        cmd_info.object_name = command_str.substr(15);
        cmd_info.type = Command::BUY;
        // cppcheck-suppress stlIfStrFind
    } else if (command_str.find("tienda.vender:") == 0) {
        cmd_info.object_name = command_str.substr(14);
        cmd_info.type = Command::SELL;
    } else {
        cmd_info.type = Command::INVALID;
    }

    return cmd_info;
}

std::string Protocol::map_id_name(ItemCode item_code) const {
    static const std::map<ItemCode, std::string> code_to_name = {
            {ItemCode::SWORD, "Espada"},
            {ItemCode::BOW, "Arco compuesto"},
            {ItemCode::FLUTE, "Flauta elfica"},
            {ItemCode::BRANCH, "Vara de fresno"},
            {ItemCode::ARMOR, "Armadura de hierro"}};

    auto it = code_to_name.find(item_code);

    if (it != code_to_name.end())
        return it->second;

    throw std::invalid_argument("Item code not recognized");
}

ItemCode Protocol::map_name_id(const std::string& object_name) const {
    static const std::map<std::string, ItemCode> name_to_code = {
            {"espada", ItemCode::SWORD},
            {"arco compuesto", ItemCode::BOW},
            {"flauta elfica", ItemCode::FLUTE},
            {"vara de fresno", ItemCode::BRANCH},
            {"armadura de hierro", ItemCode::ARMOR}};

    auto it = name_to_code.find(object_name);

    if (it != name_to_code.end())
        return it->second;

    throw std::invalid_argument("Item name not recognized: " + object_name);
}

void Protocol::send_uint8(uint8_t value) { skt.sendall(&value, sizeof(value)); }

uint8_t Protocol::recv_uint8() {
    uint8_t value;
    int bytes = skt.recvall(&value, sizeof(value));

    if (bytes <= 0) {
        throw std::runtime_error("Socket cerrado o error al recibir uint8_t");
    }

    return value;
}

void Protocol::send_uint16(uint16_t value) {
    uint16_t net_value = htons(value);  // Host to network
    skt.sendall(&net_value, sizeof(net_value));
}

uint16_t Protocol::recv_uint16() {
    uint16_t net_value;
    int bytes = skt.recvall(&net_value, sizeof(net_value));

    if (bytes <= 0) {
        throw std::runtime_error("Socket cerrado o error al recibir uint16_t");
    }

    return ntohs(net_value);  // Network to host
}

void Protocol::send_str(const std::string& message) {
    skt.sendall(message.c_str(), message.length());
}

std::string Protocol::recv_str() {
    std::string line;
    char c;

    while (true) {
        int bytes_read = skt.recvall(&c, 1);

        if (bytes_read == 0)
            break;

        if (c == '\n')
            break;

        line += c;
    }

    return line;
}
