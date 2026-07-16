#ifndef CLIENT_H
#define CLIENT_H

#include <string>

#include "../common_src/command.h"

#include "client_protocol.h"
#include "client_view.h"

class Client {
public:
    Client(const std::string& hostname, const std::string& servname);

    void run();

private:
    std::string hostname;
    std::string servname;

    NPCConfig npc_config;
    ClientView view;

    std::string get_username() const;

    void handle_session(ClientProtocol& clt_prot);

    void handle_read(ClientProtocol& clt_prot, const CommandInfo& cmd_info);
};

#endif
