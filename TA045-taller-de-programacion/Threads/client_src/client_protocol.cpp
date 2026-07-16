#include "client_protocol.h"

#include <stdexcept>
#include <string>

ClientProtocol::ClientProtocol(Socket& skt, const NPCConfig& npc_config):
        Protocol(skt), npc_config(npc_config) {}

void ClientProtocol::send_username(const std::string& username) {
    uint16_t length_username = static_cast<uint16_t>(username.length());

    send_opcode(OpCode::USERNAME_OPCODE);
    send_uint16(length_username);

    send_str(username);
}

void ClientProtocol::send_defeat(NPCCode npc_code) {
    send_opcode(OpCode::DEFEAT_CMD_OPCODE);
    send_uint8(static_cast<uint8_t>(npc_code));
}

GameEvent ClientProtocol::recv_event() {
    GameEvent event;
    OpCode header = recv_opcode();

    if (header != OpCode::EVENT_HEADER_OPCODE)
        throw std::runtime_error("Unexpected event header from server");

    OpCode type = recv_opcode();

    if (type == OpCode::EVENT_DEFEAT_OPCODE) {
        recv_event_defeat(event);
    } else if (type == OpCode::EVENT_APPEAR_OPCODE) {
        recv_event_appear(event);
    } else {
        throw std::runtime_error("Unknown event type");
    }

    return event;
}

void ClientProtocol::recv_event_defeat(GameEvent& event) {
    event.type = EventType::NPC_DEFEATED;

    // 0x06 0x0C <length-player-name> <player-name> <npc-code>
    uint16_t name_len = recv_uint16();
    event.player_name = recv_str(name_len);

    NPCCode npc_code = static_cast<NPCCode>(recv_uint8());

    try {
        npc_config.map_code_name(npc_code);
    } catch (const std::invalid_argument&) {
        throw std::runtime_error("Protocol error: received unknown NPC code in DEFEAT event");
    }

    event.npc_code = npc_code;
}

void ClientProtocol::recv_event_appear(GameEvent& event) {
    event.type = EventType::NPC_APPEARED;

    // 0x06 0x0D <npc-code>
    NPCCode npc_code = static_cast<NPCCode>(recv_uint8());

    try {
        npc_config.map_code_name(npc_code);
    } catch (const std::invalid_argument&) {
        throw std::runtime_error("Protocol error: received unknown NPC code in APPEAR event");
    }

    event.npc_code = npc_code;
}
