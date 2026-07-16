#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <cstdint>
#include <string>
#include <utility>

#include "command.h"
#include "item.h"
#include "socket.h"

#define EXPECTED_OPCODE 1

#define BINARY_CODE 0xF0
#define TEXT_CODE 0xF1

class Protocol {
protected:
    Socket& skt;
    bool is_binary;  // true -> binary - false -> text

    Command validate_binary_cmd(uint8_t opcode) const;

    CommandInfo map_text_cmd(const std::string& command_str) const;
    std::string map_cmd_text(const CommandInfo& cmd_info) const;

    std::string map_id_name(ItemCode item_code) const;
    ItemCode map_name_id(const std::string& object_name) const;

    void send_uint8(uint8_t value);
    uint8_t recv_uint8();

    void send_uint16(uint16_t value);
    uint16_t recv_uint16();

    void send_str(const std::string& message);
    std::string recv_str();

public:
    Protocol(Socket& skt, bool is_binary);

    // It is virtual because destructors are not overwritten
    // in derived classes, but are called in reverse order.
    virtual ~Protocol() = default;
};

#endif
