#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <cstdint>
#include <string>

#include "socket.h"

enum class OpCode : uint8_t {
    USERNAME_OPCODE = 0x10,
    DEFEAT_CMD_OPCODE = 0x0A,
    EVENT_HEADER_OPCODE = 0x06,
    EVENT_DEFEAT_OPCODE = 0x0C,
    EVENT_APPEAR_OPCODE = 0x0D
};

class Protocol {
protected:
    Socket& skt;

    void send_uint8(uint8_t value);
    uint8_t recv_uint8();

    void send_uint16(uint16_t value);
    uint16_t recv_uint16();

    void send_str(const std::string& message);
    std::string recv_str(uint16_t length);

    void send_opcode(OpCode opcode);
    OpCode recv_opcode();

public:
    explicit Protocol(Socket& skt);

    // It is virtual because destructors are not overwritten
    // in derived classes, but are called in reverse order.
    virtual ~Protocol() = default;
};

#endif
