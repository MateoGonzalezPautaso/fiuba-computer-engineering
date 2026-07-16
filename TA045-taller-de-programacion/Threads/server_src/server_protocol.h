#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <string>

#include "../common_src/command.h"
#include "../common_src/game_event.h"
#include "../common_src/protocol.h"

class ServerProtocol: public Protocol {
public:
    ServerProtocol(Socket& skt, const NPCConfig& npc_config);

    std::string recv_username();

    CommandInfo recv_command();  // receives from client's send_defeat()

    void send_event(const GameEvent& event);

    void shutdown(int how);

    ServerProtocol(const ServerProtocol&) = delete;
    ServerProtocol& operator=(const ServerProtocol&) = delete;

private:
    const NPCConfig& npc_config;

    CommandInfo recv_command_defeat();

    void send_event_defeat(const GameEvent& event);
    void send_event_appear(const GameEvent& event);
};

#endif
