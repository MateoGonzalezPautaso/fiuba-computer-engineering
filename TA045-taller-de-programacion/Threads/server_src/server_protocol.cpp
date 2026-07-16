#include "server_protocol.h"

#include <stdexcept>
#include <string>

ServerProtocol::ServerProtocol(Socket& skt, const NPCConfig& npc_config):
        Protocol(skt), npc_config(npc_config) {}

std::string ServerProtocol::recv_username() {
    OpCode opcode = recv_opcode();

    if (opcode != OpCode::USERNAME_OPCODE)
        throw std::runtime_error("Wrong Opcode in recv_username");

    uint16_t length_username = recv_uint16();
    std::string username = recv_str(length_username);

    return username;
}

CommandInfo ServerProtocol::recv_command() {
    OpCode type = recv_opcode();

    if (type == OpCode::DEFEAT_CMD_OPCODE) {
        return recv_command_defeat();
    } else {
        throw std::runtime_error("Protocol error: received unknown command opcode");
    }
}

CommandInfo ServerProtocol::recv_command_defeat() {
    CommandInfo cmd_info;
    cmd_info.type = Command::DEFEAT;

    NPCCode npc_code = static_cast<NPCCode>(recv_uint8());

    try {
        npc_config.map_code_name(npc_code);
    } catch (const std::invalid_argument&) {
        throw std::runtime_error("Protocol error: received unknown NPC code in DEFEAT command");
    }

    cmd_info.npc_code = npc_code;
    return cmd_info;
}

void ServerProtocol::send_event(const GameEvent& event) {
    send_opcode(OpCode::EVENT_HEADER_OPCODE);

    if (event.type == EventType::NPC_DEFEATED) {
        send_event_defeat(event);
    } else if (event.type == EventType::NPC_APPEARED) {
        send_event_appear(event);
    }
}

void ServerProtocol::send_event_defeat(const GameEvent& event) {
    send_opcode(OpCode::EVENT_DEFEAT_OPCODE);

    // EventType is NPC_DEFEATED so player_name is safe to use
    const std::string& player_name = event.player_name.value();
    uint16_t length_username = static_cast<uint16_t>(player_name.length());

    send_uint16(length_username);
    send_str(player_name);

    send_uint8(static_cast<uint8_t>(event.npc_code));
}

void ServerProtocol::send_event_appear(const GameEvent& event) {
    send_opcode(OpCode::EVENT_APPEAR_OPCODE);
    send_uint8(static_cast<uint8_t>(event.npc_code));
}

void ServerProtocol::shutdown(int how) {
    // "how" could be SHUT_RD (0), SHUT_WR (1) or SHUT_RDWR (2)
    skt.shutdown(how);
}
