#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <string>

#include "../common_src/game_event.h"
#include "../common_src/protocol.h"

class ClientProtocol: public Protocol {
public:
    ClientProtocol(Socket& skt, const NPCConfig& npc_config);

    void send_username(const std::string& username);

    GameEvent recv_event();
    void send_defeat(NPCCode npc_code);

private:
    const NPCConfig& npc_config;

    void recv_event_defeat(GameEvent& event);
    void recv_event_appear(GameEvent& event);
};

#endif
